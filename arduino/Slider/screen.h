#include <TFT.h>
#include <SPI.h>

#define cs   10
#define dc   9
#define rst  8

class Screen{
  public:
    Screen();
    void set();
    void welcome();
    int getPosition();
    void setPosition(int position);
    int getSubPosition();
    void setSubPosition(int position);
    void menu();
    void working();
    void updateArrow();
    void backButton(bool fill);
    void startButton(bool fill);
    int addPosition();
    int substractPosition();
    int addSubPosition();
    int substractSubPosition();
    void setEntered(bool entered);
    bool getEntered();
    void setSubEntered(bool entered);
    bool getSubEntered();
    void byPosition(int position);
    void byTime(long int timing);
    void byLoop(bool state);
  private:
    int position_;
    bool entered_;
    int subposition_;
    bool subentered_;
    TFT* screen_;
    char* numero_;
};
