#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

// Modos de pino
#define INPUT          0
#define OUTPUT         1
#define INPUT_PULLUP   2
#define INPUT_PULLDOWN 3

// Estados lógicos
#define LOW  0
#define HIGH 1

// Número máximo de pinos simulados
const int MAX_PINS = 20;

inline int pin_modes[MAX_PINS]  = {INPUT};
inline int pin_values[MAX_PINS] = {LOW};


inline void pinMode(int pin, int mode) {
    if (pin < 0 || pin >= MAX_PINS) return;
    pin_modes[pin] = mode;
    // Ajusta valor padrão conforme o modo pull
    if (mode == INPUT_PULLUP) {
        pin_values[pin] = HIGH;
    }
    else if (mode == INPUT_PULLDOWN) {
        pin_values[pin] = LOW;
    }
}


inline void digitalWrite(int pin, int value) {
    if (pin < 0 || pin >= MAX_PINS) return;
    if (pin_modes[pin] != OUTPUT) return;
    pin_values[pin] = (value == HIGH ? HIGH : LOW);
}


inline int digitalRead(int pin) {
    if (pin < 0 || pin >= MAX_PINS) return LOW;
    int mode = pin_modes[pin];
    if (mode == INPUT_PULLUP || mode == INPUT_PULLDOWN || mode == INPUT) {
        return (pin_values[pin] == HIGH ? HIGH : LOW);
    }
    return LOW;
}

#endif
