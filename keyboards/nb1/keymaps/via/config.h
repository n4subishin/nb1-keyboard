// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// ---------------------------------------------------------------------------
// Wear-leveling sizing for the STM32F405RG
//
// Flash layout on this part: sectors 0-3 are 16 kB, sector 4 is 64 kB, and
// sectors 5-11 are 128 kB each, totalling 1 MB. The firmware occupies only the
// first few sectors, so the last 128 kB sector is free to use as the EEPROM
// backing store.
//
// BACKING_SIZE must be a whole number of erase sectors, hence 128 kB. The
// LOGICAL_SIZE is what QMK exposes as EEPROM, and every wear-leveling driver
// reserves that much RAM -- so keep it small. 2 kB comfortably covers VIA's
// 1 kB minimum plus the dynamic keymap for 4 layers x 12 keys x 2 bytes and
// the encoder map, while costing only 2 kB of the 192 kB of RAM.
//
// If a remap does not survive an unplug, these three values are the first
// thing to revisit.
// ---------------------------------------------------------------------------

#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE 131072
#define WEAR_LEVELING_EFL_FIRST_SECTOR 11

// Four layers is VIA's default and is plenty for a 12-key board. Raising this
// costs EEPROM, so only increase it alongside WEAR_LEVELING_LOGICAL_SIZE.
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
