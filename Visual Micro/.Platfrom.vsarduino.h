/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void handle_remote_control(void);
void setup_WebServer_Commands();
void setup_ISRs(void);
void ISR_limit_switch_reached(void);
void ISR_remote_control(void);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Platfrom.ino"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\ClickButton.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\ClickButton.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\EscapedString.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\EscapedString.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonArray.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonArrayBase.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonArrayBase.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonGenerator.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonGenerator.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonObject.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonObjectBase.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonObjectBase.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonParser.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonParser.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonPrintable.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonValue.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\JsonValue.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\LimitSwitch.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\LimitSwitch.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\MCP4921.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\MCP4921.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Motor.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Motor.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\MotorWithBrake.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\MotorWithBrake.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Print.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Print.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Printable.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\StringBuilder.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\StringBuilder.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Vlonder.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\Vlonder_enums.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterMeasurer.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterMeasurer.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterSensor.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterSensorOneSensor.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterSensorOneSensor.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterSensorTwoSensors.cpp"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WaterSensorTwoSensors.h"
#include "D:\Documents\GitHub\Arduino Projects\Platfrom\WebServer.h"
#endif
