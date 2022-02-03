/*
 DS1085.cpp - Arduino Library for controlling DS1085 EconOscillator Frequency Synthesizer
 Copyright (c) 2011 Pablo Muñoz.  All right reserved.

 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DS1085.h"


DS1085::DS1085(int address)
{
	_address = address >> 1;
}

void DS1085::begin(){	
	Wire.begin();
	_DEF_OFFSET = getRANGE();
}
/*DS1085::void setup(){
}
*/


/*
 * Gets the DAC register value 
 */
int DS1085::getDAC(){
	int result = 0;
	Wire.beginTransmission(_address); Wire.write(AccDAC); 		Wire.endTransmission();
  	Wire.requestFrom(_address,2); int byte1 = 		Wire.read(); int byte2 = Wire.read();
	result = (byte1 << 2) | (byte2 >> 6);
	return result;
}

/*
 * Sets the DAC register value
 */
void DS1085::setDAC(int val){
	byte byte1 = val >> 2;
	byte byte2 = (0b11 & val) << 6;  
	byte data[] =  {byte1,byte2};  
	Wire.beginTransmission(_address); Wire.write(AccDAC); 		Wire.write(data,2); Wire.endTransmission();
}

//---------------------------------------------------------------------------------------------

/*
 * Gets the OFFSET register value 
 */
int DS1085::getOFFSET(){
	Wire.beginTransmission(_address); Wire.write(AccOFFSET); Wire.endTransmission();
	Wire.requestFrom(_address,1); int byte1 = Wire.read();
	int val = (0x1F) & byte1;
	return val;
}

/*
 * Sets the OFFSET register value 
 */
void DS1085::setOFFSET(int offset){
	byte byte1 = (byte) 0x1F & offset;
	Wire.beginTransmission(_address); Wire.write(AccOFFSET); Wire.write(byte1); Wire.endTransmission();
}


int DS1085::get_Relative_OFFSET(){
	return getOFFSET() - _DEF_OFFSET;
}
 
void DS1085::set_Relative_OFFSET(int dif){
	int offset = _DEF_OFFSET + dif;
	setOFFSET(offset); 
}

//---------------------------------------------------------------------------------------------


/*
 * Gets the DIV register value 
 */
int DS1085::getDIV(){
	int result = 0;
	Wire.beginTransmission(_address); Wire.write(AccDIV); Wire.endTransmission();
	Wire.requestFrom(_address,2); int byte1 = Wire.read(); int byte2 = Wire.read();
	result = (byte1 << 2) | (byte2 >> 6);
	return result;
}

/*
 * Sets the DIV register value
 */
void DS1085::setDIV(int val){
	byte byte1 = val >> 2;
	byte byte2 = (0b11 & val) << 6;  
	byte data[] =  {byte1,byte2};  
	Wire.beginTransmission(_address); Wire.write(AccDIV); Wire.write(data,2); Wire.endTransmission();
}

//---------------------------------------------------------------------------------------------


/*
 * Gets the ADDR register value 
 */
int DS1085::getADDR(){
	int result = 0;
	Wire.beginTransmission(_address); Wire.write(AccADDR); Wire.endTransmission();
	Wire.requestFrom(_address,1); int byte1 = Wire.read();
	result = (0x0F) & (byte1);
	return result;
}

/*
 * Sets the ADDR register value 
 */
void DS1085::setADDR(boolean WC, int addr){
	int val = (0xF) & addr;
	if(WC){
		val = (0b1000) | val;   
	}
	else{
		val = (0b0111) & val;  
	}
	Wire.beginTransmission(_address); Wire.write(AccADDR); Wire.write(val); Wire.endTransmission();
}

//---------------------------------------------------------------------------------------------

/*
 * Writes configuration to the EEPROM memory
 */
void DS1085::writeE2(){
	Wire.beginTransmission(_address); Wire.write(WriteE2); Wire.endTransmission();
}

//---------------------------------------------------------------------------------------------


/*
 * Gets the MUX register value 
 */
int DS1085::getMUX(){
	int result = 0;
	Wire.beginTransmission(_address); Wire.write(AccMUX); Wire.endTransmission();
	Wire.requestFrom(_address,2); int byte1 = Wire.read(); int byte2 = Wire.read();
	result = (byte1 << 2) | (byte2 >> 6);
	return result;
}

/*
 * Gets the MUX register value 
 */
void DS1085::setMUX(int val){
	byte byte1 = val >> 2;
	byte byte2 = (0b11 & val) << 6;  
	byte data[] =  {byte1,byte2};  
	Wire.beginTransmission(_address); Wire.write(AccMUX); Wire.write(data,2); Wire.endTransmission();
}

int DS1085::getDIV1(){
	int mux = getMUX();
	return mux & 0x1;
}

void DS1085::setDIV1(boolean div1){
	int mux = getMUX();
	if(div1 == true){
		mux = (mux | 0x01);    
	}
	else{
		mux = (mux & 0xFE);
	}
	setMUX(mux);
}

int DS1085::getPS0(){
	int mux = getMUX();
	return (mux & 0x18) >> 3;
}

void DS1085::setPS0(int ps0){
	int mux = getMUX();
	int ps = ps0;
	mux = mux & 0x3E7;
	ps = (ps0 & 0x3)<<3;
	mux = mux | ps;
	setMUX(mux);
}

int DS1085::getPS1(){
	int mux = getMUX();
	return (mux & 0x6) >> 1;
}

void DS1085::setPS1(int ps1){
	int mux = getMUX();
	int ps = ps1;
	mux = mux & 0x3F9;
	ps = (ps1 & 0x3)<<1;
	mux = mux | ps;
	setMUX(mux);
}

/*

void setModeOUT0(int val){
  int mode0 = 0b111 & val;
  int mux = getMUX();
  mux = mux & 0xF1F;
  mode0 = mode0 << 5;
  mux = mux | mode0;
  setMUX(mux);
}

int getModeOUT0(){
  int mux = getMUX();
  return (mux & 0xD0) >> 5;
}

void setModeOUT1(int val){
  int mode1 = 0b1 & val;
  int mux = getMUX();
  mux = mux & 0x2FF;
  mode1 = mode1 << 8;
  mux = mux | mode1;
  setMUX(mux);  
}

int getModeOUT1(){
  int mux = getMUX();
  return (mux & 0x100) >> 8;
}
*/





//---------------------------------------------------------------------------------------------

/*
 * Gets the RANGE register value (only-read)
 */
int DS1085::getRANGE(){
	int result = 0;
	Wire.beginTransmission(_address); Wire.write(AccRANGE); Wire.endTransmission();
	Wire.requestFrom(_address,2); int byte1 = Wire.read(); int byte2 = Wire.read();
	result = (byte1 >> 3);
	return result;
}


