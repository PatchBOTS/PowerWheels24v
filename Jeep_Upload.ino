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
//             Speed1  | [ ]2                     A3[ ] |
//             Speed2  | [ ]3~                    A2[ ] |
//             Speed3  | [ ]4                     A1[ ] |
//             Speed4  | [ ]5~                    A0[ ] |
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
//The shifter on the car will half the voltage so the settings will be:
//SPEED 1 - DEFAULT -  12v high, 6v Low - 50% Duty Cycle to motors.  PWM = 128
//SPEED 2 - 16v high, 8v low -67% duty cycle PWM = 171
//SPEED 3 - 20v high, 10v low -  84% duty cycle PWM = 214
//SPEED 4 - 24v high , 12v low - 100% duty cycle.  PWM = 255


// ---------------------------------------------------------------------------------------
//                                   definitions
// ---------------------------------------------------------------------------------------

#define speedOne 2  //defines Pin 2 on the Arduino for 12v mode
#define speedTwo 3  //defines Pin 3 on the Arduino for 16v mode
#define speedThree 4 //defines Pin 4 on the Arduino for 20v mode
#define speedFour 5 //defines Pin 5 on the Arduino for 24v mode
#define MCEnable 7  // This gets wired to R_EN on the BTS7960 motor controller. 
#define RPWM 9  // Wire this to RPWM on the BTS7960 motor controller. 
#define LPWM 10 // This isn't used in the code.  It would give us a reverse function via the motor controller, which isn't really useful in this setting. 


//Below are variables we will be using in the code. 
int speed1;
int speed2;
int speed3;
int speed4;

int pwmWrite = 0; //default boot up speed is 0 


void setup() {  //this section just tells the arduino what pins will be doing what

  pinMode (speedOne, INPUT_PULLUP);
  pinMode (speedTwo, INPUT_PULLUP);
  pinMode (speedThree, INPUT_PULLUP);
  pinMode (speedFour, INPUT_PULLUP);
  pinMode (MCEnable, OUTPUT);
  pinMode (toggleEnable, INPUT_PULLUP);
  pinMode (RPWM, OUTPUT);
  pinMode (LPWM, OUTPUT);
 
  digitalWrite(MCEnable, HIGH); //enable the Microcontroller. This will need to reamin high in order to work.  


}

void loop() {  //THIS IS THE START OF OUR MAIN LOOP
  
  speed1 = digitalRead(speedOne); //check to see if the jumper is on lowest setting
  speed2 = digitalRead(speedTwo); // check to see if the jumper is on the 2nd setting
  speed3 = digitalRead(speedThree); //check to see if the jumper is on the 3rd setting
  speed4 = digitalRead(speedFour); //check to see if the jumper is on the 4th setting

  if (speed1 == 1 && speed2 == 1 && speed3 ==  1 && speed4 == 1) {  //this is just a safety measure.  If the jumper pin is not properly on any of the setting pins, the car does nothing. 
    pwmWrite = 0; // you can change this value to have a default "no pin" speed.  The highest is 255 for 100% power. 
  }

  if (speed1 == 0) { // this is saying "if the jumper for speed1 is engaged, then change the PWM value to what is entered here. 
    pwmWrite = 128; //this value determines the speed at the lowest setting. The number is out of 255 so in this case 128/255 is about 50% power.  Change value as you see fit. 
  }
  if (speed2 == 0) { // this is saying "if the jumper for speed2 is engaged, then change the PWM value to what is entered here. 
    pwmWrite = 171; //this value determines the speed at the 2nd setting. The number is out of 255 so in this case 171/255 is about 67% power. Change value as you see fit
  }
  if (speed3 == 0) { // this is saying "if the jumper for speed3 is engaged, then change the PWM value to what is entered here. 
    pwmWrite = 214; //this value determines the speed at the 3rd setting. The number is out of 255 so in this case 214/255 is about 84% power. Change value as you see fit. 
  }
  if (speed4 == 0) { // this is saying "if the jumper for speed4 is engaged, then change the PWM value to what is entered here. 
    pwmWrite = 255; //this value determines the speed at the Highest setting. The number is out of 255 so in this case 255/255 is 100% power. Change value as you see fit. 
  }

  analogWrite (RPWM, pwmWrite); //with the above "if" statement determining the PWM value. This line of code sends that value to the motor controller, then the loop repeats

}
