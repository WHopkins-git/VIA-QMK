#!/bin/bash
# Neo65 Tri-Mode Firmware Build Script

set -e

echo "========================================="
echo "Neo65 Tri-Mode QMK Firmware Builder"
echo "========================================="
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if QMK firmware directory exists
if [ ! -d "$HOME/qmk_firmware" ]; then
    echo -e "${YELLOW}QMK firmware not found. Setting up...${NC}"
    echo ""
    echo "Running: qmk setup"
    qmk setup -H "$HOME/qmk_firmware"

    if [ $? -ne 0 ]; then
        echo -e "${RED}Failed to setup QMK. Please install QMK CLI first:${NC}"
        echo "  python3 -m pip install --user qmk"
        exit 1
    fi
fi

# Copy keyboard files to QMK
echo -e "${GREEN}Copying Neo65 keyboard files to QMK...${NC}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cp -r "$SCRIPT_DIR/keyboards/neo" "$HOME/qmk_firmware/keyboards/"

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Files copied successfully${NC}"
else
    echo -e "${RED}✗ Failed to copy files${NC}"
    exit 1
fi

# Determine keymap (default to 'via')
KEYMAP="${1:-via}"

echo ""
echo -e "${GREEN}Building firmware with keymap: ${KEYMAP}${NC}"
echo ""

# Change to QMK directory
cd "$HOME/qmk_firmware"

# Compile firmware
echo "Running: qmk compile -kb neo/neo65_trimode -km $KEYMAP"
qmk compile -kb neo/neo65_trimode -km "$KEYMAP"

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}=========================================${NC}"
    echo -e "${GREEN}✓ BUILD SUCCESSFUL!${NC}"
    echo -e "${GREEN}=========================================${NC}"
    echo ""
    echo "Firmware file:"
    FIRMWARE_FILE="$HOME/qmk_firmware/neo_neo65_trimode_${KEYMAP}.bin"
    if [ -f "$FIRMWARE_FILE" ]; then
        echo -e "  ${GREEN}$FIRMWARE_FILE${NC}"
        echo ""
        echo "File size: $(du -h "$FIRMWARE_FILE" | cut -f1)"
        echo ""
        echo "Next steps:"
        echo "  1. Enter bootloader mode (hold ESC while plugging in USB)"
        echo "  2. Flash using QMK Toolbox or:"
        echo "     dfu-util -d 342D:DFA0 -a 0 -s 0x08000000:leave -D $FIRMWARE_FILE"
    else
        echo -e "${YELLOW}Warning: Firmware file not found at expected location${NC}"
        echo "Check: $HOME/qmk_firmware/.build/"
    fi
else
    echo ""
    echo -e "${RED}=========================================${NC}"
    echo -e "${RED}✗ BUILD FAILED${NC}"
    echo -e "${RED}=========================================${NC}"
    echo ""
    echo "Please check the error messages above"
    echo "Common issues:"
    echo "  - Missing arm-none-eabi-gcc toolchain"
    echo "  - QMK submodules not initialized"
    echo "  - Configuration errors in keyboard files"
    exit 1
fi
