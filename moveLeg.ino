#include "twoJointLeg.h"
#include <Servo.h>

twoJointLeg leg1;
twoJointLeg leg2;
twoJointLeg leg3;
twoJointLeg leg4;
twoJointLeg leg5;
twoJointLeg leg6;

int leg1Gate[3] = {-1, 0, 1};
int leg2Gate[3] = {1, -1, 0};
int leg3Gate[3] = {0, 1, -1};

void setup() 
{
  Serial.begin(9600);
  leg1.SetKnee(12);
  leg1.SetHip(13);
  leg2.SetKnee(49);
  leg2.SetHip(50);
  leg3.SetKnee(45);
  leg3.SetHip(44);
  leg4.SetKnee(29);
  leg4.SetHip(46);
  leg5.SetKnee(27);
  leg5.SetHip(28);
  leg6.SetKnee(2);
  leg6.SetHip(3);
  stand();
}

void stand()
{
  leg1.MoveLeg(90, 90);
  leg2.MoveLeg(40, 90);
  leg3.MoveLeg(90, 90);
  leg4.MoveLeg(90, 40);
  leg5.MoveLeg(140, 60);
  leg6.MoveLeg(120, 90);
}

int flip = 1;
void walk1()
{
  
  int hipAdjust=40 * flip;
  //int kneeAdjust=-40 * flip;
  int kneeAdjust = 0;
  leg1.writeState();
  leg1.MoveLegForward(kneeAdjust, hipAdjust);
  delay(1000);
  leg2.MoveLegForward(kneeAdjust, hipAdjust);
  delay(1000);
  leg3.MoveLegForward(kneeAdjust, hipAdjust);
  delay(1000);
  flip *= -1;
}

//Three states 1, 0, -1
//going 60 than -60, 60 than -60
//Needs to go
// 60, -60, -60, 60, 60, -60, -60
int pulse = 1;
void adjecentLegWalk()
{
  /*int kneeAdjust = -60 * flip;
  leg1.MoveLegForward(kneeAdjust, 0);
  leg4.MoveLegForward(kneeAdjust * -1, 0);
  leg1.writeState();
  delay(1000);
  pulse++;
  if(pulse >= 2){
    flip *= -1;
    pulse=0;
  }*/
  leg1.KneeWalk();
  leg4.KneeWalk();
}

//AdjecentLegs ignored.
//This walk will move each leg one at a time.
//Gate sync
//Leg2 knee up hip forward
//leg6 hip backward
//Leg2 knee down
//Leg6 knee up
//Leg2 hip backward
//leg6 hip forward x 2
//leg6 knee down
//leg2 knee backward
//leg6 hip backward
//leg2 knee up hip forward x 2

//start walk one leg up and one leg in the back position
//leg2 is knee +1 hip +1
//leg6 is knee 0 hip -1
//leg2 knee 0
//leg6 knee +1
//leg2 hip 0
//leg6 hip 0


//leg6 knee down

void fourLegWalk()
{
  leg1.MoveLegForward(-100,0);
  leg4.MoveLegForward(-100,0);
}

int pin = -1;
void loop() 
{
  int newInput = Serial.parseInt();
  if(newInput != 0){
    pin = newInput;
    stand();
    delay(1000);
  }
  switch(pin)
  {
    
    case -1:
      Serial.print("Waiting for command \n");
      stand();
    break;
    case 1:
      walk1();
    break;
    case 2:
      adjecentLegWalk();
    break;
    case 3:
      fourLegWalk();
    break;
  }
}
