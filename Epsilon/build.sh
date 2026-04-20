#!/usr/bin/env bash
set -euo pipefail

# -----------------------------
# Cross compiler environment
# -----------------------------
PREFIX="$HOME/opt/cross"
TARGET="i686-elf"
export PATH="$PREFIX/bin:$PATH"

# -----------------------------
# Checks
# -----------------------------
if ! command -v i686-elf-gcc >/dev/null 2>&1; then
    echo "[ERROR] i686-elf-gcc bulunamadı!"
    echo "PATH: $PATH"
    exit 1
fi

if ! command -v i686-elf-ld >/dev/null 2>&1; then
    echo "[ERROR] i686-elf-ld bulunamadı!"
    exit 1
fi

# -----------------------------
# Build
# -----------------------------
echo "[INFO] Cross compiler OK"
echo "[INFO] Target: $TARGET"
echo "[INFO] Build başlıyor..."

make clean || true
make all

echo "[SUCCESS] Build tamamlandı"