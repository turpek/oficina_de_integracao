#include <cstdint>

#define NUM_PIECE_TYPES     7
#define NUM_ROTATION        4

/*                      Peça I
 *
 *    modo normal Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *       0000         0010           0000           0100
 *       1111         0010           0000           0100
 *       0000         0010           1111           0100
 *       0000         0010           0000           0100
 * Hex  0x0F00
 */

uint16_t piece_I[NUM_ROTATION] = {0x0F00, 0x2222, 0x00F0, 0x4444};


void decodePiece(uint8_t *piece, const uint16_t bitmask){
  for(int i=0, bshift=15; i<15; i++, bshift--){
    piece[i] = bitmask >> bshift & 1;
  }
}

#ifndef UNIT_TEST
int main(){

  return 0;
}
#endif
