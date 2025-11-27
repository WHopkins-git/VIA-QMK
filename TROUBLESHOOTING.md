# Neo65 Tri-Mode Firmware Troubleshooting Guide

## 🔴 Current Issues

You're experiencing:
1. ✅ Firmware flashes successfully
2. ❌ Windows doesn't recognize key presses
3. ❌ VIA doesn't detect the keyboard
4. ❌ QMK Toolbox doesn't recognize it

## 🔧 Root Causes & Fixes

### Issue #1: Wrong USB VID/PID (FIXED)

**Problem:** The firmware was using bootloader IDs (`0x342D:0xDFA0`) instead of keyboard IDs.

**Fix Applied:**
- Changed VID to `0xFEED` (QMK community vendor)
- Changed PID to `0x6565` (unique product ID)
- Updated in: `config.h`, `info.json`, and `neo65_iso_uk_625_via.json`

**Action Required:** Recompile and reflash the firmware.

---

### Issue #2: Unknown Matrix Pin Configuration

**Problem:** Matrix pins were guessed and are likely incorrect.

**Possible Fixes:**

#### Option A: Extract Configuration from Working Firmware

If you have source code for the working firmware:

1. **Look for these files:**
   ```
   config.h
   keyboard.json
   info.json
   [keyboard_name].c
   ```

2. **Find these values:**
   ```c
   // In config.h:
   #define MATRIX_ROW_PINS { ... }
   #define MATRIX_COL_PINS { ... }
   #define DIODE_DIRECTION ...

   // Also check for:
   #define VENDOR_ID ...
   #define PRODUCT_ID ...
   ```

3. **Share the files with me** - I'll extract and apply the correct configuration.

---

#### Option B: Use QMK Console to Debug Matrix

1. **Compile the debug keymap:**
   ```bash
   qmk compile -kb neo/neo65_trimode -km debug
   ```

2. **Flash the debug firmware:**
   ```bash
   qmk flash -kb neo/neo65_trimode -km debug
   ```

3. **Open QMK Toolbox Console:**
   - Launch QMK Toolbox
   - Make sure "Console" is enabled
   - Watch for matrix scan output

4. **Press each key** and note:
   - Which keys register presses
   - Which matrix positions they report
   - Any patterns or shifts in the mapping

---

#### Option C: Common WB32 Pin Configurations

Based on similar WB32F3G71 keyboards, try these alternative pin configs:

**Configuration 1 (Current):**
```c
Rows: B12, B13, B14, B15, A8
Cols: B11, B10, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0, C15, C14, C13
```

**Configuration 2 (Alternative):**
```c
Rows: A0, A1, A2, A3, A4
Cols: A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, C13, C14, C15, A15
```

**Configuration 3 (Neo65 Variant):**
```c
Rows: B0, B1, B10, B11, B12
Cols: A0, A1, A2, A3, A4, A5, A6, A7, B13, B14, B15, C13, C14, C15, A8
```

---

### Issue #3: VIA Not Detecting Keyboard

**Why:** VIA requires keyboards to either:
1. Be in the VIA approved keyboards list, OR
2. Load a draft JSON definition

**Fixes:**

#### Fix 1: Load Draft Definition
1. Open VIA
2. Go to **Settings** → Enable "Show Design Tab"
3. Go to **Design** tab
4. Click **"Load Draft Definition"**
5. Select `neo65_iso_uk_625_via.json` from the repo
6. VIA should now detect your keyboard

#### Fix 2: Add to VIA Database (Long-term)
Submit a PR to: https://github.com/the-via/keyboards

---

## 🧪 Testing Steps

### Step 1: Test with Fixed VID/PID

```bash
# Rebuild with corrected VID/PID
./build.sh via

# Flash
qmk flash -kb neo/neo65_trimode -km via
```

**Expected Result:**
- Windows should recognize it as "Neo65 Tri-Mode"
- Device Manager should show it under "Keyboards"
- VIA should detect it after loading JSON

---

### Step 2: If Keys Still Don't Work

The matrix pins are wrong. Try:

#### Method 1: Test Alternative Pin Configs

Edit `keyboards/neo/neo65_trimode/config.h`:

