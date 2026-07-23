# GNU Operating System / H-Linux
# systemd

![Systemd](http://brand.systemd.io/assets/page-logo.png)

## System and Service Manager

Patched and repackaged `systemd` for GNU Operating System / H-Linux.

This build is based on upstream systemd, with a brand new `sysd Service Manager Interface`, patches applied, packaging improvements, and H-Linux-specific integration.

---

## Complete Removal of birthDate Registration Fields

This package permanently removes the `birthDate` registration fields from the systemd introduced for age-verification related workflows.

The removal is performed at the source code level.

The affected fields are not secretly disabled, hidden, or filtered at runtime — they have been **permanently removed** from this repackaged build.

The issue has been a subject of heated discussion within the Linux and systemd communities, particularly around questions of operating system scope, privacy, metadata handling, and the role of user identity records.

The goal of this patched and repackaged build of systemd is to provide a cleaner system identity model aligned with the H-Linux design philosophy, and protection of user privacy.

---

## sysd - Service Manager Interface

This build introduces **sysd**, a lightweight native service management interface.

Instead of requiring traditional systemctl syntax:

```bash
> sudo systemctl status squid.service
```

users can now interact with services through a more simplified prompt interface:

```bash
> sysd status squid
```

Examples:

```bash
  sysd start [service]
  sysd stop [service]
  sysd restart [service]
  sysd enable [service]
  sysd disable [service]
  sysd status [service]
  sysd logs [service]
  sysd failed [service]
```

Version information is available through:

```bash
> sysd version (or --version)
```

`sysd` is compiled as part of the systemd package build process and installed alongside the system manager, ensuring that the interface is always available when systemd is installed.

---

## Build & Install

This package is built specifically for:

- GNU Operating System / H-Linux (and other distributions with minimal changes needed)
- x86_64 architecture
- H-Linux ecosystem

To install:

```bash
> gh repo clone fpucore/systemd

> goto systemd

> ./INSTALL.sh
```

---

## Credits

This project is based on the upstream [systemd](https://www.github.com/systemd/systemd) project.

Upstream systemd provides the foundation for this work and is a near drop-in replacement.

Any patches, repackaging and other modifications focus on downstream integration, packaging, UX improvements, and distribution-specific requirements.

## License(s)

The systemd components remain licensed under their respective upstream licenses.

Additional components, including `sysd`, are released under the MIT License.
