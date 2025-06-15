#ifndef GBUTTON_H
#define GBUTTON_H

#include "Arduino.h"

#define LONG_PRESS_TIME 400
#define CLICK_TIME 150
#define MULTI_CLICK_INTERVAL 250
#define DEBOUNCING_DELAY 50
#define GJOYSTICK_DEAD_ZONE 100


class BaseButton {

  private:
    bool lastState = false;
    bool singleClick = false;
    bool doubleClick = false;
    bool multiClick = false;
    bool justPress = false;
    bool pressed = false;
    bool longPressed = false;
    bool released = false;
    unsigned int countClick = 0;
    unsigned int countMultiClick = 0;
    unsigned long interval = DEBOUNCING_DELAY;
    unsigned long multiClickInterval = MULTI_CLICK_INTERVAL;
    unsigned long lastTime = 0;
    unsigned long pressedTime = 0;
    unsigned long lastReleaseTime = 0;
    unsigned long longPressTime = LONG_PRESS_TIME;
    unsigned long clickTime = CLICK_TIME;

  public:

    BaseButton();
    BaseButton(unsigned long interval);
    void setLongPressedTime(unsigned long msecs);
    void setInterval(unsigned long msecs);
    void setClickTime(unsigned long msecs);
    void setMultiClickInterval(unsigned long msecs);
    bool justPressed();
    bool isClick();
    bool isDoubleClick();
    bool isMultiClick();
    bool isPressed();
    bool isLongPressed();
    bool justReleased();
    unsigned int getCountMultiClick();

  protected:
    void updateState(bool state);

};


class GButton: public BaseButton {
  private:
    int pin;
    int mode;
    int pressedLevel = LOW;

  public:
    GButton();
    GButton(int pin, int mode, unsigned long interval);
    void begin(int pin, int mode, unsigned long interval);
    void setPressedState(int state);
    void update();
};

typedef int (*MapFunction)(int);

int defaultMap(int value);

class BaseJoystick: public BaseButton{
  public:
    BaseJoystick(int interval);
    void update(bool state);
};


class GJoystick{

  private:
    int pinX;
    int pinY;
    int dx;
    int dy;
    int deadZone;
    MapFunction m_mapY = defaultMap;
    MapFunction m_mapX = defaultMap;

  public:
    BaseJoystick up;
    BaseJoystick down;
    BaseJoystick left;
    BaseJoystick right;

    GJoystick(
        int pinX,
        int pinY,
        int deadZone = GJOYSTICK_DEAD_ZONE,
        unsigned long interval = DEBOUNCING_DELAY
    );
    void setMap(MapFunction custom_map);
    void setMapX(MapFunction custom_map);
    void setMapY(MapFunction custom_map);
    void setDeadZone(int deadZone);
    void setLongPressedTime(unsigned long msecs);
    void setInterval(unsigned long msecs);
    void setClickTime(unsigned long msecs);
    void setMultiClickInterval(unsigned long msecs);
    void update();
};

#endif
