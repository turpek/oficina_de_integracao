#include <cstdint>

#define NUM_PIECE_TYPES     7
#define NUM_ROTATION        4

/*                            Peça I
 *
 *   Rotacional 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *       0000         0010           0000           0100
 *       1111         0010           0000           0100
 *       0000         0010           1111           0100
 *       0000         0010           0000           0100
 * Hex  0x0F00       0x2222          0x00F0        0x4444
 *
 *                            Peça L
 *
 *    Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *        0010           0100           0000           1100          
 *        1110           0100           1110           0100          
 *        0000           0110           1000           0100          
 *        0000           0000           0000           0000          
 * Hex   0x2E00         0x4460         0x0E80         0xC440
 *
 *                            Peça J
 *
 *  Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *      1000          0110           0000           0100
 *      1110          0100           1110           0100
 *      0000          0100           0010           1100
 *      0000          0000           0000           0000
 * Hex 0x8E00        0x6440         0x1CA0         0xFCC0
 */

uint16_t piece_I[NUM_ROTATION] = {0x0F00, 0x2222, 0x00F0, 0x4444};
uint16_t piece_L[NUM_ROTATION] = {0x2E00, 0x4460, 0x0E80, 0xC440};
uint16_t piece_J[NUM_ROTATION] = {0x8E00, 0x6440, 0x0000, 0x0000};


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
