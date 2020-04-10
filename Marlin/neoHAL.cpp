/***************************************************************************
[NAME OF THE LIBRARY]
A library for [NAME OF IC] by [NAME OF MANUFACTURER]
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

#include "Arduino.h"
#include "neoHAL.h"
#include "Wire.h"

neoHAL::neoHAL(uint8_t addr){
   // constructor
   _address = addr;
}

void neoHAL::begin(uint8_t FTH, uint8_t SF){
  Wire.begin();
  byte package = (FTH<<2) | (SF<<0);
  writeByte(0x07,package);
}

void neoHAL::updateDX(){
  DX.pcs.header = 0xD0;
  DX.pcs.ID = 10;
  DX.pcs.status = stat;
  DX.pcs.angle = angle;
  DX.pcs.origin = origin;
}

uint16_t neoHAL::readAngle(){
  Wire.beginTransmission(_address);
  Wire.write(0x0C);
  Wire.endTransmission(false);
  Wire.requestFrom(_address,2);
  uint16_t A = Wire.read() & 0x0F;
  uint8_t B = Wire.read();
  rawAngle = (A<<8) | B;
  angle = (((A<<8) | B) - origin + 4095) % 4095;
  degrees = (float)angle/4095.0*360.0;
  rad = (float)angle/4095.0*2*PI;
  updateDX();
  return angle;
}

uint8_t neoHAL::status(){
  Wire.beginTransmission(_address);
  Wire.write(0x0B);
  Wire.endTransmission(false);
  Wire.requestFrom(_address,1);
  uint16_t A = Wire.read();
  bool MD = (A&0b100000)>>5;
  bool ML = (A&0b010000)>>4;
  bool MH = (A&0b001000)>>3;
  if (!MD) { 
    stat = MAGNET_MISSING;
  } else if (ML) {
  stat = MAGNET_WEAK;
  } else if (MH) {
  stat = MAGNET_STRONG;
  } else {
  stat = MAGNET_OK;
  }
  updateDX();
  return stat;
}

void neoHAL::setOrigin(){
  readAngle();
  origin = rawAngle;
}

uint8_t neoHAL::readByte(uint8_t reg){
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(_address,1);
  return Wire.read();
}

void neoHAL::writeByte(uint8_t reg, uint8_t val){
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
