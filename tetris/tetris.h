#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>
#include "GButton.h"


#define NUM_PIECE_TYPES     7
#define NUM_ROTATION        4
#define NUM_KICKS           5
#define NUM_KICKS_I         3
#define PIECE_I             6

// Definição do tamanho do grid, ou seja, do tamanho da matriz de LEDs
#define GRID_W 8
#define GRID_H 20
#define GRID_COUNT (GRID_W * GRID_H)
#define LED_COUNT 128
#define LED_PIN 6

// Opções do joystick
#define JOYSTICK_DEAD_ZONE 30
#define JOYSTICK_PIN 2


// Dimensões das peças
#define PIECE_W 4
#define PIECE_H 4

// Coordenada do spawner
#define INITIAL_PIECE_X        3
#define INITIAL_PIECE_Y        2
#define INITIAL_PIECE_ROTATION 0


// Opções do tempo de descida
#define INITIAL_FALL_DELAY 1000
#define MINIMUM_FALL_DELAY 100
#define INITIAL_LAST_FALL_DELAY 0
#define INITIAL_LOCK_DELAY 500
#define SOFT_DROP_FACTOR 4
#define MOVE_DELAY 100
#define DEBOUNCE_TIME 40
#define LONG_PRESSED_TIME 100

#define MAX7219_Data_IN 3
#define MAX7219_Chip_Select  4
#define MAX7219_Clock 5




// Declaração dos pinos
extern int btn_left;
extern int btn_right;
extern int btn_down;
extern int btn_up;
extern int btn_pause;
extern int btn_start;


extern GButton button_up;
extern GButton button_down;
extern GButton button_right;
extern GButton button_left;
extern GButton button_start;
extern GButton button_pause;
extern GJoystick joystick;

// Declaração (não definição!)
extern uint16_t piece_I[];
extern uint16_t piece_L[];
extern uint16_t piece_J[];
extern uint16_t piece_T[];
extern uint16_t piece_S[];
extern uint16_t piece_Z[];
extern uint16_t piece_O[];

extern uint16_t* pieces[];
extern uint32_t piece_colors[];
extern uint32_t grid[];

extern int piece_id;
extern int piece_rotation;
extern int piece_x;
extern int piece_y;
extern int top_row;

extern unsigned long fall_delay;
extern unsigned long last_fall_delay;
extern unsigned long last_lock_delay;

void clear_grid();
void decodePiece(uint8_t *piece, const uint16_t bitmask);
void update_piece();
void add_piece_to_grid();
void remove_piece_from_grid();
void update_top_row();
void clear_row(int y);
void push_rows(int y, int dy, int rows);
bool row_is_full(int y);
int clear_rows();
bool is_right_pressed();
bool is_left_pressed();
bool is_down_pressed();
bool is_up_pressed();
int check_left_border(int dx);
int check_right_border(int dx);
bool check_botton_border(int dy);
bool has_no_collision(int dx, int dy);
bool try_rotate();
void start_fall_delay();
bool is_fall_delay_elapsed();
void start_lock_delay();
void reset_lock_delay();
bool is_lock_delay_elapsed();
bool is_lock_delay_active();
void set_score_check();
void reset_score_check();
bool can_score_check();
bool can_fall();
bool has_piece_moved();
void set_piece_moved();
void reset_piece_moved();
bool try_soft_drop();
void react_to_player();
void update_game_state();
void update_buttons();
void setup();

#ifdef ENABLE_TEST

uint8_t* get_test_piece();
void clear_piece();
#endif


#endif
