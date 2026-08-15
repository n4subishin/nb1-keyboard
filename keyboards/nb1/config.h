// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// ---------------------------------------------------------------------------
// Encoders
// ---------------------------------------------------------------------------
// 12 encoders share footprints with the MX switches. If a knob registers two
// steps per detent, raise this; if it registers every other detent, lower it.
// #define ENCODER_RESOLUTION 4

// Uncomment if a specific encoder spins the wrong way and you would rather
// not swap pin_a / pin_b in keyboard.json:
// #define ENCODER_DIRECTION_FLIP

// ---------------------------------------------------------------------------
// Matrix
// ---------------------------------------------------------------------------
// The three row lines (IN_1..IN_3) run through the J16 -> cable -> J17 jumper.
// That adds a little series resistance and contact bounce, so allow a slightly
// longer settle time than a fully on-board matrix would need.
#define MATRIX_IO_DELAY 30

// ---------------------------------------------------------------------------
// HSE crystal / PLL
// ---------------------------------------------------------------------------
// Y1 is a 16 MHz passive crystal. The clock tree is configured in the
// accompanying board.h and mcuconf.h:
//
//   PFD 2 MHz -> VCO 336 MHz -> SYSCLK 168 MHz, USB 48 MHz
//
// Compare against platforms/chibios/boards/GENERIC_STM32_F405XG/configs/ and
// delete those two files if the defaults already match.
