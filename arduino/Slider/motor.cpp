#include "motor.h"

Motor::Motor(int stepPin, int dirPin, int enablePin){
  stepPin_ = stepPin;
  dirPin_ = dirPin;
  enablePin_ = enablePin;
  position_ = 0;
  target_ = 0;

  //From EEPROM in the future
  //set from setup submenu
  stepTime_ = 600;
  length_ = 240;
  stepBymm_ = 75;
  time_ = 10;
  //

  stepsDistance_ = length_ * stepBymm_;
  working_ = false;
  finished_ = false;
  direction_ = true;
  loop_ = false;

  pinMode(stepPin_,OUTPUT);
  pinMode(dirPin_,OUTPUT);
  pinMode(enablePin_,OUTPUT);

  digitalWrite(enablePin_, HIGH);
}

/*
*   Move the motor one step
*/
void Motor::move(){

  //If it is'n necesary, do not move the motor
  if(working_ && position_ != target_){
    //Enable motor
    digitalWrite(enablePin_, LOW);

    //Set directión
    if(direction_)
      digitalWrite(dirPin_, HIGH);
    else
      digitalWrite(dirPin_, LOW);

    //Step
    digitalWrite(stepPin_, HIGH);
    delayMicroseconds(stepTime_/2);
    digitalWrite(stepPin_, LOW);
    delayMicroseconds(stepTime_/2);

    steps_--;

    //If we are at the end
    if(steps_ == 0){
      //Update the current position
      position_ = target_;
      //If we are in loop mode
      if(loop_){
        if(position_ == 240){
          this->setTime(time_, 0);
          loop_ = true;
        }
        else if (position_ == 0){
          this->setTime(time_, 240);
          loop_ = true;
        }
        else{
          working_ = false;
          finished_ = true;
        }
      }
      //If we are NOT in loop position, it has finished the movement
      else {
        working_ = false;
        finished_ = true;
      }
    }
  }
  else {
  //Disable motor
  digitalWrite(enablePin_, HIGH);
  }
}

int Motor::getPosition(){
  return position_;
}

void Motor::setPosition(int position){
  position_ = position;
}

int Motor::getTarget(){
  return target_;
}

/*
*   This method update the target_, steps_ and direction_
*/
void Motor::setTarget(int target){
  stepTime_ = 600;
  target_ = target;
  steps_ = (target_ - position_)*stepBymm_;

  //Change direction if necccesary
  if(steps_ < 0){
    steps_ = steps_*(-1);
    direction_ = false;
  } else {
    direction_ = true;
  }

  loop_ = false;
}

int Motor::getStepTime(){
  return stepTime_;
}

void Motor::setStepTime(int stepTime){
  stepTime_ = stepTime;
}

bool Motor::getWorking(){
  return working_;
}

void Motor::setWorking(bool working){
  working_ = working;
}

long int Motor::getStepsDistance(){
  return stepsDistance_;
}

unsigned long int Motor::getTime(){
  return time_;
}

/*
*   This method update time_, target_, steps_ and direction_
*/
void Motor::setTime(unsigned long int timming, int target){
  time_ = timming;
  stepTime_ = (time_ * 1000000) / stepsDistance_;

  target_ = target;
  steps_ = (target_ - position_)*stepBymm_;

  //Change direction if necesary
  if(steps_ < 0){
    steps_ = steps_*(-1);
    direction_ = false;
  } else {
    direction_ = true;
  }

  loop_ = false;

}

bool Motor::getFinished(){
  return finished_;
}

void Motor::setFinished(bool finished){
    finished_ = finished;
}

bool Motor::getLoop(){
  return loop_;
}

void Motor::setLoop(bool loop){
  this->setTime(time_, 240);
  loop_ = loop;  
}

int Motor::getlength(){
  return length_;
}

