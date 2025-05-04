#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

// Declaração dos pinos
extern int button_right;

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

void clear_grid();
void decodePiece(uint8_t *piece, const uint16_t bitmask);
void add_piece_to_grid();
void remove_piece_from_grid();
int is_right_pressed(int dx);

#endif
