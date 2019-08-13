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
//        ToggleEnable | [ ]5~                    A0[ ] | Potentiometer
//                     | [ ]6~                    15[ ] |
//                     | [ ]7                     14[ ] |
//                     | [ ]8                     16[ ] |
//               RPWM  | [ ]9~                   ~10[ ] | LPWM
//                     |                                |
//                     +--------------------------------+
//
// ---------------------------------------------------------------------------------------
//                                   definitions
// ---------------------------------------------------------------------------------------

#define MCEnable 3
#define toggleEnable 5
#define RPWM 9
#define LPWM 10
#define potentiometer A0

int pot = 0;
int pwmWrite = 0;


void setup() {
  Serial.begin(9600); 
  pinMode (potentiometer, INPUT);
  pinMode (MCEnable, OUTPUT);
  pinMode (toggleEnable, INPUT_PULLUP);
  pinMode (RPWM, OUTPUT);
  pinMode (LPWM, OUTPUT);


  digitalWrite(MCEnable, HIGH);

}

void loop() {

  pot = analogRead(potentiometer);
  pwmWrite = constrain (map (pot, 0, 1024, 126, 257),128,255) ;
  analogWrite (RPWM, pwmWrite);
  Serial.println(pwmWrite); 

}
