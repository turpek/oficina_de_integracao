#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>

// Declaração (não definição!)
extern uint16_t piece_I[];


void decodePiece(uint8_t *piece, const uint16_t bitmask);

#endif
