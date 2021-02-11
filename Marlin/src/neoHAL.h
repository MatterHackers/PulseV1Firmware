/***************************************************************************
neoHAL
A library for AS5600 by AMS
Copyright (c) 2017, Deft Dynamics
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by Deft Dynamics.
4. Neither the name of Deft Dynamics nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY DEFT DYNAMICS ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DEFT DYNAMICS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/

#ifndef NEOHAL_H
#define NEOHAL_H
#include "stdint.h"
//#include "Arduino.h"
//#include <Wire.h>

#define MAGNET_WEAK     3
#define MAGNET_STRONG   2
#define MAGNET_MISSING  1
#define MAGNET_OK       0

// Slow Filter
//    step delay (ms) | max RMS noise (1sigma deg)
// 0b00    2.200    0.015
// 0b01    1.100    0.021
// 0b10    0.550    0.030
// 0b11    0.286    0.043

// Fast Filter Threshold (LSB)
//    slow-to-fast  | fast-to-slow
// 0b000      slow only
// 0b001    6            1
// 0b010    7            1
// 0b011    9            1
// 0b100   18            2
// 0b101   21            2
// 0b110   24            2
// 0b111   10            4 

class neoHAL
{  
public:
  neoHAL(uint8_t addr=0x36);
  void begin(uint8_t FTH=0b001, uint8_t SF=0b00);
  uint16_t readAngle();
  uint8_t status();
  void setOrigin();
  uint8_t readByte(uint8_t reg);
  void writeByte(uint8_t reg, uint8_t val);
  
  uint16_t  angle = 0;
  uint16_t  rawAngle = 0;
  float degrees = 0;
  float rad = 0;
  uint16_t origin = 0;
  uint8_t stat = 0;
  
  union {
  char raw[20];
  struct {
   uint8_t header;      // alignment header
   uint8_t ID;          // message ID
   uint8_t status;
   uint8_t reserve1;
   uint16_t angle;
   uint16_t origin;
   uint16_t reserve2;
   uint16_t reserve3;
   uint16_t reserve4;
   uint16_t reserve5;
   uint16_t reserve6;
   uint16_t reserve7;
  } pcs;
} DX;

void updateDX();
  
private:
  int _address = 0x36;
  
};

#endif
