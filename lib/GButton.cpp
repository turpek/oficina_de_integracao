#include "GButton.h"
#include "Arduino.h"

BaseButton::BaseButton(){};

BaseButton::BaseButton(unsigned long interval){
  setInterval(interval);
}

void BaseButton::setLongPressedTime(unsigned long msecs){
  this->longPressTime = msecs;
}

void BaseButton::setInterval(unsigned long msecs){
  this->interval = msecs;
}

void BaseButton::setClickTime(unsigned long msecs) {
  this->clickTime = msecs;
}

void BaseButton::setMultiClickInterval(unsigned long msecs) {
  this->multiClickInterval = msecs;
}

bool BaseButton::justPressed(){
  return justPress;
}

bool BaseButton::isClick(){
  return singleClick;
}

bool BaseButton::isDoubleClick(){
  return doubleClick;
}

bool BaseButton::isMultiClick(){
  return multiClick;
}

bool BaseButton::isPressed(){
  return pressed;
}

bool BaseButton::isLongPressed(){
  return longPressed;
}

bool BaseButton::justReleased(){
  return released;
}

unsigned int BaseButton::getCountMultiClick(){
  return countMultiClick;
}

void BaseButton::updateState(bool state){
  unsigned long currentTime = millis();
  singleClick = false;
  doubleClick = false;
  multiClick = false;
  released = false;
  justPress = false;
  countMultiClick = 0;

  if((currentTime - lastTime) >= interval){
    lastTime = currentTime;
    if(state == true && state != lastState){
      pressed = true;
      justPress = true;
      pressedTime = currentTime;
    }
    else if(state == false && state != lastState){
      released = true;
      pressed = false;
      longPressed = false;
      lastReleaseTime = currentTime;
    }
    lastState = state;
  }

  if(isPressed() && (currentTime - pressedTime) >= longPressTime){
    longPressed = true;
    countClick = 0;
  }
  else if(justReleased() && (currentTime - pressedTime) <= clickTime){
    countClick += 1;
  }

  if(!isPressed() && countClick > 0 && (currentTime - lastReleaseTime) >= multiClickInterval){
    if(countClick == 1){
      singleClick = true;
    }
    else if(countClick == 2){
      doubleClick = true;
    }
    else{
      multiClick = true;
      countMultiClick = countClick;
    }
    countClick = 0;
  }
}


GButton::GButton(){
  setInterval(DEBOUNCING_DELAY);
};

GButton::GButton(int pin, int mode, unsigned long interval)
  : BaseButton(interval),
    pin(pin),
    mode(mode)
{}

void GButton::begin(int pin, int mode, unsigned long interval){
  this->pin = pin;
  this->mode = mode;
  pinMode(pin, mode);
  setInterval(interval);
}

void GButton::setPressedState(int state){
  pressedLevel = state;
}

void GButton::update(){
  updateState(digitalRead(this->pin) == pressedLevel);
}


BaseJoystick::BaseJoystick(int interval)
  :BaseButton(interval)
{};

void BaseJoystick::update(bool state){
  updateState(state);
};

GJoystick::GJoystick(int pinX, int pinY, int deadZone, unsigned long interval):
  pinX(pinX),
  pinY(pinY),
  dx(0),
  dy(0),
  deadZone(deadZone),
  up(interval),
  down(interval),
  left(interval),
  right(interval)
  {}

void GJoystick::setMap(MapFunction custom_map){
  m_mapX = custom_map;
  m_mapY = custom_map;
}

void GJoystick::setMapX(MapFunction custom_map){
  m_mapX = custom_map;
}

void GJoystick::setMapY(MapFunction custom_map){
  m_mapY = custom_map;
}

void GJoystick::setDeadZone(int deadZone){
  this->deadZone = deadZone;
}

void GJoystick::setLongPressedTime(unsigned long msecs){
  up.setLongPressedTime(msecs);
  down.setLongPressedTime(msecs);
  left.setLongPressedTime(msecs);
  right.setLongPressedTime(msecs);
}

void GJoystick::setInterval(unsigned long msecs){
  up.setInterval(msecs);
  down.setInterval(msecs);
  left.setInterval(msecs);
  right.setInterval(msecs);
}

void GJoystick::setClickTime(unsigned long msecs){
  up.setClickTime(msecs);
  down.setClickTime(msecs);
  left.setClickTime(msecs);
  right.setClickTime(msecs);
}

void GJoystick::setMultiClickInterval(unsigned long msecs){
  up.setMultiClickInterval(msecs);
  down.setMultiClickInterval(msecs);
  left.setMultiClickInterval(msecs);
  right.setMultiClickInterval(msecs);
}

void GJoystick::update(){
  dy = m_mapY(analogRead(pinY));
  dx = m_mapX(analogRead(pinX));

  up.update(dy > deadZone);
  down.update(dy < -deadZone);
  left.update(dx < -deadZone);
  right.update(dx > deadZone);
}

int defaultMap(int value){
  return map(value, 0, 1023, -512, 512);
}
