# Building the Neo65 Tri-Mode Firmware

This guide explains how to compile the QMK firmware for the Neo65 Tri-Mode keyboard.

## Prerequisites

You need:
- **QMK Toolbox** (for flashing) OR
- **QMK Build Environment** (for compiling from source)

---

## Option 1: Quick Build with QMK Toolbox (Recommended for Most Users)

### Step 1: Set Up QMK Environment

```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Setup QMK (first time only)
qmk setup

# Alternatively, clone QMK manually:
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

### Step 2: Copy Keyboard Files

```bash
# Copy the Neo65 keyboard directory into QMK
cp -r /path/to/VIA-QMK/keyboards/neo ~/qmk_firmware/keyboards/
```

### Step 3: Compile the Firmware

```bash
# For VIA-enabled firmware (recommended):
qmk compile -kb neo/neo65_trimode -km via

# For default firmware:
qmk compile -kb neo/neo65_trimode -km default

# Using make instead:
cd ~/qmk_firmware
make neo/neo65_trimode:via
```

### Step 4: Flash the Firmware

The compiled firmware will be in:
```
~/qmk_firmware/neo_neo65_trimode_via.bin
```

**To Flash:**
1. Download [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
2. Open the `.bin` file in QMK Toolbox
3. Hold `ESC` while plugging in your keyboard (bootloader mode)
4. Click "Flash" in QMK Toolbox

---

## Option 2: Manual Build (Advanced)

### Requirements

- **GCC ARM Embedded Toolchain** (arm-none-eabi-gcc)
- **Make**
- **Git**
- **Python 3.7+**

### Ubuntu/Debian Installation

```bash
sudo apt-get update
sudo apt-get install -y \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    avr-libc \
    dfu-util \
    dfu-programmer \
    make \
    git \
    python3 \
    python3-pip

python3 -m pip install --user qmk
```

### macOS Installation

```bash
brew install qmk/qmk/qmk
brew install --cask qmk-toolbox

# Or install dependencies manually:
brew tap osx-cross/arm
brew install arm-gcc-bin
brew install avrdude
brew install dfu-util
```

### Windows Installation

1. Install [QMK MSYS](https://msys.qmk.fm/)
2. Open QMK MSYS terminal
3. Run: `qmk setup`

---

## Build Output Files

After successful compilation, you'll get:

| File | Description |
|------|-------------|
| `neo_neo65_trimode_via.bin` | VIA firmware (recommended) |
| `neo_neo65_trimode_via.elf` | Debug symbols |
| `neo_neo65_trimode_default.bin` | Default firmware |

**File Size:** Approximately 50-80KB (WB32F3G71 has 256KB flash)

---

## Flashing Methods

### Method 1: QMK Toolbox (GUI - Easiest)

1. Download from [github.com/qmk/qmk_toolbox/releases](https://github.com/qmk/qmk_toolbox/releases)
2. Open QMK Toolbox
3. Select the `.bin` file
4. Enter bootloader: Hold `ESC` + plug in USB
5. QMK Toolbox should show "WB32 DFU device connected"
6. Click **Flash**

### Method 2: Command Line (dfu-util)

```bash
# Enter bootloader mode first (hold ESC while plugging in)

# Flash using dfu-util
dfu-util -d 342D:DFA0 -a 0 -s 0x08000000:leave -D neo_neo65_trimode_via.bin

# Verify:
dfu-util -d 342D:DFA0 -a 0 -s 0x08000000 -U verify.bin
```

### Method 3: QMK CLI Flash

```bash
qmk flash -kb neo/neo65_trimode -km via
# Hold ESC when prompted
```

---

## Entering Bootloader Mode

There are **3 ways** to enter DFU bootloader:

1. **Bootmagic Lite (Recommended)**
   - Unplug the keyboard
   - Hold down `ESC` key (top-left)
   - Plug in the USB cable
   - Release `ESC` after 2 seconds

2. **Physical Reset Button**
   - Press the RESET button on the back of the PCB
   - Or short RESET to GND

3. **Keycode Method**
   - Press `QK_BOOT` if mapped in your keymap
   - Default: `Fn + ESC` (may need to be configured first)

**Verify Bootloader Mode:**
```bash
# Linux/macOS:
dfu-util -l

# Should show:
# Found DFU: [342d:dfa0] ver=0200, devnum=X, cfg=1, intf=0, path="X-X", alt=0, name="WB32 DFU Bootloader", serial="UNKNOWN"

# Windows:
# Device Manager should show "WB32-DFU" under "Universal Serial Bus devices"
```

---

## Troubleshooting

### Build Errors

#### "arm-none-eabi-gcc: command not found"
```bash
# Install ARM toolchain:
sudo apt-get install gcc-arm-none-eabi
```

#### "qmk: command not found"
```bash
# Add QMK to PATH:
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

