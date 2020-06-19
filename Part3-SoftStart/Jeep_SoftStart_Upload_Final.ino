// =======================================================================================
//                  PowerWheels Conversion-- Jeep Wrangler
// =======================================================================================
//                            Written By: PatchBOTS
// =======================================================================================
//                     microcontroller  ---  Sparkfun Pro Micro (5v)
// --------------------------------------------------------------------------------------
//
//                                 proMicro
//                                ------------
//                                |           |
//                     +--------------------------------+
//                     |                                |
//                     | [ ]TX                   RAW[ ] |  POWER IN
//                     | [ ]RX                   GND[ ] |  GND
//              GND    | [ ]GND                  RST[ ] |
//              GND    | [ ]GND                  VCC[ ] | MotorControllers
//      Speed 1 Jumper | [ ]2                     A3[ ] |
//      Speed 2 Jumper | [ ]3~                    A2[ ] |
//      Speed 3 Jumper | [ ]4                     A1[ ] |
//          Gas Switch | [ ]5~                    A0[ ] |
//           NeoPixel  | [ ]6~                    15[ ] |
//           MCEnable  | [ ]7                     14[ ] |
//                     | [ ]8                     16[ ] |
//               RPWM  | [ ]9~                   ~10[ ] | LPWM
//                     |                                |
//                     +--------------------------------+
//
//
// ---------------------------------------------------------------------------------------
//                                   NOTES
// ---------------------------------------------------------------------------------------

//A video build log for this project can be found here:  youtube.com/PatchBOTS

//I purposely didn't break this out into function based on the response I get from people on YouTube. 
//People looking to do this are usually non-coders who want to upgrade their kid's PowerWheels, so I didn't want to add any complexity where it wasn't necessary.
//I tried to be as verbose as possible with my comments, but feel free to email me with any additional questions. 

//There are a couple hardware changes from the previous version:
// I elimated on of the speed modes.  Previously I had 4 speeds (12v, 16v, 20v, and 24v).  My kids are well beyond 12v, so I just eliminated that and will have 3 speeds starting around 16v. 
// Since we have one less speed, we have an extra pin already wired in, so I'll use that for the gas pedal switch.  Pin 2 is the lowest speed (like before, even though it's faster now), Pin 3 for Speed 2, and Pin 4 for Speed 3, Pin 5 will be for the gas pedal switch. 

// ---------------------------------------------------------------------------------------
//                                   definitions
// ---------------------------------------------------------------------------------------

#define speedOne 2  //defines Pin 2 on the Arduino for Speed1
#define speedTwo 3  //defines Pin 3 on the Arduino for Speed2
#define speedThree 4 //defines Pin 4 on the Arduino for Speed3
#define Switch  5 //defines Pin 5 on the Arduino for the digital switch at the gas pedal
#define MCEnable 7  // This gets wired to R_EN on the BTS7960 motor controller. 
#define RPWM 9  // Wire this to RPWM on the BTS7960 motor controller. 
#define LPWM 10 // This isn't used in the code.  It would give us a reverse function via the motor controller, which isn't really useful in this setting. 


//Below are variables we will be using in the code.
int speed1 = 1; //all the speed control pins and the switch at the gas pedal work by grounding the pin (setting to 0). By setting it's inital value to 1 it keeps everything safely "off" at boot up.
int speed2 = 1;
int speed3 = 1;
int gasSwitch = 1;

int pwmWrite = 0; //default boot up speed is 0
int rampSpeed; //this will be the starting point of our "ramp ups" in Speed 2 and Speed 3



void setup() {  //this section just tells the arduino what pins will be doing what

  Serial.begin(38400);

  pinMode (speedOne, INPUT_PULLUP);
  pinMode (speedTwo, INPUT_PULLUP);
  pinMode (speedThree, INPUT_PULLUP);
  pinMode (Switch, INPUT_PULLUP);
  pinMode (MCEnable, OUTPUT);
  pinMode (RPWM, OUTPUT);
  pinMode (LPWM, OUTPUT);

  digitalWrite(MCEnable, HIGH); //enable the Microcontroller. This will need to reamin high in order to work.
}


// ---------------------------------------------------------------------------------------
//                                  MAIN PROGRAM LOOP
// ---------------------------------------------------------------------------------------

