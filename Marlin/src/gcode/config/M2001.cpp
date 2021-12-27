/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"
#include "../../module/printcounter.h"

#include "../../MarlinCore.h" // for startOrResumeJob

#include "../../sd/cardreader.h"
#include "../../inc/MarlinConfig.h"

static uint16_t total_samples2 = 1;
static uint16_t count_samples2 = 0;

void GcodeSuite::M2001() { //Tobbe

  //static uint16_t total_samples;
  //static uint16_t count_samples;

  if (parser.seenval('S')) { 
    total_samples2 = parser.value_int();
    //SERIAL_ECHO_MSG("Total: ", total_samples);
  }

  if (parser.seenval('C')) {  
    count_samples2 = parser.value_int();
    //SERIAL_ECHO_MSG("Count: ", count_samples);
    //SERIAL_ECHO_MSG("Total: ", total_samples);
  }
  
  if (count_samples2 > total_samples2) {
    //SERIAL_ECHO_MSG("Abort");

    if (IS_SD_PRINTING()) {
      card.abortFilePrintSoon();
    }
    else if (card.isMounted())
      card.closefile();
  }
}