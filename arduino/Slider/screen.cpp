#include "screen.h"

Screen::Screen(){
  numero_ = "1000";
  position_ = 0;
  entered_ = false;
  subentered_ = false;
}

/*
* Boot the screen and write the RincónIngenieril brand
*/
void Screen::set(){

  TFT screen = TFT(cs, dc, rst);
  screen_ = &screen;
  screen.begin();
  screen.setRotation(180);

  screen.background(0, 0, 0);
  screen.stroke(255, 112, 67);
  screen.setTextSize(1);

  screen.text("RinconIngenieril", 15, 5);
  screen.line(0, 15, 128, 15);
}

/*
*   Show the menu options
*/
void Screen::menu(){
  screen_->fill(0, 0, 0);
  screen_->stroke(0, 0, 0);
  screen_->rect(0, 18, 128, 142);
  screen_->stroke(255, 255, 255);
  screen_->setTextSize(2);
  screen_->text("Position", 15, 30);
  screen_->text("Time", 15, 50);
  screen_->text("Loop", 15, 70);

  this->updateArrow();
}

/*
*   This screen is shown while the motor is moving
*/
void Screen::working(){
  subposition_ = 0;

  screen_->fill(0, 0, 0);
  screen_->stroke(0, 0, 0);
  screen_->rect(0, 18, 128, 142);
  screen_->stroke(255, 255, 255);
  screen_->setTextSize(2);
  screen_->text("Working", 15, 30);

  screen_->setTextSize(1);
  screen_->text("Press to stop", 15, 60);
}

/*
*   This screen guide the user in order to
*   set the next position of the slider
*/
void Screen::byPosition(int position){
  //Clear menu
  screen_->fill(0, 0, 0);
  screen_->stroke(0, 0, 0);
  screen_->rect(0, 18, 128, 142);
  //Write the title
  screen_->stroke(255, 255, 255);
  screen_->setTextSize(2);
  screen_->text("Position", 15, 30);

  //Screen animation, it depends on subposition_ value
  switch (subposition_) {
    case 0:   //The position number is selected
      this->backButton(false);
      this->startButton(false);
      screen_->fill(255,255,255);

      if (!subentered_) screen_->stroke(0, 0, 0);
      else screen_->stroke(255, 0, 0);

      break;
    case 1:   //The back button is selected
      this->backButton(true);
      this->startButton(false);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
    case 2:   //The start button is selected
      this->backButton(false);
      this->startButton(true);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
  }
  screen_->setTextSize(3);
  screen_->rect(15, 70, 92, 30);
  //Get and print the position value
  String numero_string = String(position);
  numero_string.toCharArray(numero_, numero_string.length()+1);
  screen_->text(numero_, 30, 75);
}

/*
*   This screen guide the user in order
*   to set the time with will be used
*   for the complete movement
*/
void Screen::byTime(long int timing){
  //Clear menu
  screen_->fill(0, 0, 0);
  screen_->stroke(0, 0, 0);
  screen_->rect(0, 18, 128, 142);
  //Write the title
  screen_->stroke(255, 255, 255);
  screen_->setTextSize(2);
  screen_->text("Time", 15, 30);

  //Screen animation, it depends on subposition_ value
  switch (subposition_) {
    case 0:   //The time value is selected
      this->backButton(false);
      this->startButton(false);
      screen_->fill(255,255,255);

      if (!subentered_) screen_->stroke(0, 0, 0);
      else screen_->stroke(255, 0, 0);

      break;
    case 1:   //The back button is selected
      this->backButton(true);
      this->startButton(false);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
    case 2:   //The start button is selected
      this->backButton(false);
      this->startButton(true);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
  }
  screen_->setTextSize(3);
  screen_->rect(15, 70, 92, 30);
  //Get and print the time value
  String numero_string = String(timing);
  numero_string.toCharArray(numero_, numero_string.length()+1);
  screen_->text(numero_, 30, 75);

}

void Screen::byLoop(bool state){
  //Clear menu
  screen_->fill(0, 0, 0);
  screen_->stroke(0, 0, 0);
  screen_->rect(0, 18, 128, 142);
  //Wrtie the title
  screen_->stroke(255, 255, 255);
  screen_->setTextSize(2);
  screen_->text("Loop", 15, 30);

  //Get and print the position value
  switch (subposition_) {
    case 0:   //The laps value is selected
      this->backButton(false);
      this->startButton(false);
      screen_->fill(255,255,255);

      if (!subentered_) screen_->stroke(0, 0, 0);
      else screen_->stroke(255, 0, 0);

      break;
    case 1:   //The back button is selected
      this->backButton(true);
      this->startButton(false);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
    case 2:   //The start button is selected
      this->backButton(false);
      this->startButton(true);
      screen_->noFill();
      screen_->stroke(255, 255, 255);
      break;
  }
  screen_->setTextSize(1);
  screen_->rect(15, 70, 92, 30);
  if(state)
    screen_->text("Enable", 40, 80);
  else
    screen_->text("Disable", 40, 80);

}

int Screen::addPosition(){
    position_++;
    if(position_ > 2)  position_ = 0;

}

int Screen::substractPosition(){
    position_--;
    if(position_ < 0)  position_ = 2;

}

int Screen::addSubPosition(){
    subposition_++;
    if(subposition_ > 2)  subposition_ = 0;

}

int Screen::substractSubPosition(){
    subposition_--;
    if(subposition_ < 0)  subposition_ = 2;

  }

/*
*   This method update the arrow
*   position in the menu screen
*/
void Screen::updateArrow(){
  switch(position_){
    case 0:
      screen_->stroke(0, 0, 0);
      screen_->text(">", 0, 50);
      screen_->text(">", 0, 70);
      screen_->stroke(255, 255, 255);
      screen_->text(">", 0, 30);
      break;
    case 1:
      screen_->stroke(0, 0, 0);
      screen_->text(">", 0, 30);
      screen_->text(">", 0, 70);
      screen_->stroke(255, 255, 255);
      screen_->text(">", 0, 50);
      break;
    case 2:
      screen_->stroke(0, 0, 0);
      screen_->text(">", 0, 30);
      screen_->text(">", 0, 50);
      screen_->stroke(255, 255, 255);
      screen_->text(">", 0, 70);
      break;
  }
}

/*
*   This method draw the back button
*/
void Screen::backButton(bool fill){
  if(fill){
    screen_->fill(255,255,255);
    screen_->stroke(0, 0, 0);
  } else {
    screen_->noFill();
    screen_->stroke(255, 255, 255);
  }

  screen_->rect(0, 120, 56, 30);  //rectangulo atras
  screen_->setTextSize(1);
  screen_->text("Back", 15, 130);
}

/*
*   This method draw the start button
*/
void Screen::startButton(bool fill){

  if(fill){
    screen_->fill(255,255,255);
    screen_->stroke(0, 0, 0);
  } else {
    screen_->noFill();
    screen_->stroke(255, 255, 255);
  }

  screen_->rect(66, 120, 62, 30);  //rectangulo start
  screen_->setTextSize(1);
  screen_->text("Start", 80, 130);

}

void Screen::setEntered(bool entered){
    entered_ = entered;
}

bool Screen::getEntered(){
  return entered_;
}

void Screen::setSubEntered(bool entered){
    subentered_ = entered;
}

bool Screen::getSubEntered(){
  return subentered_;
}

int Screen::getPosition(){
  return position_;
}

int Screen::getSubPosition(){
  return subposition_;
}

void Screen::setSubPosition(int position){
  subposition_ = position;
}
