#!/bin/bash

# systemd package installer
# Patched and repackaged systemd for GNU Operating System / H-Linux.

set -e

echo "==> Compiling and installing systemd..."
echo ""

makepkg -seCfi

echo ""
echo "==> systemd compile and install procedures complete."
echo "Please reboot your system!"
echo ""
