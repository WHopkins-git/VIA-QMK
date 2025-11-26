# Neo65 Tri-Mode QMK/VIA Firmware

Complete QMK firmware and VIA configuration for the **Neo65 Tri-Mode** keyboard with ISO-UK layout.

## 🎯 Quick Start

### For Users

1. **Download the compiled firmware** from the releases page
2. **Enter bootloader mode:**
   - Hold `ESC` while plugging in the USB cable
   - Or press the reset button on the PCB
3. **Flash using QMK Toolbox:**
   - Open [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
   - Select the downloaded `.bin` file
   - Click "Flash"

### For VIA Users

1. **Install VIA:** Download from [usevia.app](https://usevia.app/) or [caniusevia.com](https://www.caniusevia.com/)
2. **Load keyboard definition:**
   - Open VIA
   - Go to the **Design** tab
   - Click **Load Draft Definition**
   - Select `neo65_iso_uk_625_via.json` from this repository
3. **Configure:** Your keyboard will be automatically detected and ready to customize

## 📁 Repository Structure

```
VIA-QMK/
├── keyboards/neo/neo65_trimode/
│   ├── config.h              # Hardware configuration
│   ├── info.json             # Keyboard metadata and layout
│   ├── rules.mk              # Build configuration
│   ├── readme.md             # Detailed documentation
│   ├── keymaps/
│   │   ├── default/
│   │   │   └── keymap.c      # Default keymap (2 layers)
│   │   └── via/
│   │       ├── keymap.c      # VIA keymap (4 layers)
│   │       └── rules.mk      # VIA-specific build rules
└── neo65_iso_uk_625_via.json # VIA definition file
```

## 🔧 Hardware Specifications

| Component | Details |
|-----------|---------|
| **MCU** | WB32F3G71 |
| **Bootloader** | WB32-DFU (VID: 0x342D, PID: 0xDFA0) |
| **Layout** | ISO-UK with split backspace |
| **Bottom Row** | 6.25U spacebar |
| **Features** | VIA, Bootmagic Lite, NKRO |
| **Connectivity** | USB wired (tri-mode capable) |

## 🔨 Building From Source

### Prerequisites

```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Setup QMK
qmk setup
```

### Compile

```bash
# Clone this repository into your QMK keyboards directory
cd ~/qmk_firmware/keyboards
git clone https://github.com/YOUR_USERNAME/VIA-QMK.git neo/neo65_trimode

# Compile VIA firmware
qmk compile -kb neo/neo65_trimode -km via

# Or compile default firmware
qmk compile -kb neo/neo65_trimode -km default
```

### Flash

```bash
# Enter bootloader mode, then:
qmk flash -kb neo/neo65_trimode -km via
```

## ⌨️ Layout Details

### Base Layer (Layer 0)
```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
│Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bs │Bs │Del│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │     │PgU│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │    │PgD│
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
│Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │End│
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
│Ctrl│Win │Alt │ Fn │      Space        │Alt │Win │ │ ← │ ↓ │ → │
└────┴────┴────┴────┴───────────────────┴────┴────┘ └───┴───┴───┘
```

### Function Layer (Layer 1 - Hold Fn)
- **F1-F12** on number row
- **Media controls:** Mute, Volume Down, Volume Up (M, <, >)
- **Navigation:** Home, End, Page Up, Page Down
- **Utilities:** Print Screen, Insert, Menu key

### Layers 2-3
Reserved for user customization via VIA.

## 🎨 VIA Configuration

The `neo65_iso_uk_625_via.json` file enables full VIA support:

- ✅ Automatic keyboard detection
- ✅ Real-time keymap editing (no reflash needed)
- ✅ 4 customizable layers
- ✅ Macro support
- ✅ Key tester
- ✅ Lighting controls (if enabled)

**Note:** VIA requires the VIA-enabled firmware to be flashed first.

## 🐛 Troubleshooting

### Keyboard not detected in VIA
1. Ensure you flashed the **VIA keymap** (`make neo/neo65_trimode:via`)
2. Load the `neo65_iso_uk_625_via.json` in VIA's Design tab
3. Try unplugging and replugging the keyboard
4. Check USB cable and try a different port

### Can't enter bootloader
1. **Bootmagic:** Hold ESC while plugging in
2. **Reset button:** Press the physical button on the PCB back
3. **Emergency:** Short the BOOT0 pin to GND while plugging in

### Build errors
1. Ensure QMK is up to date: `qmk setup`
2. Clean build files: `qmk clean`
3. Check WB32 support: `qmk doctor`

## 📜 License

This firmware is released under the **GPL-2.0-or-later** license.

Copyright 2025 Neo Keyboards

## 🤝 Contributing

Contributions are welcome! Please:

1. Fork this repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 📚 Resources

- [QMK Documentation](https://docs.qmk.fm/)
- [VIA Documentation](https://www.caniusevia.com/docs/specification)
- [QMK Discord](https://discord.gg/qmk)
- [VIA Discord](https://discord.gg/via)

## 🙏 Acknowledgments

- QMK Firmware Team
- VIA Configurator Team
- Neo Keyboards Community

---

**Made with ❤️ for the mechanical keyboard community**
