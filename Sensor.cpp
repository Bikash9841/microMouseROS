#include "Sensor.h"

uint16_t dist[4] = {0};
uint16_t distOld[4]={0};

bool F = false;
bool R = true ;
bool L = true;


VL53L0X sensor[4];


void setID() {  //all sensors in reset/(OFF)
  digitalWrite(xshutFrontRight, LOW);
  digitalWrite(xshutFrontLeft, LOW);
  digitalWrite(xshutRight, LOW);
  digitalWrite(xshutLeft, LOW);
  delay(10);

  // all sensors is ON
  digitalWrite(xshutFrontRight, HIGH);
  digitalWrite(xshutFrontLeft, HIGH);
  digitalWrite(xshutRight, HIGH);
  digitalWrite(xshutLeft, HIGH);

  delay(10);

  // keeping front sensor ON while turning OFF sensors on the LEFT and RIGHT

  digitalWrite(xshutFrontLeft, LOW);
  digitalWrite(xshutFrontRight, HIGH);
  digitalWrite(xshutRight, LOW);
  digitalWrite(xshutLeft, LOW);
  delay(10);
  sensor[frontRight].setAddress(frontAddressRight); //setting the address (API mai bhako function raixa yo)
  delay(10);
  Serial.println("front right done");    //debugging purpose ko laagi print matra haaneyko

  digitalWrite(xshutFrontLeft, HIGH);
  digitalWrite(xshutRight, LOW);
  digitalWrite(xshutLeft, LOW);
  delay(10);
  sensor[frontLeft].setAddress(frontAddressLeft);
  delay(10);
  Serial.println("front left done");

  digitalWrite(xshutRight, HIGH);
  digitalWrite(xshutLeft, LOW);
  delay(10);
  sensor[right].setAddress(rightAddress);
  delay(10);
  Serial.println("right done");


  // keeping front sensor and Left sensor ON while turning OFF sensor on the RIGHT
  digitalWrite(xshutLeft, HIGH);
  delay(10);
  sensor[left].setAddress(leftAddress);
  delay(10);
  Serial.println("left done");
}


void read_quad_sensors() {

  dist[0] = sensor[right].readRangeContinuousMillimeters();
  dist[1] = sensor[frontRight].readRangeContinuousMillimeters();
  dist[2] = sensor[frontLeft].readRangeContinuousMillimeters();
  dist[3] = sensor[left].readRangeContinuousMillimeters();

  dist[0] = 0.97 * dist[0] + 0.03 * distOld[0];
  dist[1] = 0.97 * dist[1] + 0.03 * distOld[1];
  dist[2] = 0.97 * dist[2] + 0.03 * distOld[2];
  dist[3] = 0.97 * dist[3] + 0.03 * distOld[3];

  distOld[0] = dist[0];
  distOld[1] = dist[1];
  distOld[2] = dist[2];
  distOld[3] = dist[3];
  
}

void printDistance() {

  Serial.print(dist[0]);
  Serial.print("\t");
  Serial.print(dist[1]);
  Serial.print("\t");
  Serial.print(dist[2]);
  Serial.print("\t");
  Serial.println(dist[3]);

}

void detectWalls() {

  if (dist[1] < 60 && dist[2] < 100) {
    F = true;
  } else {
    F = false;
  }
  if (dist[0] < 150) {
    R = true;
  } else {
    R = false;
  }
  if (dist[3] < 150) {
    L = true;
  } else {
    L = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wallsInfo() {
  Serial.print(L);
  Serial.print("\t");
  Serial.print(F);
  Serial.print("\t");
  Serial.println(R);
}
