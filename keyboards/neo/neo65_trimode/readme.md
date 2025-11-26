# Neo65 Tri-Mode

![Neo65 Tri-Mode](https://i.imgur.com/placeholder.png)

A 65% ISO-UK keyboard with tri-mode connectivity (USB, Bluetooth, 2.4GHz).

## Hardware Specifications

* **Keyboard Maintainer:** [Neo Keyboards](https://github.com/neo)
* **Hardware Supported:** Neo65 Tri-Mode PCB (WB32F3G71 MCU)
* **Hardware Availability:** [Neo Keyboards](https://neokeys.com)
* **Layout:** ISO-UK with split backspace and 6.25U spacebar
* **Bootloader:** WB32-DFU (VID: 0x342D, PID: 0xDFA0)
* **MCU Chip ID:** 0x3A50E980

## Features

* **VIA Support:** Fully compatible with VIA Configurator
* **Bootmagic Lite:** Hold ESC while plugging in to enter bootloader
* **N-Key Rollover (NKRO):** Full NKRO support enabled
* **ISO-UK Layout:** True ISO enter and UK-specific key positions
* **Split Backspace:** Two 1U keys in backspace position
* **Fn Layer:** Function key located left of Alt (as printed on PCB)

## Building Firmware

Make sure you have [QMK Firmware](https://github.com/qmk/qmk_firmware) set up and configured.

### Compile the firmware:

```bash
qmk compile -kb neo/neo65_trimode -km via
```

Or using make:

```bash
make neo/neo65_trimode:via
```

### Flash the firmware:

```bash
qmk flash -kb neo/neo65_trimode -km via
```

## Entering Bootloader Mode

There are 3 ways to enter the bootloader:

1. **Bootmagic reset:** Hold down ESC key while plugging in the USB cable
2. **Physical reset button:** Press the reset button on the back of the PCB
3. **Keycode in layout:** Press the key mapped to `QK_BOOT` (typically Fn+Esc in default layout)

## VIA Configuration

1. Download and install [VIA](https://www.caniusevia.com/)
2. Load the `neo65_iso_uk_625_via.json` file in VIA (Design tab → Load Draft Definition)
3. Your keyboard should be automatically detected
4. Customize your layout and layers as needed

## Layer Information

### Layer 0 (Base Layer)
Standard ISO-UK layout with split backspace:
- Esc, numbers, split backspace, Delete
- Tab, QWERTY, ISO Enter, Page Up
- Caps Lock, home row, Page Down
- Shift (1.25U), backslash, ZXCVBNM, Shift (1.75U), Up, End
- Ctrl, Win, Alt, **Fn**, Space (6.25U), Alt, Win, Left, Down, Right

### Layer 1 (Function Layer)
Activated by holding the Fn key:
- F1-F12, Insert
- Print Screen, Home
- End
- Media controls (Mute, Vol-, Vol+), Page Up
- Menu key, Home, Page Down, End

### Layers 2-3
Available for custom configuration via VIA

## Pin Configuration

### Matrix Pins:
- **Rows:** B12, B13, B14, B15, A8
- **Columns:** B11, B10, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0, C15, C14, C13

### Matrix Layout:
```
     0    1    2    3    4    5    6    7    8    9   10   11   12   13   14
  ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
0 │Esc │ 1  │ 2  │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 0  │ -  │ =  │Bsp │Bsp │
  ├────┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴──┬─┴────┤
1 │Tab    │ Q  │ W  │ E  │ R  │ T  │ Y  │ U  │ I  │ O  │ P  │ [  │ ]  │Enter │
  ├───────┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┬───┴┐     │
2 │Caps    │ A  │ S  │ D  │ F  │ G  │ H  │ J  │ K  │ L  │ ;  │ '  │ #  │     │
  ├──────┬─┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴─┬──┴────┴─────┤
3 │Shift │ \ │ Z  │ X  │ C  │ V  │ B  │ N  │ M  │ ,  │ .  │ /  │Shift│
  ├──────┴┬──┴──┬─┴────┴┬───┴────┴────┴────┴────┴┬───┴──┬─┴──┬──┴─────┴──────┤
4 │Ctrl   │Win  │Alt    │Space                   │Alt   │Win │
  └───────┴─────┴───────┴────────────────────────┴──────┴────┘

Additional mappings:
- 2,14: Delete (top right)
- 1,14: Page Up (right side row 1)
- 2,13: Page Down (right side row 2)
- 3,13: Up Arrow
- 3,14: End
- 4,12: Left Arrow
- 4,13: Down Arrow
- 4,14: Right Arrow
```

## License

Copyright 2025 Neo Keyboards

This firmware is released under the GPL-2.0-or-later license.

See [QMK Documentation](https://docs.qmk.fm/) for more information.
