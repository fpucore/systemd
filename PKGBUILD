# Maintainers: Chris McGimpsey-Jones <chrisjones.unixmen@gmail.com>, Thorsten Toepper <atsutane-aur@freethoughts.de>
# Contributor: Yurii Kolesnykov <root@yurikoles.com>
# Based on core/systemd by Christian Hesse <mail@eworm.de>

pkgbase=systemd
pkgname=('systemd'
         'systemd-libs'
         'systemd-resolvconf'
         'systemd-sysvcompat'
         'systemd-tests'
         'systemd-ukify')
pkgdesc='Patched and repackaged systemd for GNU Operating System / H-Linux.'
pkgver=263.2
pkgrel=4
arch=('x86_64')
license=('LGPL-2.1-or-later')
url='https://www.freedompublishersunion.net/h-linux.html'
makedepends=('acl' 'apparmor' 'cryptsetup' 'docbook-xsl' 'gperf' 'lz4' 'xz' 'pam' 'libelf'
             'intltool' 'iptables' 'kmod' 'libarchive' 'libcap' 'libidn2' 'libgcrypt'
             'libmicrohttpd' 'libxcrypt' 'libxslt' 'util-linux' 'linux-api-headers'
             'python-jinja' 'python-lxml' 'quota-tools' 'shadow' 'git'
             'meson' 'libseccomp' 'pcre2' 'audit' 'kexec-tools' 'libxkbcommon'
             'bash-completion' 'p11-kit' 'systemd' 'libfido2' 'tpm2-tss' 'rsync'
             'bpf' 'libbpf' 'clang' 'llvm' 'curl' 'gnutls' 'python-pyelftools'
             'libpwquality' 'qrencode' 'lib32-gcc-libs' 'python-pefile' 'ccache')
conflicts=("mkinitcpio<38-1")
replaces=('systemd' 'systemd-libs' 'systemd-resolvconf' 'systemd-sysvcompat' 'systemd-tests' 'systemd-ukify' 'systemd-git' 'systemd-libs-git' 'systemd-resolvconf-git' 'systemd-sysvcompat-git' 'systemd-tests-git' 'systemd-ukify-git')
options=('!strip')
source=(
#"$pkgbase-stable::git+https://github.com/systemd/systemd"
        '0001-Use-Arch-Linux-device-access-groups.patch'
        # bootloader files
        'arch.conf'
        'loader.conf'
        'splash-arch.bmp'::'https://gitlab.archlinux.org/archlinux/packaging/packages/systemd/-/raw/main/splash-arch.bmp'
        # pam configuration
        'systemd-user.pam'
        # pacman / libalpm hooks
        'systemd-hook'
        '20-systemd-sysusers.hook'
        '30-systemd-binfmt.hook'
        '30-systemd-catalog.hook'
        '30-systemd-daemon-reload-system.hook'
        '30-systemd-daemon-reload-user.hook'
        '30-systemd-hwdb.hook'
        '30-systemd-restart-marked.hook'
        '30-systemd-sysctl.hook'
        '30-systemd-tmpfiles.hook'
        '30-systemd-udev-reload.hook'
        '30-systemd-update.hook')
sha512sums=('SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP')

# Version schema should be declared by initial declaration only without git additions
#pkgver() {
#  cd "$pkgbase-stable"
  # Upstream versioning is incompatible with pacman's version comparisons, one
  # way or another. So we replace dashes and tildes to make sure pacman's
  # version comparing does the right thing for rc versions:
#  local _major=`sed 's/~/./g' meson.version`
#  printf "%s.r%s.%s" "${_major}" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
#}

prepare() {
  cd "${pkgbase}-stable"

  # Replace cdrom/dialout/tape groups with optical/uucp/storage
  patch -Np1 -i ../0001-Use-Arch-Linux-device-access-groups.patch
}

