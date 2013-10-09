/* InductiveCharging
 
 Receives commands from a PC connected via USB serial connection, interprets the commands
 and, when needed, sends a response back to the PC
 
 Created Sept 2013
 by Jeff Thacker
 Last modified Oct 2013
*/  

const int led =  13;      // the number of the onboard LED pin

// inputs and outputs for Charging Pad 1
const int pad1 = 2;          // output pin for Charging Pad 1 power relay
const int pad1Voltage = A0;  // analog input pin for Charging Pad 1 voltage measurement
const int pad1Current = A1;  // analog input pin for Charging Pad 1 current measurement

// inputs and outputs for Charging Pad 2
const int pad2 = 3;          // output pin for Charging Pad 2 power relay
const int pad2Voltage = A2;  // analog input pin for Charging Pad 2 voltage measurement
const int pad2Current = A3;  // analog imput pin for Charging Pad 2 current measurement

// inputs and outputs for Charging Pad 3
const int pad3 = 4;          // output pin for Charging Pad 3 power relay
const int pad3Voltage = A4;  // analog input pin for Charging Pad 3 voltage measurement
const int pad3Current = A5;  // analog input pin for Charging Pad 3 current measurement

//int serialData = 0;
char pcSerialData;       // the ~ character is being used to denote

/*
  Initialization routine runs on power up and reset
*/
void setup() {
  // set the digital pin as output:
  pinMode(led, OUTPUT);     
  pinMode(pad1, OUTPUT);
  pinMode(pad2, OUTPUT);
  pinMode(pad3, OUTPUT);
  
  // open serial communication with the PC
  Serial.begin(9600); 
}

/*
  Main loop
*/
void loop() {
  checkPCSerial();
  
}

/*
  Checks for input from the PC through the USB serial connection and takes
  any action given by the PC
*/
void checkPCSerial() {
  
  if (Serial.available()) {
    pcSerialData = Serial.read();
    Serial.print("received ");
    Serial.println(pcSerialData);
    // Serial.println();
    
    if (pcSerialData != '\0') {
      switch (pcSerialData) {
        case ' ':  // char ' ' turns on Charging Pad 1
          pad1On();
          break;
        case '!':  // char '!' turns off Charging Pad 1
          pad1Off();
          break;
        case '"':  // char '"' gets Charging Pad 1 voltage reading
          pad1GetVoltage();
          break;
        case '#':  // char '#' gets Charging Pad 1 current reading
          pad1GetCurrent();
          break;
        case '$':  // char '$' gets Charging Pad 1 color sensor reading
          pad1GetColor();
          break;
        case '%':  // char '%' turns on Charging Pad 1 color sensor LED
          pad1ColorLEDOn();
          break;
        case '&':  // char '&' turns off Charging Pad 1 color sensor LED
          pad1ColorLEDOff();
          break;
        case '\'':  // char ''' calibrates Charging Pad 1 color sensor
          pad1ColorCalibrate();
          break;
        case '(':  // char '(' turns on Charging Pad 2
          pad2On();
          break;
        case ')':  // char ')' turns off Charging Pad 2
          pad2Off();
          break;
        case '*':  // char '*' gets Charging Pad 2 voltage reading
          pad2GetVoltage();
          break;
        case '+':  // char '+' gets Charging Pad 2 current reading
          pad2GetCurrent();
          break;
        case ',':  // char ',' gets Charging Pad 2 color sensor reading
          pad2GetColor();
          break;
        case '-':  // char '-' turns on Charging Pad 2 color sensor LED
          pad2ColorLEDOn();
          break;
        case '.':  // char '.' turns off Charging Pad 2 color sensor LED
          pad2ColorLEDOff();
          break;
        case '/':  // char '/' calibrates Charging Pad 2 color sensor
          pad2ColorCalibrate();
          break;
        case '0':  // char '0' turns on Charging Pad 3
          pad3On();
          break;
        case '1':  // char '1' turns off Charging Pad 3
          pad3Off();
          break;
        case '2':  // char '2' gets Charging Pad 3 voltage reading
          pad3GetVoltage();
          break;
        case '3':  // char '3' gets Charging Pad 3 current reading
          pad3GetCurrent();
          break;
        case '4':  // char '4' gets Charging Pad 3 color sensor reading
          pad3GetColor();
          break;
        case '5':  // char '5' turns on Charging Pad 3 color sensor LED
          pad3ColorLEDOn();
          break;
        case '6':  // char '6' turns off Charging Pad 3 color sensor LED
          pad3ColorLEDOff();
          break;
        case '7':  // char '7' calibrates Charging Pad 3 color sensor
          pad3ColorCalibrate();
          break;
        default:
          break;
      }
    } 
  }
}


