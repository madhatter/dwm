# dwm

A custom build of [dwm](https://dwm.suckless.org) for Arch Linux, managed as an AUR-style PKGBUILD with a set of patches applied on top of the vanilla source.

## Package

| | |
|---|---|
| `pkgname` | `dwm-custom` |
| `pkgver` | `6.5` |
| **Patches** | alpha, pertag, bottomstack, centered, cfacts, vanitygaps |
> Note: cfacts, bottomstack and vanitygaps are in one patch combined.

## Structure

| File/Dir | Description |
|---|---|
| `PKGBUILD` | Arch Linux package definition, downloads dwm source and applies patches |
| `config.h` | dwm configuration, copied into the build by the PKGBUILD |
| `dwm-*.diff` | Patches applied during the build |
| `Dockerfile` | Minimal Arch environment for testing patch compatibility |

## Building (Arch Linux)

```bash
makepkg -si
```

`config.h` is picked up automatically from `$SRCDEST` by the PKGBUILD.

## Testing patches

The Dockerfile runs a dry-run check and a full patch+compile against the target dwm version without needing an Arch system:

```bash
docker build -t dwm-patch-test .
docker run --rm dwm-patch-test
```

A successful run applies all patches and compiles dwm without errors.