build() {
  local _timeservers=({0..3}.arch.pool.ntp.org)
  local _nameservers=(
    #  * Quad9, primary
    '9.9.9.9#dns.quad9.net'
    '2620:fe::9#dns.quad9.net'
    #  * Cloudflare, secondary
    '1.1.1.1#cloudflare-dns.com'
    '2606:4700:4700::1111#cloudflare-dns.com'
  )

local _meson_options=(
    -Dwerror=false
    -Dc_args="-Wno-error=shadow"
    -Dversion-tag="${pkgver}-${pkgrel}"
    -Dvcs-tag=true
    -Dshared-lib-tag="${pkgver}-${pkgrel}"
    -Dmode=developer

    -Dapparmor=enabled
    -Dbootloader=enabled
    -Dxenctrl=disabled
    -Dbpf-framework=enabled
    -Dima=false

    -Dinstall-tests=false
    #  Kill switch for test binary compilation
    -Dtests=false
    
    -Dlibidn2=enabled
    -Dlz4=enabled
    -Dman=enabled
    -Dselinux=disabled
    -Dsshdprivsepdir=/usr/share/empty.sshd
    -Dvmlinux-h=provided
    -Dvmlinux-h-path=/usr/src/linux/vmlinux.h

    -Ddbuspolicydir=/usr/share/dbus-1/system.d
    -Ddefault-dnssec=no
    -Ddefault-kill-user-processes=false
    -Ddefault-locale='C.UTF-8'
    -Dlocalegen-path=/usr/bin/locale-gen
    -Ddns-over-tls=openssl
    -Dfallback-hostname='h-linux'
    -Dnologin-path=/usr/bin/nologin
    -Dntp-servers="${_timeservers[*]}"
    -Ddns-servers="${_nameservers[*]}"
    -Drpmmacrosdir=no

    -Dsbat-distro='h-linux'
    -Dsbat-distro-summary='Patched and repackaged.'
    -Dsbat-distro-pkgname="${pkgname}"
    -Dsbat-distro-version="${pkgver}"
    -Dsbat-distro-url="https://www.freedompublishersunion.net/h-linux.html"

    # The graveyard of temporary fixes and patches
    -Dtpm2=disabled
    -Dlibarchive=disabled
    -Drepart=disabled
    -Dsysupdate=disabled
  )

  export CC="ccache gcc"
  export CXX="ccache g++"
  
  arch-meson "${pkgbase}-stable" build "${_meson_options[@]}"

  #meson compile -C build --verbose <<< debug option
  meson compile -C build

  msg2 "Compiling sysd - Service Manager Interface..."

  ccache gcc \
    ${CPPFLAGS} \
    ${CFLAGS} \
    ${LDFLAGS} \
    -o "$srcdir/sysd" \
    "$srcdir/${pkgbase}-stable/utils/sysd.c"
}

check() {
  meson test -C build --print-errorlogs
}

