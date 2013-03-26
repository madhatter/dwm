/* See LICENSE file for copyright and license details. */
#include "X11/XF86keysym.h"
#include "push.c"
#include "runorraise.c"

/* appearance */
static const char font[] = "-*-terminus-medium-*-*-*-12-*-*-*-*-*-utf8-*";
//static const char font[] = "-*-*-medium-*-*-*-14-*-*-*-*-*-*-*";

#define NUMCOLORS 20
static const char colors[NUMCOLORS][ColLast][20] = {
    /* border     fg         bg */
    { "#242323", "#94928F", "#000000" },            /* 01 - normal */
    { "#666362", "#CDCDCD", "#17597b" },            /* 02 - selected */
    { "#91444D", "#91444D", "#000000" },            /* 03 - urgent */

    { "#0A1724", "#0A1724", "#000000" },            /* 04 - black */
    { "#701726", "#701726", "#000000" },            /* 05 - red */
    { "#286332", "#286332", "#000000" },            /* 06 - green */
    { "#706A2D", "#706A2D", "#000000" },            /* 07 - yellow */
    { "#00508A", "#00508A", "#000000" },            /* 08 - blue */
    { "#454E7D", "#454E7D", "#000000" },            /* 09 - magenta */
    { "#000000", "#000000", "#000000" },            /* unusable */
    { "#007070", "#007070", "#000000" },            /* 0B - cyan */
    { "#5E687D", "#5E687D", "#000000" },            /* 0C - light gray */
    { "#303B4A", "#303B4A", "#000000" },            /* 0D - gray */
    { "#A33144", "#A33144", "#000000" },            /* 0E - light red */
    { "#449652", "#449652", "#000000" },            /* 0F - light green */
    { "#A38262", "#A38262", "#000000" },            /* 10 - light yellow */
    { "#357CB0", "#357CB0", "#000000" },            /* 11 - light blue */
    { "#963576", "#963576", "#000000" },            /* 12 - light magenta */
    { "#2C9696", "#2C9696", "#000000" },            /* 13 - light cyan */
    { "#878F96", "#878F96", "#000000" },            /* 14 - white */
};

static const unsigned int borderpx = 1;             /* border pixel of windows */
static const unsigned int snap     = 8;             /* snap pixel */
static const Bool showbar          = True;          /* False means no bar */
static const Bool topbar           = True;          /* False means bottom bar */
static const char scratchpadname[] = "Scratchpad";  /* scratchpad window title */

/* layout(s) */
static const float mfact           = 0.50;          /* factor of master area size [0.05..0.95] */
static const int nmaster           = 1;             /* number of clients in master area */
static const Bool resizehints      = False;         /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[|]",      tile },
	{ "[-]",      bstack },
	{ "[ ]",      monocle },                         /* first entry is default */
	{ "><>",      NULL },                            /* no layout function means floating behavior */
};

/* tagging */
static const Tag tags[] = {
    /* name       layout           mfact    nmaster */
    { "term",     &layouts[0],     -1,      -1 },
    { "code",     &layouts[0],     -1,      -1 },
    { "mail",     &layouts[0],     -1,      -1 },
    { "www",      &layouts[0],     -1,      -1 },
    { "irc",      &layouts[0],     -1,      -1 },
    { "sfx",      &layouts[3],     -1,      -1 },
    { "gfx",      &layouts[3],     -1,      -1 },
    { "vm",       &layouts[2],     -1,      -1 },
};

static const Rule rules[] = {
    /* class      instance     title        tags mask  isfloating  iscentred   monitor */
   	{ "Gimp",     NULL,       NULL,         1 << 6,    True,        -1 }, // appears on tag 7
	{ "Firefox",  NULL,       NULL,         1 << 3,    False,       -1 }, // appears on tag 4
	{ "URxvt",    NULL,       "ncmpcpp",    1 << 5,    True,        -1 },
	{ "mplayer2", NULL,       NULL,         0,         True,        -1 },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[]      = { "dmenu_run", "-i", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],
                                    "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-i", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]	= { "urxvt", NULL };
static const char *lockcmd[]	= { "slimlock", NULL };
static const char *ncmpcppcmd[] = { "urxvt", "-title", "ncmpcpp", "-e", "ncmpcpp", NULL };

static const char *voldown[]    = { "amixer", "-q", "set", "Master", "2dB-",  NULL };
static const char *voltoggle[]  = { "amixer", "-q", "set", "Master", "toggle",  NULL };
static const char *volup[]      = { "amixer", "-q", "set", "Master", "2dB+",  NULL };

static const char *next[]       = { "mpc", "next", NULL };
static const char *play[]       = { "mpc", "toggle", NULL };
static const char *prev[]       = { "mpc", "prev", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = lockcmd } },		
	{ MODKEY,                       XK_n,      spawn,          {.v = ncmpcppcmd } },
	{ MODKEY|ShiftMask,				XK_Up,     spawn,		   {.v = volup } },
	{ MODKEY|ShiftMask,				XK_Down,   spawn,		   {.v = voldown } },
	{ MODKEY|ShiftMask,				XK_Left,   spawn,		   {.v = prev } },
	{ MODKEY|ShiftMask,				XK_Right,  spawn,		   {.v = next } },
	{ MODKEY|ShiftMask,				XK_p,	   spawn,		   {.v = play } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

