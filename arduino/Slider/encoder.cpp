#include "encoder.h"

Encoder::Encoder(Screen* screen, Motor* motor){
  screen_ = screen;
  motor_ = motor;
  changeTime_ = 20;
}

/*
*   When the rotatory enconder go clock-wise
*/
void Encoder::clockWise(){
  //Timeout to prevent debounce on the rotatory encoder
  if((millis() - time_) > changeTime_){
    time_ = millis();
    // If we are in the menu (getEntered == false),
    // update the position of the arrow
    if(digitalRead(3) == HIGH && screen_->getEntered() == false){
      screen_->addPosition();
      screen_->updateArrow();
    }
    //If we are inside a submenu (getEntered == true)
    else if(digitalRead(3) == HIGH && screen_->getEntered() == true){
      //If we are NOT trying to change the number value (getSubEntered == false)
      if(screen_->getSubEntered() == false)
        screen_->addSubPosition();

      //Draw the submenu
      switch (screen_->getPosition()) {
        case 0:
          //If we are changing the number value
          if(screen_->getSubEntered() == true){
            if(motor_->getTarget() < motor_->getlength())
              motor_->setTarget(motor_->getTarget() + 10);
            else
              motor_->setTarget(0);
          }
          //Draw byPosition submenu and update the position number
          screen_->byPosition(motor_->getTarget());
          break;
        case 1:
          //If we are changing the number value
          if(screen_->getSubEntered() == true)
            motor_->setTime(motor_->getTime() + 10, 240);
          //Draw byTime submenu
          screen_->byTime(motor_->getTime());
          break;
        case 2:
          //If we are changing the value
          if(screen_->getSubEntered() == true)
            motor_->setLoop(!motor_->getLoop());
          //Draw byLoop menu
          screen_->byLoop(motor_->getLoop());
          break;
      }
    }
  }
}

/*
*   When the rotatory encoder go counter-clock-wise
*/
void Encoder::counterClockWise(){
  //Time out to prevent debounce on the rotatory encoder
  if((millis() - time_) > changeTime_){
    time_ = millis();
    // If we are in the menu (getEntered == false)
    // update the position of the arrow
    if(digitalRead(2) == HIGH && screen_->getEntered() == false){
      screen_->substractPosition();
      screen_->updateArrow();
    }
    // If we are inside a submenu (getEntered == true)
    else if(digitalRead(2) == HIGH && screen_->getEntered() == true){
      //If we are NOT trying to change the number value (getSubEntered == false)
      if(screen_->getSubEntered() == false)
        screen_->substractSubPosition();

      //Draw the submenu
      switch (screen_->getPosition()) {
        case 0:
          //If we are changing the value number
          if(screen_->getSubEntered() == true){
            if(motor_->getTarget() > 0)
              motor_->setTarget(motor_->getTarget() - 10);
            else
              motor_->setTarget(motor_->getlength());
          }
          //Draw byPositon submenu
          screen_->byPosition(motor_->getTarget());
          break;
        case 1:
          //If we are changing the value number
          if(screen_->getSubEntered() == true)
            motor_->setTime(motor_->getTime() - 10, 240);
          //Draw byTime submenu
          screen_->byTime(motor_->getTime());
          break;
        case 2:
          //If we are changing the value
          if(screen_->getSubEntered() == true)
            motor_->setLoop(!motor_->getLoop());
          //Draw byLoop menu
          screen_->byLoop(motor_->getLoop());
          break;
      }
    }
  }
}

/*
*   When the button is pressed
*/
void Encoder::button(){
  //Emergency stop when the motor is moving
  if(motor_->getWorking()){
    motor_->setWorking(false);
  }

  //If we are in the menu
  if(!screen_->getEntered()){
    //Draw the submenu
    screen_->setEntered(true);
    this->drawSubmenu();
  }
  //If we are in the submenu
  else {
    //If back button is selected
    if(screen_->getSubPosition() == 1){
      //Go to menu
      screen_->setEntered(false);
      screen_->menu();
    }
    //If start button is selected
    else if (screen_->getSubPosition() == 2) {
      //Start moving and update screen
      motor_->setWorking(true);
      screen_->working();
    }
    //If number is selected
    else {
      //Change status
      if(screen_->getSubPosition() == 0 && !screen_->getSubEntered())
        screen_->setSubEntered(true);
      else
        screen_->setSubEntered(false);

      this->drawSubmenu();

    }
  }


}

void Encoder::drawSubmenu(){
  switch (screen_->getPosition()) {
    case 0:
      screen_->byPosition(motor_->getTarget());
      break;
    case 1:
      screen_->byTime(motor_->getTime());
      break;
    case 2:
      screen_->byLoop(motor_->getLoop());
      break;
  }
}
