
// Include Libraries
#include "Arduino.h"
#include "DS18B20.h"
#include "Keypad.h"
#include "LiquidCrystal_PCF8574.h"


// Pin Definitions
#define DS18B20WP_PIN_DQ	0
#define FINGERPRINTSCANNER_3V3_PIN_RX	3
#define FINGERPRINTSCANNER_3V3_PIN_TX	1
#define KEYPADMEM3X4_PIN_ROW1	6
#define KEYPADMEM3X4_PIN_ROW2	7
#define KEYPADMEM3X4_PIN_ROW3	8
#define KEYPADMEM3X4_PIN_ROW4	9
#define KEYPADMEM3X4_PIN_COL1	2
#define KEYPADMEM3X4_PIN_COL2	4
#define KEYPADMEM3X4_PIN_COL3	5



// Global variables and defines
//Use this 2D array to map the keys as you desire
char keypadmem3x4keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints. 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
// object initialization
DS18B20 ds18b20wp(DS18B20WP_PIN_DQ);
Keypad keypadmem3x4(KEYPADMEM3X4_PIN_COL1,KEYPADMEM3X4_PIN_COL2,KEYPADMEM3X4_PIN_COL3,KEYPADMEM3X4_PIN_ROW1,KEYPADMEM3X4_PIN_ROW2,KEYPADMEM3X4_PIN_ROW3,KEYPADMEM3X4_PIN_ROW4);
LiquidCrystal_PCF8574 lcdI2C;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //Initialize the keypad with selected key map
    keypadmem3x4.begin(keypadmem3x4keys);
    // initialize the lcd
    lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // DS18B20 1-Wire Temperature Sensor - Waterproof - Test Code
    // Read DS18B20 temp sensor value in degrees celsius. for degrees fahrenheit use ds18b20wp.ReadTempF()
    float ds18b20wpTempC = ds18b20wp.readTempC();
    Serial.print(F("Temp: ")); Serial.print(ds18b20wpTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Fingerprint Scanner - TTL (GT-511C3) is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3') {
    // Membrane 3x4 Matrix Keypad - Test Code
    //Read keypad
    char keypadmem3x4Key = keypadmem3x4.getKey();
    if (isDigit(keypadmem3x4Key) ||  keypadmem3x4Key == '*' ||  keypadmem3x4Key == '#')
    {
    Serial.print(keypadmem3x4Key);
    }
    }
    else if(menuOption == '4') {
    // LCD 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '5')
    {
    // Disclaimer: The SparkFun Particle Sensor Breakout - MAX30105 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DS18B20 1-Wire Temperature Sensor - Waterproof"));
    Serial.println(F("(2) Fingerprint Scanner - TTL (GT-511C3)"));
    Serial.println(F("(3) Membrane 3x4 Matrix Keypad"));
    Serial.println(F("(4) LCD 16x2 I2C"));
    Serial.println(F("(5) SparkFun Particle Sensor Breakout - MAX30105"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DS18B20 1-Wire Temperature Sensor - Waterproof"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Fingerprint Scanner - TTL (GT-511C3) - note that this component doesn't have a test code"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Membrane 3x4 Matrix Keypad"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing LCD 16x2 I2C"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing SparkFun Particle Sensor Breakout - MAX30105 - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/