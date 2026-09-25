#!/usr/bin/env bash
set -euo pipefail

# Configuration
LVM="build/lvm"

echo "Running Test Suite..."
echo "---"
echo "Building lvm..."

# Run make
make all

# Verify the executable actually exists before running
if [[ -x "$LVM" ]]; then
    echo "# 1. Testing LVM CLI arguments..."
    
    printf "\n ====== Test 1. help ====== \n"
    ./"$LVM" --help

    printf "\n ====== Test 2. version ====== \n"
    ./"$LVM" --version

    printf "\n ====== Test 3. detailed info  ====== \n"
    ./"$LVM" -v

    printf "\n ====== Test 4. error explanation ====== \n"
    for i in {1..64}; do
        ./"$LVM"  -e="$i"
    done

    printf "# 2. Starting comprehensive test.\n"
    make test

else
    echo "Error: Executable $LVM not found or not executable." >&2
    exit 1
fi
