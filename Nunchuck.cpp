/*
  Nunchuck.cpp -  Wii Nunchuck library for Arduino
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

#include "Nunchuck.h"
#include "Arduino.h"
#include <Wire.h>

#define NOP __asm__ __volatile__ ("nop\n\t")

//Constructor
Nunchuck::Nunchuck(){
	_joyX=0;
	_joyY=0;
	_accX=0;
	_accY=0;
	_accZ=0;
	_c=false;
	_z=false;
	
	_calibrated=false;
	_joyCenterX=122;
	_joyCenterY=122;
	_joyMaxX=122;
	_joyMaxY=122;
	_joyMinX=122;
	_joyMinY=122;
	
	Wire.begin();

}

void Nunchuck::begin(){
	//Initailialize Controller
	Wire.beginTransmission(NUNCHUCK_ADDRESS);
	Wire.write(0x40);
	Wire.write(0x00);
	Wire.endTransmission();	
}

bool Nunchuck::read(){
	unsigned char buffer[6];
	int counter=0;
	
	Wire.beginTransmission(NUNCHUCK_ADDRESS);
	Wire.write(0x00);
	Wire.endTransmission ();
	
	//Delay between send 0 and read
		
	//for(int i=0;i<200;i++)
	//	NOP;
	delay(1);
	Wire.requestFrom(NUNCHUCK_ADDRESS, 6);
	
	while (Wire.available()){
		buffer[counter]=(Wire.read() ^ 0x17)+0x17;
		counter++;
	}
	
	//Failed to retrieve all bytes
	if(counter<5)
		return false;
		
	//Process the data
	_joyX=buffer[0];
	_joyY=buffer[1];
	
	_accX=buffer[2] << 2;
	_accY=buffer[3] << 2;
	_accZ=buffer[4] << 2;
	
	_accX+=(buffer[5]>>2)&0x03;
	_accY+=(buffer[5]>>4)&0x03;
	_accZ+=(buffer[5]>>6)&0x03;
	
	if((buffer[5]&0x01)!=0)
		_z=false;
	else
		_z=true;
		
	if((buffer[5]&0x02)!=0)
		_c=false;
	else
		_c=true;
		
	return true;
}

bool Nunchuck::getC(){
	return _c;
}

bool Nunchuck::getZ(){
	return _z;
}

int Nunchuck::getAccX(){
	return _accX;
}

int Nunchuck::getAccY(){
	return _accY;
}

int Nunchuck::getAccZ(){
	return _accZ;
}

int Nunchuck::getJoyX(){
	return _joyX;
}

int Nunchuck::getJoyY(){
	return _joyY;
}

void Nunchuck::calibrate(){
	//Calibrate Center Point
	read();
	while(!getC()){
		read();
		_joyCenterX=getJoyX();
		_joyCenterY=getJoyY();
	}
	delay(300);
	read();
	//Calibrate Max/Min
	while(!getC()){
		read();
		if(getJoyX()>_joyMaxX)
			_joyMaxX=getJoyX();
		if(getJoyY()>_joyMaxY)
			_joyMaxY=getJoyY();
			
		if(getJoyX()<_joyMinX)
			_joyMinX=getJoyX();
		if(getJoyY()<_joyMinY)
			_joyMinY=getJoyY();
	}
	
	_calibrated=true;
}

void Nunchuck::calibrateCenter(){
	//Calibrate Center Point
	read();
	while(!getC()){
		read();
		_joyCenterX=getJoyX();
		_joyCenterY=getJoyY();
	}
	_calibrated=true;
}

void Nunchuck::calibrateRange(){
	read();
	//Calibrate Max/Min
	while(!getC()){
		read();
		if(getJoyX()>_joyMaxX)
			_joyMaxX=getJoyX();
		if(getJoyY()>_joyMaxY)
			_joyMaxY=getJoyY();
			
		if(getJoyX()<_joyMinX)
			_joyMinX=getJoyX();
		if(getJoyY()<_joyMinY)
			_joyMinY=getJoyY();
	}
	_calibrated=true;
}

int Nunchuck::getPercentJoyX(){
	int temp;
	
	if(_joyX<_joyCenterX){
		temp = (_joyX-_joyCenterX)*100/(_joyMinX-_joyCenterX);
		if(temp>100)
			return -100;
		return -temp;
	}
	else if(_joyX>_joyCenterX){
		temp = (_joyX-_joyCenterX)*100/(_joyMaxX-_joyCenterX);
		if(temp>100)
			return 100;
		return temp;
	}
	else 
		return 0;
}

int Nunchuck::getPercentJoyY(){
	int temp;
	
	if(_joyY<_joyCenterY){
		temp= (_joyY-_joyCenterY)*100/(_joyMinY-_joyCenterY);
		if(temp>100)
			return -100;
		return -temp;
	}
	else if(_joyY>_joyCenterY){
		temp = (_joyY-_joyCenterY)*100/(_joyMaxY-_joyCenterY);
		if(temp>100)
			return 100;
		return temp;
	}
	else
		return 0;
}