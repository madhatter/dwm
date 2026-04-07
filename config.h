/* See LICENSE file for copyright and license details. */

/* Customized config.h */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = { "DejaVuSansMono Nerd Font Mono:size=12" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0x99u;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const unsigned int alphas[][3]      = {
        /*               fg      bg        border     */
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "\ue795", "\ue62b", "\uf6ee", "\uf738", "\uf27a", "\uf886", "\ue22b", "\ue708" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask    iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,         1 << 6,        0,           1,         -1 }, // appears on tag 7
	{ "URxvt",    NULL,       "ncmpcpp",    1 << 5,        1,           1,         -1 },
	{ "URxvt",    NULL,       "ncspot",     1 << 5,        1,           1,         -1 },
	{ "keepassx", NULL,       NULL,         1 << 7,        0,           1,         -1 },
	{ "Spotify",  NULL,       NULL,         1 << 5,        0,           1,         -1 }, // fixes rendering glitches
	{ "Steam",    NULL,       NULL,         1 << 6,        0,           1,         -1 }, // fixes rendering glitches
	{ "jetbrains-idea",  NULL,   NULL,      1 << 1,        0,           1,         -1 }, // fixes rendering glitches
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *dmenucmd[] = { "/home/awarnecke/bin/dmenu_bind.sh", NULL };
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *lockcmd[]	= { "slock", NULL };
static const char *ncmpcppcmd[] = { "urxvt", "-title", "ncmpcpp", "-e", "ncmpcpp", NULL };
static const char *ncspotcmd[] = { "urxvt", "-title", "ncspot", "-e", "/home/awarnecke/.cargo/bin/ncspot", NULL };

static const char *voldown[]    = { "amixer", "-q", "set", "Master", "2%-",  NULL };
static const char *voltoggle[]  = { "pactl", "set-sink-mute", "0", "toggle",  NULL };
static const char *volup[]      = { "amixer", "-q", "set", "Master", "2%+",  NULL };

static const char *brightup[]   = { "sudo", "light", "-A", "5", NULL};
static const char *brightdown[] = { "sudo", "light", "-U", "5", NULL};

static const char *next[]       = { "mpc", "next", NULL };
static const char *play[]       = { "mpc", "toggle", NULL };
static const char *prev[]       = { "mpc", "prev", NULL };

static const char *snext[]		= { "spotifycli", "--next", NULL };
static const char *splay[]		= { "spotifycli", "--playpause", NULL };
static const char *sprev[]		= { "spotifycli", "--prev", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            0x1008ff03,spawn,          {.v = brightdown} },
	{ 0,                            0x1008ff02,spawn,          {.v = brightup} },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = lockcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = ncmpcppcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = ncspotcmd } },
	{ MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = volup } },
	{ 0,                            0x1008ff13,spawn,          {.v = volup } },
	{ MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = voldown } },
	{ 0,                            0x1008ff11,spawn,          {.v = voldown } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = voltoggle } },
	{ 0,                            0x1008ff12,spawn,          {.v = voltoggle } },
	{ MODKEY|ShiftMask,             XK_Left,   spawn,          {.v = prev } },
	{ MODKEY|ShiftMask,             XK_Right,  spawn,          {.v = next } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = play } },
	{ MODKEY|ControlMask,           XK_Left,   spawn,          {.v = sprev } },
	{ MODKEY|ControlMask,           XK_Right,  spawn,          {.v = snext } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = splay } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
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
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

