#include "Motor.h"
#include "Sensor.h"
#include "PID.h"

volatile int16_t ticksL = 0;
volatile int16_t ticksR = 0;
int16_t finalTick = 0;
int16_t avTicks = 0;


int minpwm = 46;


float pwmd = 0.0;
float pwmr = 0.0;
float pwms = 0.0;

float lmpwm = 0.0;
float rmpwm = 0.0;



PIDController pid_dist;
PIDController pid_angle;
PIDController pid_Dsen;
PIDController pid_Lsen;
PIDController pid_Rsen;

void setPID() {

  ///distance controller
  pid_dist.limMax = /*60*/100;
  pid_dist.limMin = /*-60*/ -100;
  pid_dist.Kp = /*22.3*/0.5;
  pid_dist.Kd = 0;
  pid_dist.Ki = 0;
  pid_dist.tau = 0.02;
  pid_dist.T = 0.01;

  pid_dist.limMaxInt = 0.0;
  pid_dist.limMinInt = 0.0;

  ///angle controller

  pid_angle.limMax = /*100*/100;
  pid_angle.limMin = /*-100*/ -100;
  pid_angle.Kp = 0.5;
  pid_angle.Kd = 0;
  pid_angle.Ki = 0;
  pid_angle.tau = 0.02;
  pid_angle.T = 0.01;

  pid_angle.limMaxInt = 0.0;
  pid_angle.limMinInt = 0.0;


  //  DiffSensorController
  pid_Dsen.limMax = 60.0;
  pid_Dsen.limMin = -60.0;
  pid_Dsen.Kp = 0.99;
  pid_Dsen.Kd = 0.1;
  pid_Dsen.Ki = 0;
  pid_Dsen.tau = 0.02;
  pid_Dsen.T = 0.01;

  pid_Dsen.limMaxInt = 0.0;
  pid_Dsen.limMinInt = 0.0;

  //  LeftSensorController
  pid_Lsen.limMax = /*100.0*/85;
  pid_Lsen.limMin = /*-100.0*/ -85;
  pid_Lsen.Kp = 1.1;
  pid_Lsen.Kd = 0.6;
  pid_Lsen.Ki = 0;
  pid_Lsen.tau = 0.02;
  pid_Lsen.T = 0.01;

  pid_Lsen.limMaxInt = 0.0;
  pid_Lsen.limMinInt = 0.0;


  //  RightSensorController
  pid_Rsen.limMax = 85.0;
  pid_Rsen.limMin = -85.0;
  pid_Rsen.Kp = 1.1;
  pid_Rsen.Kd = /*0.11*/ 0.5;
  pid_Rsen.Ki = 0;
  pid_Rsen.tau = 0.02;
  pid_Rsen.T = 0.01;

  pid_Rsen.limMaxInt = 0.0;
  pid_Rsen.limMinInt = 0.0;


  PIDController_Init(&pid_dist);
  PIDController_Init(&pid_angle);
  PIDController_Init(&pid_Lsen);
  PIDController_Init(&pid_Rsen);
  PIDController_Init(&pid_Dsen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void countTicksL() {
  if (digitalRead(Lenc2) == 0) {
    ticksL++;
  } else {
    ticksL--;
  }
}

void countTicksR() {
  if (digitalRead(Renc2) == 0) {
    ticksR++;
  } else {
    ticksR--;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void motorMotion(float lpwm, float rpwm) {

  if ((abs(lpwm) < minpwm) && abs(lpwm) != 0)
  {
    if (lpwm < 0)
      lpwm = -minpwm;
    else
      lpwm = minpwm;
  }


  if (abs(rpwm) < minpwm && abs(rpwm) != 0)
  {
    if (rpwm < 0)
      rpwm = -minpwm;
    else
      rpwm = minpwm;
  }

  analogWrite(eLeft, abs(lpwm));
  analogWrite(eRight, abs(rpwm));

  if (lpwm > 0) {
    digitalWrite(fLeft, HIGH);
    digitalWrite(bLeft, LOW);
  }

  else if (lpwm < 0) {
    digitalWrite(bLeft, HIGH);
    digitalWrite(fLeft, LOW);
  }

  else {
    digitalWrite(fLeft, LOW);
    digitalWrite(bLeft, LOW);
  }

  if (rpwm > 0) {
    digitalWrite(fRight, HIGH);
    digitalWrite(bRight, LOW);
  }

  else if (rpwm < 0) {
    digitalWrite(bRight, HIGH);
    digitalWrite(fRight, LOW);
  }

  else {
    digitalWrite(fRight, LOW);
    digitalWrite(bRight, LOW);
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stopbot() {
  analogWrite(eLeft, 0);
  analogWrite(eRight, 0);
  digitalWrite(fLeft, LOW);
  digitalWrite(bLeft, LOW);
  digitalWrite(fRight, LOW);
  digitalWrite(bRight, LOW);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void turnRight() {
  finalTick = 1105;
  int fla = 55;
  int co = 0;
  int16_t oldTicksDiff = 9999; //as avTicks is also 0 initially

  while (fla) {

    PIDController_Update(&pid_dist, finalTick, (ticksL - ticksR));
    PIDController_Update(&pid_angle, 0, (ticksL + ticksR));
    motorMotion(pid_dist.out+pid_angle.out, -pid_dist.out-pid_angle.out);

    if ((ticksL - ticksR) == oldTicksDiff)
    {
      co = co + 1;
    }

    else
      co = 0;

    if (co == 4 && abs(finalTick - ticksL + ticksR) < 1)
    {
      fla = 0;
    }

    oldTicksDiff = ticksL - ticksR;
    
  }
  stopbot();
  delay(2000);
  ticksL = 0;
  ticksR = 0;
  avTicks = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void turnLeft() {
  finalTick = 1105;
  int fla = 55;
  int co = 0;
  int16_t oldTicksDiff = 9999; //as avTicks is also 0 initially

  while (fla) {

    PIDController_Update(&pid_dist, finalTick, (ticksR - ticksL));
    PIDController_Update(&pid_angle, 0, (ticksR + ticksL));
    motorMotion(-pid_dist.out-pid_angle.out, pid_dist.out+pid_angle.out);

    if ((ticksR - ticksL) == oldTicksDiff)
    {
      co = co + 1;
    }

    else
      co = 0;

    if (co == 4 && abs(finalTick - ticksR + ticksL) < 1)
    {
      fla = 0;
    }



    oldTicksDiff = ticksR - ticksL;



  }
  //  flag = false;/
  stopbot();
  delay(2000);
  ticksL = 0;
  ticksR = 0;
  avTicks = 0;
  /*
  L = false;
  R = F;
  F = L;
  */
//    read_quad_sensors();/
//    detectWalls();/

}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void uTurn() {

  finalTick = 2 * 1105;
  int fla = 55;
  int co = 0;
  int16_t oldTicksDiff = 9999; //as avTicks is also 0 initially

  while (fla) {

    PIDController_Update(&pid_dist, finalTick, (ticksR - ticksL));
    PIDController_Update(&pid_angle, 0, (ticksL + ticksR));
    motorMotion(-pid_dist.out, pid_dist.out);

    if ((ticksR - ticksL) == oldTicksDiff)
    {
      co = co + 1;
    }

    else
      co = 0;

    if (co == 4 && abs(finalTick - ticksR + ticksL) < 4)
    {
      fla = 0;
    }

    oldTicksDiff = ticksR - ticksL;


  }
  stopbot();
  delay(500);
  ticksL = 0;
  ticksR = 0;
  avTicks = 0;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moveFS(float distance) {

  //1 ticks equals 0.01713596cm
  finalTick = (int)(58.38 * distance);  //distance in cm  //4.2cm dia //770 ticks
  while(avTicks!=finalTick){
    
    avTicks=(int)(0.5 * ticksL + 0.5 * ticksR);
    
    PIDController_Update(&pid_dist, finalTick, avTicks);
    PIDController_Update(&pid_angle, 0, (ticksL - ticksR));

    pwmd = pid_dist.out;
    pwmr = pid_angle.out;

    lmpwm = pwmd + pwmr;
    rmpwm = pwmd - pwmr;
    
    motorMotion(lmpwm, rmpwm);
/*
  Serial.print(ticksL);
  Serial.print("\t");
  Serial.print(ticksR);
  Serial.print("\t");
  Serial.println(pwmd);
  */
  }
  stopbot();
  delay(2000);
  ticksL = 0;
  ticksR = 0;
  avTicks = 0;
}
