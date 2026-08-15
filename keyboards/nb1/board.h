// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

// ---------------------------------------------------------------------------
// Y1 = HUSG-16.000-20, 16 MHz, HC-49/S, CL = 20 pF (matches C9/C10 = 30 pF).
//
// Check platforms/chibios/boards/GENERIC_STM32_F405XG/configs/board.h first.
// If STM32_HSECLK is already 16000000 there, delete this file.
// ---------------------------------------------------------------------------

#undef STM32_HSECLK
#define STM32_HSECLK 16000000U

// Passive crystal, not an active oscillator, so bypass mode stays off.
#undef STM32_HSE_BYPASS
