# dwm Patches (old repo, dwm 6.0)

These patches were used in the previous dwm setup. Listed here for reference when updating to a newer version.

## Summary

Patches already present in the current repo:

| Patch | Status |
|---|---|
| pertag | already included |
| centered (centred-floating) | already included (as `dwm-centered.diff`) |
| alpha | new addition (not in old repo) |
| bottomstack | new addition (not in old repo) |

New additions in the current repo (not in old repo):

| Patch | Description |
|---|---|
| alpha | Adds transparency to the dwm bar using the X composite extension. Transparency level is configurable per color scheme in `config.h` via an alpha value. |
| bottomstack | Adds a layout variant where the stack area sits below the master window instead of beside it. Comes in two flavors: `bstack` (clients tiled horizontally in the stack) and `bstackhoriz` (clients stacked vertically). |

Patches from the old repo not yet in the current setup:

| Patch | Notes |
|---|---|
| statuscolors | not included |
| scratchpad-stay | not included |
| single_window_no_border | not included |
| save_floats | not included |
| cflags | not a real patch, just compiler flag tweaks — skip |

## 01 - statuscolors

Enables colored text in the status bar (right side). Status scripts can switch between multiple color schemes defined in `config.h` using escape sequences (`\x01`, `\x02`, etc.). Useful for visually highlighting status indicators like low battery.

**Caveats:** Modifies the global color definition structure, which can conflict with other color-related patches (e.g. alpha). Requires status scripts to explicitly emit escape sequences.

See: https://dwm.suckless.org/patches/statuscolors/

## 02 - pertag2

Stores layout, master width factor, bar position, and nmaster count per tag instead of globally. Each tag has its own independent window management settings.

`pertag2` is a community variant (not an official suckless patch name) that was used for older dwm versions (5.x) and included additional fixes. Likely based on the standard `pertag` patch.

**Caveats:** Can conflict with layout patches that also modify global layout variables (e.g. bstack). Multiple versions exist for different dwm releases.

See: https://dwm.suckless.org/patches/pertag/

## 03 - scratchpad-stay

A variant of the scratchpad patch. The standard scratchpad spawns or toggles a floating terminal window via a keybind. The "stay" variant keeps the scratchpad visible on a dedicated tag rather than hiding it completely, toggled via `toggleview`. Similar in behavior to the `scratchpads` patch (plural).

**Caveats:** Can have issues on multi-monitor setups. Interacts with floating and layout patches.

See: https://dwm.suckless.org/patches/scratchpad/
See also: https://dwm.suckless.org/patches/scratchpads/

## 04 - cflags

Not a functionality patch. Simply changes compiler flags in `config.mk` from `-Os` to `-O2 -march=native`. No equivalent needed — can be set directly in the PKGBUILD or `config.mk` if desired.

## 05 - single_window_no_border

Automatically removes the window border when only a single window is visible on the current tag (in both tiling and monocle layout). The original border width is saved and restored when a second window appears.

Community variant of the official `noborder` patch.

**Caveats:** The simple noborder variant can cause a growing-border bug with floating windows. Interacts with other patches that modify border width (`singularborders`, `smartborders`).

See: https://dwm.suckless.org/patches/noborder/

## 06 - centred-floating

Automatically centers floating windows on screen when they are opened, instead of placing them at their requested or default position. Behavior can be overridden per window via rules in `config.h`.

Not an official suckless patch under this name. The modern equivalent is `alwayscenter`. This variant targets dwm 6.0.

**Caveats:** By default centers all clients; windows that need specific positions (tooltips, popups) must be excluded explicitly. Interacts with other patches that modify `manage()` (e.g. `save_floats`).

See (modern equivalent): https://dwm.suckless.org/patches/alwayscenter/

## 07 - save_floats

Saves the size and position of each floating window before it is forced into tiling mode. When the window is returned to floating mode, the saved dimensions are restored instead of using default floating sizes.

**Caveats:** Saved values are lost when dwm restarts. Can interact with `centred-floating`/`alwayscenter` since both hook into `manage()`; patch application order matters.

See: https://dwm.suckless.org/patches/save_floats/
