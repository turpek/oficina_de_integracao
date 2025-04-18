#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

// Declaração (não definição!)
extern uint16_t piece_I[];
extern uint16_t piece_L[];
extern uint16_t piece_J[];
extern uint16_t piece_T[];
extern uint16_t piece_S[];
extern uint16_t piece_Z[];
extern uint16_t piece_O[];


void decodePiece(uint8_t *piece, const uint16_t bitmask);

#endif
