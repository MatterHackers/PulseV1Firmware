#ifndef CONFIGURATION_PULSE_H
#define CONFIGURATION_PULSE_H

// Pulse v1 options
// A = Machine type
// 
// First Digit (Bed & Leveling)
// 0 = Standard Bed, 1 = Heated Bed, 2 = Big Not Heated b Bed, 3 = Big Heated Bed,
// 4 = Not Heated, Inductive Zmax, 5 = Heated, Inductive Zmax, 6 = Not Heated, Probe, 7 = Heated, Probe
//
// Second Digit (Electronics)
// 2 = No LCD, 3 = LCD
// 
// Third Digit (Hotend & Extruder)
// 4 = EZ-Struder & E3D light, 5 = BondTech & E3Dv6, 6 = 3mm BondTech & 3mm E3Dv6

#define BedType 5
#define ControllerType 3
#define ExtruderType 5

#if BedType == 0 // Standard Bed
#define TEMP_SENSOR_BED 0
// Travel limits after homing
#define X_MAX_POS 220
#define X_MIN_POS -16
#define Y_MAX_POS 220
#define Y_MIN_POS -8
#define Z_MAX_POS 165
#define Z_MIN_POS -10

#elif BedType == 1 // Heated Bed
#define TEMP_SENSOR_BED 5
// Travel limits after homing
#define X_MAX_POS 205
#define X_MIN_POS 0
#define Y_MAX_POS 205
#define Y_MIN_POS 0
#define Z_MAX_POS 180
#define Z_MIN_POS -10

#elif BedType == 2 // Big Standard Bed
#define TEMP_SENSOR_BED 0
// Travel limits after homing
#define X_MAX_POS 240
#define X_MIN_POS 0
#define Y_MAX_POS 215
#define Y_MIN_POS 0
#define Z_MAX_POS 175
#define Z_MIN_POS -10

#elif BedType == 3 // Big Heated Bed
#define TEMP_SENSOR_BED 5
#define Z_MAX_POS 175 
// Travel limits after homing
#define X_MAX_POS 240
#define X_MIN_POS 0
#define Y_MAX_POS 215
#define Y_MIN_POS 0
#define Z_MAX_POS 175
#define Z_MIN_POS -10

#elif BedType == 4 // Not Heated, Inductive Zmax
#define TEMP_SENSOR_BED 0
// Travel limits after homing
#define X_MAX_POS 220
#define X_MIN_POS -16
#define Y_MAX_POS 220
#define Y_MIN_POS -8
#define Z_MAX_POS 190
#define Z_MIN_POS -10

#elif BedType == 5 // Big Heated Bed, Inductive Zmax
#define TEMP_SENSOR_BED 5
#define Z_MAX_POS 175 
// Travel limits after homing
#define X_MAX_POS 240
#define X_MIN_POS 0
#define Y_MAX_POS 215
#define Y_MIN_POS 0
#define Z_MAX_POS 195
#define Z_MIN_POS -10

#elif BedType == 6 // Not Heated, Inductive Zmax, w' probe
#define TEMP_SENSOR_BED 0
// Travel limits after homing
#define X_MAX_POS 220
#define X_MIN_POS -16
#define Y_MAX_POS 220
#define Y_MIN_POS -8
#define Z_MAX_POS 190
#define Z_MIN_POS -10
#define ENABLE_AUTO_BED_LEVELING // Delete the comment to enable (remove // at the start of the line)
//#define Z_PROBE_REPEATABILITY_TEST  // If not commented out, Z-Probe Repeatability test will be included if Auto Bed Leveling is Enabled.

#elif BedType == 7 // Big Heated Bed w' probe
#define TEMP_SENSOR_BED 5
// Travel limits after homing
#define X_MAX_POS 240
#define X_MIN_POS 0
#define Y_MAX_POS 213
#define Y_MIN_POS 0
#define Z_MAX_POS 195
#define Z_MIN_POS 0 // Happens automatically because there is a z-min switch so anything less than zero is ignored.
#define ENABLE_AUTO_BED_LEVELING // Delete the comment to enable (remove // at the start of the line)
//#define Z_PROBE_REPEATABILITY_TEST  // If not commented out, Z-Probe Repeatability test will be included if Auto Bed Leveling is Enabled.
#endif

#if ControllerType == 2 // no controller
#elif ControllerType == 3 // LCD controller (no change)
#define ControllerString = "3"
#endif

#if ExtruderType == 4 // EZ Struder
#define HEATER_0_MAXTEMP 255
#define TEMP_SENSOR_0 5
#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,92.4}  // EZR
#elif ExtruderType == 5 // BondTech & E3Dv6
#define HEATER_0_MAXTEMP 305
#define TEMP_SENSOR_0 5
#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,490}  // Bondtech
#elif ExtruderType == 6 // BondTech & E3Dv6 3mm
#define HEATER_0_MAXTEMP 305
#define TEMP_SENSOR_0 5
#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,510}  // Bondtech 3mm
#endif

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)
#define CUSTOM_MENDEL_NAME "Pulse A-" STRINGIZE(BedType) STRINGIZE(ControllerType) STRINGIZE(ExtruderType)

#define FIRMWARE_VERSION " 1"
#define MACHINE_NAME CUSTOM_MENDEL_NAME

// set the rectangle in which to probe
#define LEFT_PROBE_BED_POSITION 35 // (X_MIN_POS + 15)
#define RIGHT_PROBE_BED_POSITION 200 // (X_MAX_POS - 15)
#define FRONT_PROBE_BED_POSITION 35 // (Y_MIN_POS + 15)
#define BACK_PROBE_BED_POSITION 170 // (Y_MAX_POS - 15)

#endif //__CONFIGURATION_PULSE_H
