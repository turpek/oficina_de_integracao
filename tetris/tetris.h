#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

// Declaração dos pinos
extern int button_left;
extern int button_right;
extern int button_down;
extern int button_up;

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

extern unsigned long last_fall_delay;
extern unsigned long last_lock_delay;
extern bool piece_moved;

void clear_grid();
void decodePiece(uint8_t *piece, const uint16_t bitmask);
void update_piece();
void add_piece_to_grid();
void remove_piece_from_grid();
bool is_right_pressed(int dx);
bool is_left_pressed(int dx);
bool is_down_pressed(int dy);
bool is_up_pressed(int dy);
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
bool can_fall();
bool has_piece_moved();
void set_piece_moved();
void reset_piece_moved();

#ifdef ENABLE_TEST

uint8_t* get_test_piece();
void clear_piece();
#endif


#endif
