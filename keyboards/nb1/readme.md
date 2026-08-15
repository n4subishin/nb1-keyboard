# original_keyboard

A 12-position programmable input device built around an STM32F405RGT6.
Every position takes either a Cherry MX compatible switch (on a Kailh hotswap
socket) or a rotary encoder — the two share a single footprint, so the build
can be all keys, all encoders, or any mix. One firmware covers every variant.

* Keyboard maintainer: you
* Hardware supported: original_keyboard rev 1.0
* Hardware availability: self-made

## Layout

```
       col1   col2   col3   col4
 row1 [  1 ] [  2 ] [  3 ] [  4 ]
 row2 [  5 ] [  6 ] [  7 ] [  8 ]
 row3 [  9 ] [ 10 ] [ 11 ] [ 12 ]
```

Matrix position `[row, col]` and encoder index share the same physical spot:
encoder index = `row * 4 + col`.

## Building

```sh
qmk compile -kb original_keyboard -km default
```

## Flashing

```sh
qmk flash -kb original_keyboard -km default
```

Two ways to enter the bootloader:

* **Keycode** — hold position 9, press position 1 (`QK_BOOT` on the FN layer)
* **Hardware** — hold the BOOT0 button while plugging in USB

## Clock configuration

Y1 is a 16 MHz crystal (HUSG-16.000-20, CL = 20 pF). `board.h` and `mcuconf.h`
override the generic F405 board defaults:

```
PFD 2 MHz -> VCO 336 MHz -> SYSCLK 168 MHz, USB 48 MHz
```

Check `platforms/chibios/boards/GENERIC_STM32_F405XG/configs/` first — if the
defaults already match, delete both files.

## Notes

* PA15, PB3 and PB4 are JTAG pins at reset (JTDI / JTDO / NJTRST) and are used
  here for the indicator LED, matrix row 3 and matrix column 1. SWD-only debug
  is required; a JTAG probe will not work.
* The three matrix rows run through the J16 → cable → J17 jumper. If no key
  responds but the encoders do, check that cable first.
