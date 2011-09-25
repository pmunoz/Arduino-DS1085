/*
 DS1085.h - Library for controlling DS1085 oscillator from arduino
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

#ifndef	ds1085_h
#define ds1085_h
	#include <WProgram.h>
	#include <Wire.h>

	/*
	 *  DS1085 commands set
	 */
	#define  AccDAC      0x08
	#define  AccOFFSET   0x0E
	#define  AccDIV      0x01
	#define  AccMUX      0x02
	#define  AccADDR     0x0D
	#define  AccRANGE    0x37
	#define  WriteE2     0x3F

	class DS1085
		{
		public:
			DS1085(int address);
			void begin();
			int getDAC();		
			int getOFFSET();
			int get_Relative_OFFSET();
			int getDIV();
			int getADDR();
			int getMUX();
			int getDIV1();
			int getPS0();
			int getPS1();
			//int getModeOUT0();
			//int getModeOUT1();
			int getRANGE();
			
			void setDAC(int val);
			void setOFFSET(int offset);
			void set_Relative_OFFSET(int dif);
			void setDIV(int val);
			void setADDR(boolean WC, int addr); 
			void setMUX(int val);
			void setDIV1(boolean div1);
			void setPS0(int ps0);
			void setPS1(int ps1);
			//void setModeOUT0(int val);
			//void setModeOUT1(int val);
	
			void writeE2();
	
		private:
			int _DEF_OFFSET;
			int _address;
			
	};
#endif
