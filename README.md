# Nb.1

*[日本語版はこちら / Japanese version](README.ja.md)*

A 12-position programmable macropad. Every position accepts **either a Cherry MX
compatible switch or a rotary encoder** — the two share a single footprint, so
you can build it as twelve keys, twelve knobs, or any mix in between. One
firmware build covers every variant.

| | |
|---|---|
| MCU | STM32F405RGT6 (Cortex-M4F, 168 MHz, 1 MB Flash, 192 KB RAM) |
| Matrix | 3 rows × 4 columns, COL2ROW |
| Encoders | Up to 12, wired directly to GPIO |
| Connection | USB Type-C, USB 2.0 Full Speed |
| Firmware | QMK Firmware (ChibiOS) |
| Configurator | Remap / VIA |

---

## Changing the keymap

No programming required — everything happens in the browser.

1. Open https://remap-keys.app/ in **Chrome or Edge**
   (Firefox and Safari do not implement WebHID and will not connect)
2. Choose **Customize your keyboard** and connect Nb.1
3. Drag and drop keycodes onto the positions you want to change
4. Press **flash**

Click a knob to set its clockwise and counter-clockwise actions separately.

Until Nb.1 is listed in the Remap catalog, load
[`Nb1_remap_definition.json`](Nb1_remap_definition.json) into Remap first.

---

## Building the firmware

You need a working QMK environment. See the
[QMK setup guide](https://docs.qmk.fm/newbs_getting_started) if you don't have one.

```sh
git clone https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
qmk setup

# Drop this repository's keyboard directory into the QMK tree
cp -r /path/to/nb1-keyboard/keyboards/nb1 keyboards/

qmk compile -kb nb1 -km via
```

Two keymaps are provided. `default` is plain QMK; `via` adds Remap/VIA support
and is what ships on the board.

### Clock configuration

Y1 is a **16 MHz** crystal. QMK's `GENERIC_STM32_F405XG` board assumes 12 MHz,
so `board.h` and `mcuconf.h` override it:

```
PFD 2 MHz -> VCO 336 MHz -> SYSCLK 168 MHz, USB 48 MHz
```

**Deleting those two files breaks USB entirely** — the USB clock would land at
64 MHz instead of the required 48 MHz, and the core would run at 224 MHz, well
past its 168 MHz limit.

### EEPROM persistence

The STM32F405 has no real EEPROM, and QMK's flash emulation does not cover this
part by default, so it would silently fall back to a RAM-backed fake EEPROM and
lose every remap on unplug. `keymaps/via/rules.mk` selects the wear-leveling
driver explicitly to prevent that. Do not remove those lines.

---

## Flashing

Two ways into the bootloader:

**Keycode** — hold position 12 (bottom right) to reach layer 1, then press
position 1. That is `QK_BOOT` in the shipped keymap.

**BOOT0 button** — unplug USB, hold the BOOT0 button on the PCB, plug USB back
in. This works even when the firmware does not boot at all.

```sh
qmk flash -kb nb1 -km via
```

---

## Hardware

| | |
|---|---|
| PCB | 96.72 × 95.00 mm, 2 layer |
| Key pitch | 19.2 mm |
| Switches | Cherry MX compatible, Kailh hotswap sockets |
| Encoders | Alps EC12E2440301 (24 detent / 24 pulse, no push switch) |
| Crystal | 16 MHz, CL = 20 pF, HC-49/S |

Full details in [`docs/SPECIFICATION.md`](docs/SPECIFICATION.md).

### Known limitations

- **No SWD header.** Debugging requires soldering directly to MCU pins 46 and 49.
- **No reset button.** Can be retrofitted by adding a tactile switch in parallel
  with C8.
- **Matrix rows pass through the J16–J17 cable.** If that cable is disconnected,
  no key responds at all while the encoders keep working. This is the first
  thing to check when keys go dead.
- **The encoders have no push switch,** so a position fitted with an encoder
  responds to rotation only.

### JTAG pins

PA15 (JTDI), PB3 (JTDO) and PB4 (NJTRST) are used for the indicator LED and for
matrix row 3 / column 1. The board is SWD-only by design; a JTAG probe will not
work.

---

## License

Based on QMK Firmware, so this project is **GPL v2**. See [`LICENSE`](LICENSE).

USB VID `0x1209` is allocated by [pid.codes](https://pid.codes/) for open source
hardware. Projects using it must be released under a recognised open source
license, which this repository satisfies.
