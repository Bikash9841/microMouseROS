
///NO HEAVY CHANGE

#include "Sensor.h"
#include "Motor.h"
#include "Wire.h"

uint8_t prev=0;
uint8_t curr=0;

void setup() {

//  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);/
//  disableDebugPorts();/
  pinMode(xshutRight, OUTPUT);
  pinMode(xshutFrontRight, OUTPUT);
  pinMode(xshutFrontLeft, OUTPUT);
  pinMode(xshutLeft, OUTPUT);

  Serial.begin(115200);
  Wire.begin();
  setID();
  //  checkDevice();/
  Serial.println(sensor[right].getAddress(), HEX);
  Serial.println(sensor[frontRight].getAddress(), HEX);
  Serial.println(sensor[frontLeft].getAddress(), HEX);
  Serial.println(sensor[left].getAddress(), HEX);
  
  sensor[right].init();
  sensor[frontRight].init();
  sensor[frontLeft].init();
  sensor[left].init();

  sensor[right].setTimeout(400);
  sensor[frontRight].setTimeout(400);
  sensor[frontLeft].setTimeout(400);
  sensor[left].setTimeout(400);

  sensor[right].startContinuous();
  sensor[frontRight].startContinuous() ;
  sensor[frontLeft].startContinuous();
  sensor[left].startContinuous();

  setPID();

  pinMode(eLeft, OUTPUT);
  pinMode(eRight, OUTPUT);
  pinMode(fLeft, OUTPUT);
  pinMode(bLeft, OUTPUT);
  pinMode(fRight, OUTPUT);
  pinMode(bRight, OUTPUT);

  pinMode(Lenc1, INPUT_PULLUP);
  pinMode(Renc1, INPUT_PULLUP);
  pinMode(Renc2, INPUT_PULLUP);
  pinMode(Lenc2, INPUT_PULLUP);
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, HIGH);

  attachInterrupt(digitalPinToInterrupt(Lenc1), countTicksL, RISING);
  attachInterrupt(digitalPinToInterrupt(Renc1), countTicksR, RISING);

  initialise();
}

void loop() {
 
    while (flag) {
      if (flood[boty][botx] != 0) {
        floodfill(botx, boty);
      } else if (flood[boty][botx] == 0) {
        if (count == 0) {
          digitalWrite(PC13,LOW);
          appendDestination(15, 0);
          floodfill2();
          count = 1;
        } else if (count == 1) {
          digitalWrite(PC13,HIGH);
          appendDestination(15, 15);
          floodfill2();
          count = 2;
        } else if (count == 2) {
          digitalWrite(PC13,LOW);
          appendDestination(0, 0);
          floodfill2();
          count = 3;
        } else if (count == 3) {
          // break;
          digitalWrite(PC13,HIGH);
          appendZero();
          floodfill2();
          count = 4;
        } else if (count == 4) {
          break;
          digitalWrite(PC13,LOW);
          appendDestination(0, 0);
          floodfill2();
          count = 5;
        } else if (count == 5) {
          appendZero();
          floodfill2();
          count = 6;
        }
        else if (count == 6) {
          break;
        }
      }
      if (count == 6) {
        turning = toMoveFast(botx, boty, botxP, botyP, orient);
      } else {
        turning = toMove(botx, boty, botxP, botyP, orient);
      }
      if (turning == 'L') {
        turnLeft();
        orientation(&orient, turning);
      } else if (turning == 'R') {
        turnRight();
        orientation(&orient, turning);
      } else if (turning == 'B') {
        turnRight();
        turnRight();
        orientation(&orient, turning);
      }
      moveFS(5);
      botxP = botx;
      botyP = boty;
      updateCoordinates(&botx, &boty, orient);
      detectWalls();
      delay(1);
    //    updateWalls(botx, boty, orient, L, R, F);
    }
    if (flag) {
      flag = false;
    }

//  read_quad_sensors();/
//  printDistance();/
  Serial.print(ticksL);
  Serial.print('\t');
  Serial.println(ticksR);
  delay(100);

}
