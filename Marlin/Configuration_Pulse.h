#ifndef CONFIGURATION_PULSE_H
#define CONFIGURATION_PULSE_H

// Pulse v2 options
// Letter (Machine Type)
// A = RAMPS, B = RamboMini, C = RamboMini, Tall Frame
// 
// First Digit (Bed & Leveling)
// 1 = BuildTak, 2 = Garalite, Tall Frame
//
// Second Digit (Electronics)
// 1 = No LCD, 2 = LCD, 3 = Viki
// 
// Third Digit (Hotend & Extruder)
// 1 = EZ-Struder & E3D light, 2 = BondTech & E3Dv6, 3 = 3mm BondTech & 3mm E3Dv6

#define MachineType "C"
#define BedType 1
#define ControllerType 2
#define ExtruderType 3

// C - defines that this is MOTHERBOARD BOARD_MINIRAMBO
#define MOTHERBOARD BOARD_MINIRAMBO

#if BedType == 1 || BedType == 2 // Big Heated Bed w' probe & New larger frame
	#define TEMP_SENSOR_BED 5
	// Travel limits after homing
	#define X_MAX_POS 245
	#define X_MIN_POS 0
	#define Y_MAX_POS 220
	#define Y_MIN_POS 0
	#define Z_MAX_POS 215
	#define Z_MIN_POS -5
	#define AUTO_BED_LEVELING_BILINEAR // Delete the comment to enable (remove // at the start of the line)
	//#define Z_PROBE_REPEATABILITY_TEST  // If not commented out, Z-Probe Repeatability test will be included if Auto Bed Leveling is Enabled.
#endif

#if ControllerType == 1 // no controller
#elif ControllerType == 2 // LCD controller (no change)
	#define REPRAP_DISCOUNT_SMART_CONTROLLER
#elif ControllerType == 3 // Viki controller
	#define TEMP_STAT_LEDS
	#define VIKI2
#endif

#if ExtruderType == 1 // EZ Struder
	#define HEATER_0_MAXTEMP 255
	#define TEMP_SENSOR_0 5
	#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,92.4}  // EZR
	#define  DEFAULT_Kp 15.84
	#define  DEFAULT_Ki 1.07
	#define  DEFAULT_Kd 58.40
#elif ExtruderType == 2 // BondTech & E3Dv6
	#define HEATER_0_MAXTEMP 305
	#define TEMP_SENSOR_0 5
	#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,470}  // Bondtech
	#define  DEFAULT_Kp 15.84
	#define  DEFAULT_Ki 1.07
	#define  DEFAULT_Kd 58.40
#elif ExtruderType == 3 // BondTech & E3Dv6 3mm
	#define HEATER_0_MAXTEMP 305
	#define TEMP_SENSOR_0 5
	#define DEFAULT_AXIS_STEPS_PER_UNIT   {80,80,400,510}  // Bondtech 3mm
	#define  DEFAULT_Kp 15.84
	#define  DEFAULT_Ki 1.07
	#define  DEFAULT_Kd 58.40
#endif

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)
#define MODLE_NUMBER STRINGIZE(BedType) STRINGIZE(ControllerType) STRINGIZE(ExtruderType)
#define FIRMWARE_VERSION " 1"
#define CUSTOM_MACHINE_NAME "Pulse " MachineType "-" MODLE_NUMBER FIRMWARE_VERSION
#define SHORT_BUILD_VERSION MachineType "-" MODLE_NUMBER

// set the rectangle in which to probe
#define LEFT_PROBE_BED_POSITION 35 // (X_MIN_POS + 15)
#define RIGHT_PROBE_BED_POSITION 200 // (X_MAX_POS - 15)
#define FRONT_PROBE_BED_POSITION 35 // (Y_MIN_POS + 15)
#define BACK_PROBE_BED_POSITION 170 // (Y_MAX_POS - 15)

#endif //__CONFIGURATION_PULSE_H
