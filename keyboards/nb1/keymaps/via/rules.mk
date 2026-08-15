VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# ---------------------------------------------------------------------------
# EEPROM persistence -- REQUIRED, do not remove
#
# VIA/Remap store the user's keymap in EEPROM. The STM32F405 has no real
# EEPROM, and QMK's flash emulation only covers STM32F3xx/F1xx/F072xB natively
# (the "legacy" driver covers F0xx and F4x1 -- note F4x1, not our F4x5). Any
# other chip falls back to the "transient" driver, which is a fake EEPROM in
# RAM: every remap the customer makes would vanish the moment they unplug the
# board. Setting the driver explicitly is what makes their changes stick.
# ---------------------------------------------------------------------------
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash
