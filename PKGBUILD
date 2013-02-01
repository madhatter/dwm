# $Id: PKGBUILD 60970 2011-12-19 21:33:58Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
		config.h
		push.c
		runorraise.c
		bstack.c
		dwm.desktop)
_patches=(01-dwm-$pkgver-statuscolors.diff
          02-dwm-$pkgver-scratchpad-stay.diff
          03-dwm-$pkgver-single_window_no_border.diff
          04-dwm-$pkgver-centred-floating.diff
          05-dwm-$pkgver-save_floats.diff
          06-dwm-$pkgver-no_title.diff)
source=(${source[@]} ${_patches[@]})

build() {
  cd $srcdir/$pkgname-$pkgver

  for p in "${_patches[@]}"; do
  	msg "$p"
    patch < ../$p || return 1
  done

  cp $srcdir/config.h config.h
  cp $srcdir/push.c push.c
  cp $srcdir/runorraise.c runorraise.c
  cp $srcdir/bstack.c bstack.c
  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/^CFLAGS = -g/#CFLAGS += -g/g' config.mk
  sed -i 's/^#CFLAGS = -std/CFLAGS += -std/g' config.mk
  sed -i 's/^LDFLAGS = -g/#LDFLAGS += -g/g' config.mk
  sed -i 's/^#LDFLAGS = -s/LDFLAGS += -s/g' config.mk
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
