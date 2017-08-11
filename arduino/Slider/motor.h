#include <Arduino.h>

class Motor{
  public:
    Motor(int stepPin, int dirPin, int enablePin);
    void move();
    int getPosition();
    void setPosition(int position);
    int getTarget();
    void setTarget(int target);
    int getStepTime();
    void setStepTime(int stepTime);
    void setWorking(bool working);
    bool getWorking();
    long int getStepsDistance();
    unsigned long int getTime();
    void setTime(unsigned long int timing, int target);
    bool getFinished();
    void setFinished(bool finished);
    bool getLoop();
    void setLoop(bool loop);
  private:
    int stepPin_;
    int dirPin_;
    int enablePin_;
    int position_;
    int target_;
    int stepTime_;
    int stepBymm_;
    int length_;
    long int steps_;
    unsigned long int time_;
    unsigned long int stepsDistance_;
    bool direction_;
    bool working_;
    bool finished_;
    bool loop_;
};
