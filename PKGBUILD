# $Id: PKGBUILD 60970 2011-12-19 21:33:58Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.0
pkgrel=3
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
		dwm.desktop)
_patches=(01-dwm-$pkgver-statuscolors.diff
          02-dwm-$pkgver-pertag2.diff
          03-dwm-$pkgver-scratchpad-stay.diff
          04-dwm-$pkgver-cflags.diff
          05-dwm-$pkgver-single_window_no_border.diff
          06-dwm-$pkgver-centred-floating.diff
          07-dwm-$pkgver-save_floats.diff)
md5sums=(8bb00d4142259beb11e13473b81c0857
		 459540fb7c093f19c921f6954e8982b1
		 689534c579b1782440ddcaf71537d8fd
		 939f403a71b6e85261d09fc3412269ee
		 519d395d59b7aee06b0e318e81b25929
		 5d2a023e8f649a2539887d1cabb70b31
		 c08fe44446226ad8748f850989be629a
		 b4b8ea44c43be3cc6cd31b0aa9ec5c11
		 31ccb769758767e4fb692acbf49d6a80
		 7aef89991a42e4e65c880a6e60024ed7
		 ad4d21ab24896099a434e3b45ddb6f00)
source=(${source[@]} ${_patches[@]})

build() {
  cd $srcdir/$pkgname-$pkgver

  for p in "${_patches[@]}"; do
  	echo "=> $p"
    patch < ../$p || return 1
  done

  cp $srcdir/config.h config.h
  cp $srcdir/push.c push.c
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
