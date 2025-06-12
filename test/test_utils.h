#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>
#include "Arduino.h"
#include "GButton.h"


void transform_grid(uint32_t expect_grid[], uint32_t expect_map[], uint32_t color, int size);

extern uint32_t map_piece_S_rx0[];
extern uint32_t map_piece_S_rx1[];
extern uint32_t map_piece_S_rx2[];
extern uint32_t map_piece_S_rx3[];
extern uint32_t map_piece_S_rx0_movX1Y0[];
extern uint32_t map_piece_S_rx0_movX0Y1[];
extern uint32_t map_piece_S_rx0_movX1Y1[];
extern uint32_t map_piece_S_rx0_movX1Y1[];
extern uint32_t map_piece_S_rx0_movX_1Y0[];
extern uint32_t map_piece_S_rx0_movX0Y_1[];
extern uint32_t map_piece_S_rx0_movX_1Y_1[];
extern uint32_t map_piece_S_rx0_movX_1_Y_1[];

extern uint32_t map_piece_S_rx0_movX5Y14[];
extern uint32_t map_piece_S_rx0_movX6Y14[];
extern uint32_t map_piece_S_rx0_movX5Y15[];
extern uint32_t map_piece_S_rx0_movX6Y15[];

extern uint32_t map_rotation_L[];
extern uint32_t map_rotation_I[];
extern uint32_t map_react[];
extern uint32_t map_update_game[];
extern uint32_t map_clear_all[];
extern uint32_t map_push_rows_t1_frame_0[];
extern uint32_t map_push_rows_t1_frame_1[];
extern uint32_t map_push_rows_t2_frame_0[];
extern uint32_t map_push_rows_t2_frame_1[];
extern uint32_t map_row_full[];
extern uint32_t map_push_rows_t3_frame_0[];
extern uint32_t map_push_rows_t3_frame_1[];
extern uint32_t map_clear_rows_t1_frame_0[];
extern uint32_t map_clear_rows_t1_frame_1[];
extern uint32_t map_clear_rows_t2_frame_0[];
extern uint32_t map_clear_rows_t2_frame_1[];
extern uint32_t map_clear_rows_t3_frame_0[];
extern uint32_t map_clear_rows_t3_frame_1[];
extern uint32_t map_clear_rows_t4_frame_0[];
extern uint32_t map_clear_rows_t4_frame_1[];
extern uint32_t map_clear_rows_t5_frame_0[];
extern uint32_t map_clear_rows_t5_frame_1[];
extern uint32_t map_clear_rows_t6_frame_0[];
extern uint32_t map_clear_rows_t6_frame_1[];


template<typename Obj, typename Var>
void make_state(Obj& obj, Var& hardwareVar, Var  stateValue, unsigned long wait) {
    current_time += wait;      // avança o relógio
    hardwareVar = stateValue;  // ex: pin_values[pin] = LOW; ou mock_analog_y = JOYSTICK_UP
    obj.update();              // processa no objeto
}

void button_pressed(GButton& button, int pin, int interval);
void button_release(GButton& button, int pin, int interval);
void button_multiclick(GButton& button, int pin, unsigned long interval);
void button_click(GButton& button, int pin, unsigned long interval, unsigned long elapsed_click);

void joystick_pressed_x(GJoystick& joystick, int state, unsigned long interval);
void joystick_pressed_y(GJoystick& joystick, int state, unsigned long interval);

void joystick_released_x(GJoystick& joystick, unsigned long interval);
void joystick_released_y(GJoystick& joystick, unsigned long interval);

void joystick_click_x(GJoystick& joystick, int state, unsigned long interval, unsigned long elapsed_click);
void joystick_click_y(GJoystick& joystick, int state, unsigned long interval, unsigned long elapsed_click);

void joystick_multiclick_x(GJoystick& joystick, int state, unsigned long interval);
void joystick_multiclick_y(GJoystick& joystick, int state, unsigned long interval);


#endif
