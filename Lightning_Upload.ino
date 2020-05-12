// =======================================================================================
//                  PowerWheels Conversion-- Lightning McQueen
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
//                     | [ ]2                     A3[ ] |
//           MC Enable | [ ]3~                    A2[ ] |
//                     | [ ]4                     A1[ ] |
//                     | [ ]5~                    A0[ ] | Potentiometer
//                     | [ ]6~                    15[ ] |
//                     | [ ]7                     14[ ] |
//                     | [ ]8                     16[ ] |
//               RPWM  | [ ]9~                   ~10[ ] | 
//                     |                                |
//                     +--------------------------------+
//
// ---------------------------------------------------------------------------------------
//                                   definitions
// ---------------------------------------------------------------------------------------

#define MCEnable 3 //enable pin for Motor Controller, always high
#define RPWM 9 //sends signal to the Motor Controller
#define potentiometer A0 //reads knob 

//variables for code
int pot = 0;
int pwmWrite = 0;


void setup() { //Sets up our microcontroller 
 // Serial.begin(9600);  //enable for debugging
  pinMode (potentiometer, INPUT);
  pinMode (MCEnable, OUTPUT);
  pinMode (RPWM, OUTPUT);

  digitalWrite(MCEnable, HIGH);

}

void loop() { //THIS IS THE START OF OUR LOOP

  pot = analogRead(potentiometer); //read value of potentiometer 0-1024
  pwmWrite = constrain (map (pot, 0, 1024, 126, 257),128,255); //remap the 0-1024 to 126-257 and then only use values 128-255. THis gets rid of jitters at the extremes of the pot. 
  analogWrite (RPWM, pwmWrite); //write the value calculated above to the motorcontroller. 
//  Serial.println(pwmWrite); //enable for debugging

} //REPEAT LOOP
