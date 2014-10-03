#include <Servo.h>
#include <Arduino.h>

class twoJointLeg
{
  private:
    int _Knee;
    int _Hip;
    Servo _ServoKnee;
    Servo _ServoHip;
    int _legState;
    int _legSpeed;
    int _delaySpeed;
    int _currentPulse;
    int _pulseBetweenStateChange;
    int _kneeWalkMaxState;
    void kneeWalkStateUpdate();
  public:
    twoJointLeg();
    void KneeWalk();
    void HipWalk();
    void writeState();
    void SetKnee(int knee);
    void SetHip(int hip);
    void MoveLeg(int kneeValue, int hipValue);
    void MoveLegForward(int kneeInc, int hipInc);
};
