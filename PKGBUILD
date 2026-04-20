# Maintainer: Arvid Warnecke <arvid.warnecke@gmail.com>

pkgname=dwm-custom
pkgver=6.5
pkgrel=3
pkgdesc="A custom version of the dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft')
makedepends=('git')
install=dwm.install
provides=('dwm')
conflicts=('dwm')
_srcname=dwm-$pkgver
#epoch=1
source=(dwm.desktop
        http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz)
_patches=(dwm-alpha-20230401-348f655.diff
          dwm-pertag.diff
          dwm-centered.diff
          dwm-statuscolors.diff
          dwm-cfacts-vanitygaps-6.4_combo.diff)
md5sums=('939f403a71b6e85261d09fc3412269ee'
         '446e84f5b151a1d4483fd72fd647e47e'
         'd58169e88c4155db69964784b0bec7cf'
         '9f8c3a6ed9745856f05921837660df08'
         'f69050fc7ce0240237e6d831f83f405a'
         '3e9dac5651119983a650bac76aef4920'
         'cd58dcf76adccaac750b4e23cfaa002b')
source=(${source[@]} ${_patches[@]})

#pkgver(){
#  cd $srcdir/$_srcname
#  git describe --tags |sed 's/-/./g'
#}
#
prepare() {
  cd $srcdir/$_srcname

  for p in "${_patches[@]}"; do
        echo "=> $p"
    patch < ../$p || return 1
  done

  if [[ -f "$SRCDEST/config.h" ]]; then
    cp -f "$SRCDEST/config.h" config.h
  fi
}

build() {
  cd $srcdir/$_srcname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$_srcname
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install -m644 -D LICENSE "$pkgdir/usr/share/licenses/$pkgname/LICENSE"
  install -m644 -D README "$pkgdir/usr/share/doc/$pkgname/README"
  install -m644 -D ../dwm.desktop "$pkgdir/usr/share/xsessions/dwm.desktop"
}

# vim:set ts=2 sw=2 et:
