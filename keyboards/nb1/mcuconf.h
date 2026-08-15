// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// ---------------------------------------------------------------------------
// PLL configuration for a 16 MHz HSE crystal.
//
//   PFD    = HSE / PLLM  = 16 / 8   =   2 MHz   (ST recommends 2 MHz)
//   VCO    = PFD * PLLN  =  2 * 168 = 336 MHz   (must be 100..432 MHz)
//   SYSCLK = VCO / PLLP  = 336 / 2  = 168 MHz   (F405 maximum)
//   USB    = VCO / PLLQ  = 336 / 7  =  48 MHz   (must be exactly 48 MHz)
//
// Check platforms/chibios/boards/GENERIC_STM32_F405XG/configs/mcuconf.h first.
// If these values already match, delete this file.
// ---------------------------------------------------------------------------

#undef STM32_HSE_ENABLED
#define STM32_HSE_ENABLED TRUE

#undef STM32_PLLSRC
#define STM32_PLLSRC STM32_PLLSRC_HSE

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 168

#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE 2

#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE 7

// SYSCLK source and bus prescalers: 168 / 42 / 84 MHz.
#undef STM32_SW
#define STM32_SW STM32_SW_PLL

#undef STM32_HPRE
#define STM32_HPRE STM32_HPRE_DIV1

#undef STM32_PPRE1
#define STM32_PPRE1 STM32_PPRE1_DIV4

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV2

// USB OTG FS runs from the PLLQ output.
#undef STM32_CK48MSEL
#define STM32_CK48MSEL STM32_CK48MSEL_PLL
