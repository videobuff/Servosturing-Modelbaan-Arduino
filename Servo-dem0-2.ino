/*--------------------------------------------------------------
 * Servo controller sketch voor modelbanen - toggle schakelaar - Version 1.0
 * sketch name: Servo-demo-2
 * Last updated 21-10-201

  Description:  Demonstratie model om met een togle schakelaar een servo van links naar
                rechts te laten bewegen, bv voor een overweg of een sein.
                Maakt gebruik van de arduino uno en de pca9865

  Software:     Developed using Arduino 1.8.18 software for the Ardunino INO
                Should be compatible with Arduino 1.0 + and newer ESP32/Arduino releases if any

  ToDo          Timing fine tunen, schakelaar debouncen etc.

  Date:         21-102021

  Author:       Erik Schott - erik@pa0esh.com
*/


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// Als je een ander adres gebruikt dien je dit aan te geven. Hangt af van de solderingen op het pca9865 board
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Pas de pulsbreedte aan aan het type servo voor MIN en MAX
#define SERVOMIN  130 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  650 // this is the 'maximum' pulse length count (out of 4096)

// Onze servo # counter - we beginnen met kanaal 0 op de pca9865
uint8_t servonum = 0; //zorg later voor een loop om iedere servo aan te spreken. Test daarvoor de wijziging in een schakelaar waarde.
// Status van de servo (linksom of rechtsom)
int status_servo0 = 0;
// sla status op. Draai alleen servo als status wijzigt. 0 = links - 1 = rechts
int switch_pin0 = 4;
// sluit hier de eerste schakelaar op aan, die servo 0 bedient. digitale pin 4
// schakelaar is als volgt: pin 4 met een weerstand van 1k naar plus 5V. Middenpoot van de schakelaar aan aarde.
// rechter / of linker pootje naar pin 4 op de Arduino.



byte leds = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Modelbaan Servo test!");
  Serial.println("voor Hans Schaap!");
  Serial.println("");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos werken met ~60 Hz updates
  pinMode(switch_pin0, INPUT);
}

/*
 * angleToPulse(int ang)
 * gets angle in degree and returns the pulse width
 * also prints the value on seial monitor
 * written by Ahmad Nejrabi for Robojax, Robojax.com
 */
int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max
   //Serial.print("Angle: ");Serial.print(ang);
   //Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
void turn_left(){

   for( int angle =0; angle<181; angle +=5){
    delay(50);
    pwm.setPWM(0, 0, angleToPulse(angle) );
  }
    delay(1000);
}

void turn_right(){

  for( int angle =181; angle>5; angle -=5){
    delay(50);
    pwm.setPWM(0, 0, angleToPulse(angle) );
  }
  delay(1000);
}

void check_switch(){

  // test voor een verandering:
    if (status_servo0 == digitalRead(switch_pin0)){
      //Serial.println(" No change detected" );
      return;
    } else {
      //Serial.println(" Change detected" );
      status_servo0=digitalRead(switch_pin0);
      //Serial.print("De status van pin 4 = :");
      Serial.println(digitalRead(switch_pin0));

      if (status_servo0 == 1){
       turn_left();
      } else {
        turn_right();
      }

    }
  }

// De code binnen de void loop() functie moet je aanpasen voor wat je wilt. Ik test de positie van de schakelaars iedere keer en doe dan wat
void loop() {
check_switch();

}
