#include <Arduino.h>
#include <Servo.h>
#include "twoJointLeg.h"

twoJointLeg::twoJointLeg()
{
  _legState=1;
  _delaySpeed = 1000;
  _legSpeed = 60;
  _pulseBetweenStateChange = 2;
  _kneeWalkMaxState=4;
}

void twoJointLeg::SetKnee(int knee)
{
  _Knee = knee;
  _ServoKnee.attach(_Knee);
}

void twoJointLeg::SetHip(int hip)
{
  _Hip = hip;
  _ServoHip.attach(_Hip);
}

void twoJointLeg::MoveLeg(int kneeValue, int hipValue)
{
  _ServoKnee.write(kneeValue);
  _ServoHip.write(hipValue);
}

void twoJointLeg::MoveLegForward(int kneeInc, int hipInc)
{
  MoveLeg(_ServoKnee.read() + kneeInc, _ServoHip.read() + hipInc);
}

void twoJointLeg::HipWalk()
{
}

//The Math for this
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
void twoJointLeg::KneeWalk()
{
  switch(_legState)
  {
    case 0:
      MoveLegForward(+30, _ServoHip.read());
    break;
    case 1:
      MoveLegForward(-30, _ServoHip.read());
    break;
  }
  delay(_delaySpeed);
  kneeWalkStateUpdate();
}

void twoJointLeg::kneeWalkStateUpdate()
{
  _currentPulse++;
  if(_pulseBetweenStateChange >= _currentPulse){
    _legState++;
    if(_legState >= _kneeWalkMaxState)
    {
      _legState=0;
    }
    _currentPulse=0;
  }
}

void twoJointLeg::writeState()
{
  Serial.print("Knee: ");
  Serial.print(_Knee);
  Serial.print(_ServoKnee.read());
  Serial.print(" Hip: ");
  Serial.print(_Hip);
  Serial.print(_ServoHip.read());
  Serial.print("\n");
  Serial.print(_legState);
  Serial.print("\n");
}