////////////////////////////////////////////////
// BEGIN COMMAND FUNCTIONS FOR CHARGING PAD 1 //
////////////////////////////////////////////////

/*
  Turns on Charging Pad 1 power
*/
void pad1On() {
  //Serial.println("in pad1On function");
  digitalWrite(pad1, HIGH);
}

/*
  Turns off Charging Pad 1 power
*/
void pad1Off() {
  //Serial.println("in pad1Off function");
  digitalWrite(pad1, LOW);
}

/*
  Gets the Charging Pad 1 voltage measurement and sends it to the PC
*/
void pad1GetVoltage() {
  Serial.println(analogRead(pad1Voltage));
}

/*
  Gets the Charging Pad 1 current measurement and sends it to the PC
*/
void pad1GetCurrent() {
  Serial.println(analogRead(pad1Current));
}

/*
  Gets the Charging Pad 1 color sensor measurement and sends it to the PC
*/
void pad1GetColor() {
  
}

/*
  Turns the Charging Pad 1 color sensor LED on
*/
void pad1ColorLEDOn() {
  
}

/*
  Turns the Charging Pad 1 color sensor LED off
*/
void pad1ColorLEDOff() {
  
}

/*
  Calibrates the Charging Pad 1 color sensor
*/
void pad1ColorCalibrate() {
  
}


////////////////////////////////////////////////
// BEGIN COMMAND FUNCTIONS FOR CHARGING PAD 2 //
////////////////////////////////////////////////

/*
  Turn on Charging Pad 2 power
*/
void pad2On() {
  Serial.println("in pad2On function");
  digitalWrite(pad2, HIGH);
}

/*
  Turn off Charging Pad 2 power
*/
void pad2Off() {
  Serial.println("in pad2Off function");
  digitalWrite(pad2, LOW); 
}

/*
  Get the Charging Pad 2 voltage measurement and sends it to the PC
*/
void pad2GetVoltage() {
  Serial.println(analogRead(pad2Voltage));
}

/*
  Gets the Charging Pad 2 current measurement and sends it to the PC
*/
void pad2GetCurrent() {
  Serial.println(analogRead(pad2Current));
}

/*
  Gets the Charging Pad 2 color sensor measurement and sends it to the PC
*/
void pad2GetColor() {
  
}

/*
  Turns the Charging Pad 2 color sensor LED on
*/
void pad2ColorLEDOn() {
  
}

/*
  Turns the Charging Pad 2 color sensor LED off
*/
void pad2ColorLEDOff() {
  
}

/*
  Calibrates the charging Pad 2 color sensor
*/
void pad2ColorCalibrate() {
  
}


////////////////////////////////////////////////
// BEGIN COMMAND FUNCTIONS FOR CHARGING PAD 3 //
////////////////////////////////////////////////

/*
  Turn on Charging Pad 3
*/
void pad3On() {
  Serial.println("in pad3On function");
  digitalWrite(pad3, HIGH);
}

/*
  Turn off Charging Pad 3
*/
void pad3Off() {
  Serial.println("in pad3Off function");
  digitalWrite(pad3, LOW);
}

/*
  Gets the Charging Pad 3 voltage measurement and sends it to the PC
*/
void pad3GetVoltage() {
  Serial.println(analogRead(pad3Voltage));
}

/*
  Gets the Charging Pad 3 current measurement and sends it to the PC
*/
void pad3GetCurrent() {
  Serial.println(analogRead(pad3Current));
}

/*
  Gets the Charging Pad 3 color sensor and sends it to the PC
*/
void pad3GetColor() {
  
}

/*
  Turns on the Charging Pad 3 color sensor LED
*/
void pad3ColorLEDOn() {
  
}

/*
  Turns off the Charging Pad 3 color sensor LED
*/
void pad3ColorLEDOff() {
  
}

/*
  Calibrates the Charging Pad 3 color sensor
*/
void pad3ColorCalibrate() {
  
}