# Or install again:
python3 -m pip install --user qmk
```

#### "Cannot open keyboards/neo/neo65_trimode"
```bash
# Ensure files are copied:
ls ~/qmk_firmware/keyboards/neo/neo65_trimode
# Should show: config.h, info.json, rules.mk, keymaps/, etc.
```

###Flash Errors

#### "No DFU capable USB device found"
- Keyboard is not in bootloader mode
- Try bootmagic (hold ESC while plugging in)
- Check USB cable (must be data cable, not charge-only)

#### "dfu-util: Cannot open DFU device 342d:dfa0"
```bash
# Linux: Add udev rules
sudo bash -c 'cat > /etc/udev/rules.d/50-qmk.rules << EOF
SUBSYSTEM=="usb", ATTR{idVendor}=="342d", ATTR{idProduct}=="dfa0", TAG+="uaccess"
EOF'
sudo udevadm control --reload-rules
sudo udevadm trigger
```

#### "Error during download get_status"
- Firmware may be too large
- Use `LTO_ENABLE = yes` in rules.mk (already enabled)
- Disable unused features

### VIA Not Detecting Keyboard

1. **Flash VIA firmware** (not default)
   ```bash
   make neo/neo65_trimode:via
   ```

2. **Load VIA JSON**
   - Open VIA → Design tab
   - Click "Load Draft Definition"
   - Select `neo65_iso_uk_625_via.json`

3. **Re-plug keyboard** after flashing

4. **Clear VIA cache**
   - Settings → "Show Design tab" → ON
   - Design → "Clear all drafts"
   - Reload JSON

---

## Firmware Customization

### Modify Keymap

Edit the keymap file:
```bash
nano ~/qmk_firmware/keyboards/neo/neo65_trimode/keymaps/via/keymap.c
```

Key references:
- `KC_TRNS` or `_______` = Transparent (inherits from layer below)
- `KC_NO` or `XXXXXXX` = No key
- `MO(1)` = Momentary layer 1 (Fn)
- `TG(1)` = Toggle layer 1

See: [QMK Keycodes](https://docs.qmk.fm/#/keycodes)

### Add RGB Matrix (If Hardware Supports)

Edit `rules.mk`:
```make
RGB_MATRIX_ENABLE = yes
WS2812_DRIVER = pwm  # or spi/bitbang depending on hardware
```

Edit `config.h`:
```c
#define RGB_MATRIX_LED_COUNT 68
#define WS2812_DI_PIN A9
```

### Enable Audio/Haptics

```make
AUDIO_ENABLE = yes
HAPTIC_ENABLE = yes
HAPTIC_DRIVER = drv2605l
```

---

## Build Optimization

### Reduce Firmware Size

In `rules.mk`:
```make
LTO_ENABLE = yes           # Link-time optimization (already enabled)
CONSOLE_ENABLE = no        # Disable debug console
COMMAND_ENABLE = no        # Disable debug commands
MOUSEKEY_ENABLE = no       # Disable mouse keys if not needed
```

### Check Firmware Size

```bash
arm-none-eabi-size neo_neo65_trimode_via.elf

# Output should show:
#   text    data     bss     dec     hex filename
#  60000    1000    8000   69000   10d28 neo_neo65_trimode_via.elf
#
# WB32F3G71 has 256KB (262144 bytes) flash - must fit in "text" section
```

---

## Useful Resources

- [QMK Documentation](https://docs.qmk.fm/)
- [QMK Configurator](https://config.qmk.fm/) (web-based keymap editor)
- [VIA Downloads](https://www.caniusevia.com/)
- [QMK Discord](https://discord.gg/qmk)
- [WB32 Platform Docs](https://github.com/qmk/qmk_firmware/tree/master/platforms/chibios/boards/GENERIC_WB32_F3G71xx)

---

## Quick Reference Card

| Task | Command |
|------|---------|
| **Setup QMK** | `qmk setup` |
| **Compile VIA** | `qmk compile -kb neo/neo65_trimode -km via` |
| **Compile Default** | `qmk compile -kb neo/neo65_trimode -km default` |
| **Flash** | `qmk flash -kb neo/neo65_trimode -km via` |
| **Enter Bootloader** | Hold `ESC` + plug USB |
| **Check Bootloader** | `dfu-util -l` |
| **Manual Flash** | `dfu-util -d 342D:DFA0 -a 0 -s 0x08000000:leave -D firmware.bin` |
| **Clean Build** | `qmk clean` |
| **Format Code** | `qmk format-c keyboards/neo/neo65_trimode` |

---

**For support, please open an issue on the [GitHub repository](https://github.com/YOUR_USERNAME/VIA-QMK).**
