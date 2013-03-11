// DistanceSensor.h - Arduino library for retrieving data from Distance sensors
// Copyright 2011 Jeroen Doggen (jeroendoggen@gmail.com)
// More info: http://www.robot-electronics.co.uk/files/SRF04.pde
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include <SoftwareSerial.h>
#include "Arduino.h"
#include "ParallaxRFID.h"

SoftwareSerial mySerial(_rxPin, _txPin);

ParallaxRFID::ParallaxRFID()
{
	Serial.begin(9600);
	mySerial.begin(9600);
	pinMode(_txPin, OUTPUT);     
	pinMode(_rxPin, INPUT);
}

void ParallaxRFID::suppressAll()                                //suppresses the "null result" from being printed if no RFID tag is present
{
    if(mySerial.available() > 0)
    { mySerial.read();
      suppressAll();
    }
}

void ParallaxRFID::Read()                              
{
	 if(mySerial.available() > 0) {          // if data available from reader 

    if((val = mySerial.read()) == 10) {   // check for header 
      bytesread = 0; 
      while(bytesread<10) 
	  {              // read 10 digit code 
        if( mySerial.available() > 0) 
		{ 
          val = mySerial.read(); 
          if((val == 10)||(val == 13)) 
		  { // if header or stop bytes before the 10 digit reading 
            break;                       // stop reading 
          } 
          _code[bytesread] = val;         // add the digit           
          bytesread++;                   // ready to read next digit  
        } 
      } 

      if(bytesread == 10) {              // if 10 digit read is complete 
        Serial.print("TAG code is: ");   // possibly a good TAG 
        Serial.println(_code);            // print the TAG code 
      } 
      bytesread = 0;
}