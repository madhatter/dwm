FROM archlinux:base

RUN echo 'DisableSandbox' >> /etc/pacman.conf && \
    pacman -Sy --noconfirm base-devel libx11 libxinerama libxft curl

WORKDIR /build
RUN curl -O https://dl.suckless.org/dwm/dwm-6.5.tar.gz && \
    tar xzf dwm-6.5.tar.gz

COPY *.diff /patches/

WORKDIR /build/dwm-6.5

CMD set -e; \
    trap 'echo "=== FAILED ==="' ERR; \
    echo "=== Checking patches (dry-run) ==="; \
    for p in /patches/dwm-alpha-20180613-b69c870.diff \
             /patches/dwm-pertag.diff \
             /patches/dwm-bottomstack.diff \
             /patches/dwm-centered.diff; do \
      echo "=== $(basename $p) ==="; \
      patch --dry-run < "$p" 2>&1 | tail -5; \
      echo; \
    done && \
    echo "=== Applying patches ===" && \
    for p in /patches/dwm-alpha-20230401-348f655.diff \
             /patches/dwm-pertag.diff \
             /patches/dwm-bottomstack.diff \
             /patches/dwm-centered.diff; do \
      patch < "$p"; \
    done && \
    echo "=== Building ===" && \
    make && \
    echo "=== SUCCESS ==="