package_systemd() {
  pkgdesc='system and service manager'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  license+=(
    'CC0-1.0' # siphash
    'GPL-2.0-or-later' # udev
    'MIT-0' # documentation and config files
  )
  # Not all libs are linked, but opened via dlopen()
  depends=("systemd-libs=${pkgver}"
           'acl' 'libacl.so' 'bash' 'cryptsetup' 'libcryptsetup.so' 'dbus'
           'dbus-units' 'kbd' 'kmod' 'hwdata' 'libcap' 'libcap.so'
           'libgcrypt' 'libxcrypt' 'libcrypt.so' 'libidn2' 'lz4' 'pam'
           'libelf' 'libseccomp' 'libseccomp.so' 'util-linux' 'libblkid.so'
           'libmount.so' 'xz' 'pcre2' 'audit' 'libaudit.so'
           'openssl' 'libcrypto.so' 'libssl.so')
  provides=('nss-myhostname' "systemd-tools=${pkgver}" "udev=${pkgver}")
  provides+=("systemd=${pkgver}")
  replaces=('nss-myhostname' 'systemd-tools' 'udev')
  conflicts=('nss-myhostname' 'systemd-tools' 'udev')
  conflicts+=('systemd')
  optdepends=('libmicrohttpd: systemd-journal-gatewayd and systemd-journal-remote'
              'apparmor: additional security features'
              'quota-tools: kernel-level quota management'
              'systemd-sysvcompat: symlink package to provide sysvinit binaries'
              "systemd-ukify=${pkgver}: combine kernel and initrd into a signed Unified Kernel Image"
              'polkit: allow administration as unprivileged user'
              'curl: systemd-journal-upload, machinectl pull-tar and pull-raw'
              'gnutls: systemd-journal-gatewayd and systemd-journal-remote'
              'qrencode: show QR codes'
              'iptables: firewall features'
              'libarchive: convert DDIs to tarballs'
              'libbpf: support BPF programs'
              'libpwquality: check password quality'
              'libfido2: unlocking LUKS2 volumes with FIDO2 token'
              'libp11-kit: support PKCS#11'
              'tpm2-tss: unlocking LUKS2 volumes with TPM2')
  backup=(etc/systemd/coredump.conf
          etc/systemd/homed.conf
          etc/systemd/journald.conf
          etc/systemd/journal-remote.conf
          etc/systemd/journal-upload.conf
          etc/systemd/logind.conf
          etc/systemd/networkd.conf
          etc/systemd/oomd.conf
          etc/systemd/pstore.conf
          etc/systemd/resolved.conf
          etc/systemd/sleep.conf
          etc/systemd/system.conf
          etc/systemd/timesyncd.conf
          etc/systemd/user.conf
          etc/udev/iocost.conf
          etc/udev/udev.conf)
  install=systemd.install

  meson install -C build --no-rebuild --destdir "${pkgdir}"

  # a ghost dir which is unused but necessary for the build to succeed
  mkdir -p "$pkgdir/usr/lib/systemd/tests"

  # we'll create this on installation
  rmdir "$pkgdir"/var/log/journal/remote

  # runtime libs shipped with systemd-libs
  install -d -m0755 systemd-libs/lib/
  mv "$pkgdir"/usr/lib/lib{nss,systemd,udev}*.so* systemd-libs/lib/
  mv "$pkgdir"/usr/lib/pkgconfig systemd-libs/lib/pkgconfig
  mv "$pkgdir"/usr/include systemd-libs/include
  mv "$pkgdir"/usr/share/man/man3 systemd-libs/man3

  # ukify shipped in separate package
  install -d -m0755 systemd-ukify/{bin,systemd,man1,install.d}
  mv "$pkgdir"/usr/bin/ukify systemd-ukify/bin/
  mv "$pkgdir"/usr/lib/systemd/ukify systemd-ukify/systemd/
  mv "$pkgdir"/usr/share/man/man1/ukify.1 systemd-ukify/man1/
  # we move the ukify hook itself, but keep 90-uki-copy.install in place,
  # because there are other ways to generate UKIs w/o ukify, e.g. w/ mkinitcpio
  mv "$pkgdir"/usr/lib/kernel/install.d/60-ukify.install systemd-ukify/install.d

  # manpages shipped with systemd-sysvcompat
  rm "$pkgdir"/usr/share/man/man8/{halt,poweroff,reboot,shutdown}.8

  # executable (symlinks) shipped with systemd-sysvcompat
  rm "$pkgdir"/usr/bin/{halt,init,poweroff,reboot,shutdown}

  # files shipped with systemd-resolvconf
  rm "$pkgdir"/usr/{bin/resolvconf,share/man/man1/resolvconf.1}

  # tests shipped with systemd-tests (for upstream)
  install -d -m0755 systemd-tests/
  mv "$pkgdir"/usr/lib/systemd/tests systemd-tests/

  # avoid a potential conflict with [core]/filesystem
  rm "$pkgdir"/usr/share/factory/etc/{issue,nsswitch.conf}
  sed -i -e '/^C \/etc\/nsswitch\.conf/d' \
    -e '/^C \/etc\/issue/d' "$pkgdir"/usr/lib/tmpfiles.d/etc.conf

  # ship default policy to leave services disabled
  echo 'disable *' >"$pkgdir"/usr/lib/systemd/system-preset/99-default.preset

  # The group 'systemd-journal' is allocated dynamically and may have varying
  # gid on different systems. Let's install with gid 0 (root), systemd-tmpfiles
  # will fix the permissions for us. (see /usr/lib/tmpfiles.d/systemd.conf)
  install -d -o root -g root -m 2755 "$pkgdir"/var/log/journal

  # add example bootctl configuration
  install -D -m0644 arch.conf "$pkgdir"/usr/share/systemd/bootctl/arch.conf
  install -D -m0644 loader.conf "$pkgdir"/usr/share/systemd/bootctl/loader.conf
  install -D -m0644 splash-arch.bmp "$pkgdir"/usr/share/systemd/bootctl/splash-arch.bmp

  # pacman hooks
  install -D -m0755 systemd-hook "$pkgdir"/usr/share/libalpm/scripts/systemd-hook
  install -D -m0644 -t "$pkgdir"/usr/share/libalpm/hooks *.hook

  # sysd service manager interface
  install -D -m0755 "$srcdir/sysd" "$pkgdir/usr/bin/sysd"

  # overwrite the systemd-user PAM configuration with our own
  install -D -m0644 systemd-user.pam "$pkgdir"/usr/lib/pam.d/systemd-user

  # create a directory for cryptsetup keys
  install -d -m0700 "$pkgdir"/etc/cryptsetup-keys.d

  # handle uncommon license
  install -d -m0755 "$pkgdir/usr/share/licenses/$pkgbase"
  ln -s -t "$_" /usr/share/doc/systemd/LICENSES/MIT-0.txt
}

