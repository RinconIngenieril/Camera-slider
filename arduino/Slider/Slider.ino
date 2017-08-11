#include "encoder.h"

Screen screen;
Motor motor(5, 6, 7);
Encoder encoder(&screen, &motor);


void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT);

  attachInterrupt(0, clk, FALLING);
  attachInterrupt(1, dt, FALLING);

  screen.set();
  screen.menu();
}

void loop() {
  if(digitalRead(4) == LOW){
    encoder.button();
    delay(10);
  }

  motor.move();
  if(motor.getFinished()){
    encoder.drawSubmenu();
    motor.setFinished(false);
  }


}

void clk(){
  encoder.clockWise();
}
void dt(){
  encoder.counterClockWise();
}
