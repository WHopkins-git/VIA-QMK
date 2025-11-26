# MCU name
MCU = WB32F3G71
BOARD = WB32_F3G71xx

# Bootloader selection
BOOTLOADER = wb32-dfu

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = no      # Enable RGB matrix (optional)

# VIA Support
VIA_ENABLE = yes

# Optimize size
LTO_ENABLE = yes