void loop() {  //THIS IS THE START OF OUR MAIN LOOP

  //**************************GET VALUES*********************************************

  speed1 = digitalRead(speedOne); //check to see if the jumper is on lowest setting
  speed2 = digitalRead(speedTwo); // check to see if the jumper is on the 2nd setting
  speed3 = digitalRead(speedThree); //check to see if the jumper is on the 3rd setting
  gasSwitch = digitalRead(Switch); //check to see if Gas Pedal is engaged

  //************************NO JUMPER PINS*****************
  if (speed1 == 1 && speed2 == 1 && speed3 == 1) { //this is just a safety measure.  If the jumper pin is not properly on any of the setting pins, the car does nothing.
    pwmWrite = 0; // you can change this value to have a default "no pin" speed.  The highest is 255 for 100% power.
    analogWrite(RPWM, pwmWrite);  //Send no pin value to Gas Pedal. We are not doing any soft start here, obviously.
  }

  //************************SPEED 1****************

  if (speed1 == 0) { // this is saying "if the jumper for speed1 is engaged, then change the PWM value to what is entered here.
    pwmWrite = 175; //this value determines the speed at the lowest setting. The number is out of 255 so in this case 175/255 is about 67%% power.  Change value as you see fit.
    analogWrite(RPWM, pwmWrite); //no soft start for 16v, just business as usual.
  }

  //************************SPEED 2 *****************

  if (speed2 == 0 ) { // this is saying "if the jumper for speed2 is engaged..."
    pwmWrite = 215; //this value determines the top PWM value at the 2nd setting. The number is out of 255 so in this case 215/255 is about 85% power. Change value as you see fit
    rampSpeed = 175; //Our goal is to ramp up to "pwmWrite."  I chose 175 as a starting point for that ramp based on the fact that I've run that value a lot without problems for the gears.
    while   (gasSwitch == 1 && speed2 ==0) { //this while loop stops everything while the gas pedal is open.
      analogWrite(RPWM, rampSpeed); //while the gas pedal is open, write our starting point to the motors.
      speed1 = digitalRead(speedOne); //check to see if the jumper is on lowest setting
      speed2 = digitalRead(speedTwo); // check to see if the jumper is on the 2nd setting
      speed3 = digitalRead(speedThree); //check to see if the jumper is on the 3rd setting
      gasSwitch = digitalRead(Switch); //check again to see to if gas pedal is pressed.
    }
    while (gasSwitch == 0 ) { //if Gas Pedal is pressed....
      if (rampSpeed < pwmWrite) { //and rampSpeed is below our top speed....
        rampSpeed++; //add 1 to ramp speed
        delay(45); //delay before running the previous two lines again.  In my bench tests, a 20ms delay equals a 1 second ramp up from 175 to 215.  40ms = 2 seconds, 60 = 3 seconds, 80 = 4 seconds and so on. This will vary, but a decent starting point.
      }
      analogWrite(RPWM, rampSpeed); //write the current value of rampSpeed (when the if statement catches up to the final "pwmWrite" speed, it will hang there until the foot is taken off the gas).
      gasSwitch = digitalRead(Switch); //check again to see to if gas pedal is pressed.
    }
  }

  //************************SPEED 3*****************

  if (speed3 == 0) { // this is saying "if the jumper for speed3 is engaged...."
    pwmWrite = 255; //this value determines the top PWM value at the this setting. The number is out of 255 so in this case 255/255 is about 100% power. Change value as you see fit
    rampSpeed = 175; //Our goal is to ramp up to "pwmWrite."  I chose 175 as a starting point for that ramp based on the fact that I've run that value a lot without problems for the gears.
    while   (gasSwitch == 1 && speed3 ==0) { //this while loop stops everything while the gas pedal is open.
      speed1 = digitalRead(speedOne); //check to see if the jumper is on lowest setting
      speed2 = digitalRead(speedTwo); // check to see if the jumper is on the 2nd setting
      speed3 = digitalRead(speedThree); //check to see if the jumper is on the 3rd setting
      analogWrite(RPWM, rampSpeed); //while the gas pedal is open, write our starting point to the motors.
      gasSwitch = digitalRead(Switch); //check again to see to if gas pedal is pressed.
    }
    while (gasSwitch == 0) { //if Gas Pedal is pressed....
      if (rampSpeed < pwmWrite) { //and rampSpeed is below our top speed....
        rampSpeed++; //add 1 to ramp speed
        delay(25); //delay before running the previous two lines again.  In my bench tests, a 10ms delay equals a 1 second ramp up from 175 to 255.  20ms = 2 seconds, 30 = 3 seconds, 40 = 4 seconds and so on. This will vary, but a decent starting point.
      }
      analogWrite(RPWM, rampSpeed); //write the current value of rampSpeed (when the if statement catches up to the final "pwmWrite" speed, it will hang there until the foot is taken off the gas).
      gasSwitch = digitalRead(Switch); //check again to see to if gas pedal is pressed.
    }

  }


}

//Use for debugging. 
/*
    Serial.print("PWM Write: ");
    Serial.print(pwmWrite);
    Serial.print(", ");
    Serial.print("RampSpeed: ");
    Serial.print(rampSpeed);
    Serial.print(", ");
    Serial.println("24V");
*/