package_systemd-libs() {
  pkgdesc='systemd client libraries'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  depends=('glibc' 'gcc-libs' 'libcap' 'libgcrypt' 'lz4' 'xz' 'zstd')
  license+=(
    'CC0-1.0' # siphash
    'GPL-2.0-or-later WITH Linux-syscall-note' # src/basic/linux/*
  )
  provides=('libsystemd' 'libsystemd.so' 'libudev.so')
  provides+=("systemd-libs=${pkgver}")
  conflicts=('libsystemd')
  conflicts+=('systemd-libs')
  replaces=('libsystemd')

  install -d -m0755 "$pkgdir"/usr/share/man
  mv systemd-libs/lib "$pkgdir"/usr/lib || true
  mv systemd-libs/include "$pkgdir"/usr/include || true
  mv systemd-libs/man3 "$pkgdir"/usr/share/man/man3 || true
}

package_systemd-resolvconf() {
  pkgdesc='systemd resolvconf replacement (for use with systemd-resolved)'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  depends=("systemd=${pkgver}")
  provides=('openresolv' 'resolvconf')
  provides+=("systemd-resolvconf=${pkgver}")
  conflicts=('resolvconf')
  conflicts+=('systemd-resolvconf')

  install -d -m0755 "$pkgdir"/usr/bin
  ln -s resolvectl "$pkgdir"/usr/bin/resolvconf

  install -d -m0755 "$pkgdir"/usr/share/man/man1
  ln -s resolvectl.1.gz "$pkgdir"/usr/share/man/man1/resolvconf.1.gz
}

package_systemd-sysvcompat() {
  pkgdesc='sysvinit compat for systemd'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  conflicts=('sysvinit')
  conflicts+=('systemd-sysvcompat')
  depends=("systemd=${pkgver}")
  provides=("systemd-sysvcompat=${pkgver}")

  install -D -m0644 -t "$pkgdir"/usr/share/man/man8 \
    build/man/{halt,poweroff,reboot,shutdown}.8

  install -d -m0755 "$pkgdir"/usr/bin
  ln -s ../lib/systemd/systemd "$pkgdir"/usr/bin/init
  for tool in halt poweroff reboot shutdown; do
    ln -s systemctl "$pkgdir"/usr/bin/$tool
  done
}

package_systemd-tests() {
  pkgdesc='systemd tests'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  conflicts=('systemd-tests')
  provides=("systemd-tests=${pkgver}")
  depends=("systemd=${pkgver}")

  install -d -m0755 "$pkgdir"/usr/lib/systemd

# Since test binaries are unused for edge builds we can skip this
#  mv systemd-tests/tests "$pkgdir"/usr/lib/systemd/tests
}

package_systemd-ukify() {
  pkgdesc='Combine kernel and initrd into a signed Unified Kernel Image'
  pkgdesc+=' Patched and repackaged systemd for GNU Operating System / H-Linux.'
  conflicts=('systemd-ukify')
  provides=('ukify')
  provides+=("systemd-ukify=$pkgver")
  depends=("systemd=${pkgver}" 'binutils' 'python-cryptography' 'python-pefile')
  optdepends=('python-pillow: Show the size of splash image'
              'sbsigntools: Sign the embedded kernel')

  install -d -m0755 "$pkgdir"/usr/{lib/kernel,share/man}
  mv systemd-ukify/bin "$pkgdir"/usr/bin
  mv systemd-ukify/systemd "$pkgdir"/usr/lib/systemd
  mv systemd-ukify/man1 "$pkgdir"/usr/share/man/man1
  mv systemd-ukify/install.d "$pkgdir"/usr/lib/kernel/install.d
}
