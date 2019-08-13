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
//       ToggleEnable  | [ ]8                     16[ ] |
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

#define speedOne 2
#define speedTwo 3
#define speedThree 4
#define speedFour 5
#define NeoPixel 6
#define MCEnable 7
#define toggleEnable 8
#define RPWM 9
#define LPWM 10

int speed1;
int speed2;
int speed3;
int speed4;

int pwmWrite = 0;


void setup() {

  pinMode (speedOne, INPUT_PULLUP);
  pinMode (speedTwo, INPUT_PULLUP);
  pinMode (speedThree, INPUT_PULLUP);
  pinMode (speedFour, INPUT_PULLUP);
  pinMode (MCEnable, OUTPUT);
  pinMode (toggleEnable, INPUT_PULLUP);
  pinMode (RPWM, OUTPUT);
  pinMode (LPWM, OUTPUT);
 
  digitalWrite(MCEnable, HIGH);
  digitalWrite(toggleEnable, LOW); 

}

void loop() {
  speed1 = digitalRead(speedOne);
  speed2 = digitalRead(speedTwo);
  speed3 = digitalRead(speedThree);
  speed4 = digitalRead(speedFour);

  if (speed1 == 1 && speed2 == 1 && speed3 ==  1 && speed4 == 1) {
    pwmWrite = 0;
  }

  if (speed1 == 0) {
    pwmWrite = 128;
  }
  if (speed2 == 0) {
    pwmWrite = 171;
  }
  if (speed3 == 0) {
    pwmWrite = 214;
  }
  if (speed4 == 0) {
    pwmWrite = 255;
  }

  analogWrite (RPWM, pwmWrite);


}
