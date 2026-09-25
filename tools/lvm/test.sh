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
    
    printf "\n 1.1 Help (--help) \n"
    ./"$LVM" --help
    printf "\n ------------------------------------- \n"
    printf "\n 1.2 Version (--version) \n"
    ./"$LVM" --version
    printf "\n ------------------------------------- \n"
    printf "\n 1.3 Verbose Information (-v) \n"
    ./"$LVM" -v
    printf "\n ------------------------------------- \n"
    printf "\n 1.4 Error Code Explainations (-e=code) \n"
    for i in {1..64}; do
        ./"$LVM"  -e="$i"
    done
    printf "\n ------------------------------------- \n"
    printf "\n 1.5 No Arguments \n"
    ! ./"$LVM"
    printf "\n ------------------------------------- \n"
    printf "\n 1.6 Unknown Option \n"
    ! ./"$LVM" --unknown-option 
    printf "\n ------------------------------------- \n"



    printf "\n# 2. Starting comprehensive test.\n"
    make test
    make clean
else
    echo "Error: Executable $LVM not found or not executable." >&2
    exit 1
fi
