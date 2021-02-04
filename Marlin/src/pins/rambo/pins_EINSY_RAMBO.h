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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Einsy-Rambo pin assignments
 */

#ifndef __AVR_ATmega2560__
  #error "Oops! Select 'Arduino Mega 2560 or Rambo' in 'Tools > Board.'"
#endif

#define BOARD_INFO_NAME "Einsy Rambo"

//
// TMC2130 Configuration_adv defaults for EinsyRambo
//
#if !AXIS_DRIVER_TYPE_X(TMC2130) || !AXIS_DRIVER_TYPE_Y(TMC2130) || !AXIS_DRIVER_TYPE_Z(TMC2130) || !AXIS_DRIVER_TYPE_E0(TMC2130)
  #error "You must set ([XYZ]|E0)_DRIVER_TYPE to TMC2130 in Configuration.h for EinsyRambo."
#endif

// TMC2130 Diag Pins (currently just for reference)
#define X_DIAG_PIN                            64
#define Y_DIAG_PIN                            69
#define Z_DIAG_PIN                            68
#define E0_DIAG_PIN                           65

//
// Limit Switches
//
// Only use Diag Pins when SENSORLESS_HOMING is enabled for the TMC2130 drivers.
// Otherwise use a physical endstop based configuration.
//
// SERVO0_PIN and Z_MIN_PIN configuration for BLTOUCH sensor when combined with SENSORLESS_HOMING.
//

//#if DISABLED(SENSORLESS_HOMING)

#define X_STOP_PIN                          12
#define Y_STOP_PIN                          76 // PJ5
#define Z_STOP_PIN                          62 // PK0
#define Z_MIN_PIN                           11 // BLTouch Endstop
#define SERVO0_PIN                          10 // BLTouch Servo
#define X_MAX_PIN                           73 // conductive nozzle

#define X_STEP_PIN                            37
#define X_DIR_PIN                             49
#define X_ENABLE_PIN                          29
#define X_CS_PIN                              41

#define Y_STEP_PIN                            36
#define Y_DIR_PIN                             48
#define Y_ENABLE_PIN                          28
#define Y_CS_PIN                              39

#define Z_STEP_PIN                            35
#define Z_DIR_PIN                             47
#define Z_ENABLE_PIN                          27
#define Z_CS_PIN                              67

#define E0_STEP_PIN                           34
#define E0_DIR_PIN                            43
#define E0_ENABLE_PIN                         26
#define E0_CS_PIN                             66

#define FIL_RUNOUT_PIN                        19
// Temperature Sensors
//
#define TEMP_0_PIN                             0  // Analog Input
#define TEMP_1_PIN                             1  // Analog Input
#define TEMP_BED_PIN                           2  // Analog Input
#define TEMP_PROBE_PIN                         3  // Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN                           3
#define HEATER_BED_PIN                         4

#ifndef FAN_PIN
  #define FAN_PIN                              -1
#endif

#ifndef FAN1_PIN
  #define FAN1_PIN                             6
#endif

//
// Misc. Functions
//
#define SDSS                                  77 // PB0_SD-SS
#define LED_PIN                               13
#define CASE_LIGHT_PIN                        9


// LCD / Controller
//
#define BTN_EN1                         14  //TX3
#define BTN_EN2                         72  //PJ2
#define BTN_ENC                          9  //
#define SD_DETECT_PIN                   15  // RX3


#if defined(VIKI2) || defined(miniVIKI)
    #define BEEPER_PIN 84   // PH2
    #define DOGLCD_A0  70   // PG4
    #define DOGLCD_CS  71   // PG3
    //#define LCD_SCREEN_ROT_180
#endif // Viki2
        
#ifdef TEMP_STAT_LEDS
      #define STAT_LED_RED_PIN      61  // PF7 
      #define STAT_LED_BLUE_PIN     59  // PF5
#endif

#if defined(REPRAP_DISCOUNT_SMART_CONTROLLER)
      #define LCD_PINS_RS                     82
      #define LCD_PINS_ENABLE                 61
      #define LCD_PINS_D4                     59
      #define LCD_PINS_D5                     70
      #define LCD_PINS_D6                     85
      #define LCD_PINS_D7                     71
      #define BEEPER_PIN                      84
    #endif
    
