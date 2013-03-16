/*
  Nunchuck.h -  Wii Nunchuck library for Arduino 
  Version: 0.1
  
  Copyright (c) 2013 Joseph Diaz.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Nunchuck_h
#define Nunchuck_h

#define NUNCHUCK_ADDRESS 0x52

class Nunchuck
{
  public:
    Nunchuck();
    void begin();
	bool read();
	int getJoyX();
	int getJoyY();
	int getAccX();
	int getAccY();
	int getAccZ();
	bool getC();
	bool getZ();
	
	void calibrate();
	void calibrateCenter();
	void calibrateRange();
	int getPercentJoyX();
	int	getPercentJoyY();
	
  private:
	int _joyX;
	int _joyY;
	int _accX;
	int _accY;
	int _accZ;
	bool _c;
	bool _z;
	
	bool _calibrated;
	
	int _joyMaxX;
	int _joyMinX;
	int _joyCenterX;
	
	int _joyMaxY;
	int _joyMinY;
	int _joyCenterY;
};
	
#endif