```c
// Try Configuration 2
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4 }
#define MATRIX_COL_PINS { A5, A6, A7, B0, B1, B10, B11, B12, B13, B14, B15, C13, C14, C15, A15 }
```

Rebuild and test each key.

#### Method 2: Check Diode Direction

Try flipping the diode direction in `config.h`:

```c
// Try ROW2COL instead of COL2ROW
#define DIODE_DIRECTION ROW2COL
```

---

### Step 3: Analyze Working Firmware

**If you have a .bin file that works:**

1. **Check USB IDs:**
   ```bash
   # On Linux/macOS:
   lsusb
   # Look for the Neo65 keyboard and note VID:PID

   # On Windows:
   # Device Manager → Keyboards → Properties → Details → Hardware IDs
   # Look for VID_ and PID_ values
   ```

2. **Extract strings from binary:**
   ```bash
   strings working_firmware.bin | grep -i "neo\|matrix\|pin"
   ```

3. **Share the VID/PID with me** - I'll update the config.

**If you have source code:**
- Share the `config.h`, `info.json`, or any keyboard definition files
- I'll extract the exact pin configuration

---

## 🔍 Diagnostic Commands

### Check USB Recognition

**Linux:**
```bash
lsusb | grep -i "feed\|neo\|342d"
dmesg | tail -20
```

**macOS:**
```bash
system_profiler SPUSBDataType | grep -A 10 "Neo65"
```

**Windows:**
- Device Manager → View → Show Hidden Devices
- Look under "Keyboards" and "Human Interface Devices"

### Check QMK Console Output

1. Open QMK Toolbox
2. Enable "Console" checkbox
3. Plug in keyboard
4. Watch for:
   - USB initialization messages
   - Matrix scan data
   - Error messages

---

## 📊 Matrix Pin Finding Strategy

If you need to find pins from scratch:

### Physical PCB Inspection

1. **Locate the MCU** (WB32F3G71)
2. **Trace row diodes** - Follow D1, D2, D3, D4, D5
3. **Trace column lines** - Follow to MCU pins
4. **Use a multimeter** in continuity mode
5. **Refer to WB32F3G71 pinout:**
   - https://github.com/qmk/qmk_firmware/tree/master/platforms/chibios/boards/GENERIC_WB32_F3G71xx

### Software Method

Use the debug keymap with console enabled:

```bash
# Build and flash debug firmware
qmk flash -kb neo/neo65_trimode -km debug

# Open QMK Toolbox console
# Press ESC key (should be [0,0])
# If it shows different coords, matrix is shifted
```

---

## 🛠️ Quick Fix Checklist

- [ ] Rebuild with new VID/PID (`0xFEED:0x6565`)
- [ ] Flash firmware
- [ ] Check Windows Device Manager for "Neo65 Tri-Mode"
- [ ] Load VIA JSON definition
- [ ] Test if VIA detects keyboard
- [ ] Test key presses in notepad
- [ ] If keys don't work: Share working firmware files
- [ ] If keys don't work: Try alternative pin configs

---

## 📤 What to Share for Faster Debugging

**Please provide:**

1. **Working firmware files** (if you have them):
   - Source code (`config.h`, `info.json`, `[name].c`)
   - OR compiled binary (`.bin`, `.hex`)

2. **USB Information:**
   - Windows Device Manager → Properties → Hardware IDs
   - OR Linux `lsusb` output
   - OR macOS System Information → USB

3. **Keyboard behavior:**
   - Which keys (if any) produce output
   - Do LEDs respond?
   - Does Caps Lock LED work?
   - Any keys that work unexpectedly?

4. **PCB Information:**
   - PCB photos (especially MCU area)
   - Schematic if available
   - Original manufacturer firmware if available

---

## 🎯 Expected Next Steps

1. **Immediate:** Rebuild and test with fixed VID/PID
2. **If still broken:** Share working firmware config
3. **I will:** Extract correct pins and update firmware
4. **Final:** Test and verify all keys work + VIA detects

---

## 📞 Getting Help

If you're stuck:

1. **Try the fixed VID/PID first** (already done)
2. **Share the working firmware** you mentioned
3. **Run diagnostics** from this guide
4. **Provide output** from QMK Toolbox console

I'm here to help fix this! Just need the correct pin configuration from your working firmware.
