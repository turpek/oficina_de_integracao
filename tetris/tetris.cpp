#include <cstdint>
#include "tetris/Mock_Arduino.h"
#include <stdio.h>

#define NUM_PIECE_TYPES     7
#define NUM_ROTATION        4

// Definição do tamanho do grid, ou seja, do tamanho da matriz de LEDs
#define GRID_W 8
#define GRID_H 16
#define LED_COUNT (GRID_H * GRID_W)
#define LED_PIN 6

// Opções do joystick
#define JOYSTICK_DEAD_ZONE 30
#define JOYSTICK_PIN 2


// Dimensões das peças
#define PIECE_W 4
#define PIECE_H 4

int button_left = 8;
int button_right = 9;

//

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
 *
 *                            Peça T
 *  Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *      0100           0100           0000           0100
 *      1110           0110           1110           1100
 *      0000           0100           0100           0100
 *      0000           0000           0000           0000
 * Hex 0x4E00         0x4640         0x0E40         0x4C40
 *
 *                            Peça S
 *  Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *      0110           0100           0000           1000
 *      1100           0110           0110           1100
 *      0000           0010           1100           0100
 *      0000           0000           0000           0000
 * Hex 0x6C00         0x4620         0x06C0         0x8C40
 *
 *                            Peça Z
 *   Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *       1100           0010           0000           0100
 *       0110           0110           1100           1100
 *       0000           0100           0110           1000
 *       0000           0000           0000           0000
 * Hex  0xC600         0x2640         0x0C60         0x4C80
 *
 *                            Peça O
 *   Rotacionado 0x Rotacionado 1x Rotacionado 2x Rotacionado 3x
 *       1100           1100           1100           1100
 *       1100           1100           1100           1100
 *       0000           0000           0000           0000
 *       0000           0000           0000           0000
 * Hex  0xCC00         0xCC00         0xCC00         0xCC00
 */

uint16_t piece_I[NUM_ROTATION] = {0x0F00, 0x2222, 0x00F0, 0x4444};
uint16_t piece_L[NUM_ROTATION] = {0x2E00, 0x4460, 0x0E80, 0xC440};
uint16_t piece_J[NUM_ROTATION] = {0x8E00, 0x6440, 0x0E20, 0x44C0};
uint16_t piece_T[NUM_ROTATION] = {0x4E00, 0x4640, 0x0E40, 0x4C40};
uint16_t piece_S[NUM_ROTATION] = {0x6C00, 0x4620, 0x06C0, 0x8C40};
uint16_t piece_Z[NUM_ROTATION] = {0xC600, 0x2640, 0x0C60, 0x4C80};
uint16_t piece_O[NUM_ROTATION] = {0xCC00, 0xCC00, 0xCC00, 0xCC00};

uint16_t* pieces[NUM_PIECE_TYPES] = {
  piece_S, // 0
  piece_Z, // 1
  piece_L, // 2
  piece_J, // 3
  piece_O, // 4
  piece_T, // 5
  piece_I, // 6
};

uint32_t piece_colors[NUM_PIECE_TYPES] = {
  0x009900, // green S
  0xFF0000, // red Z
  0xFF8000, // orange L
  0x000044, // blue J
  0xFFFF00, // yellow O
  0xFF00FF, // purple T
  0x00FFFF,  // cyan I
};

int piece_id = 0;
int piece_rotation = 0;
static uint8_t piece[16] = {0};
int piece_x = 0;
int piece_y = 0;

uint32_t grid[LED_COUNT] = {0};

void clear_grid(){
  for(int i=0; i < LED_COUNT; i++){
    grid[i] = 0;
  }
}

void decodePiece(uint8_t *piece, const uint16_t bitmask){
  for(int i=0, bshift=15; i<15; i++, bshift--){
    piece[i] = bitmask >> bshift & 1;
  }
}


void update_piece(){
  decodePiece(piece, pieces[piece_id][piece_rotation]);
}

void add_piece_to_grid(){
  for(int y=0; y < PIECE_H; ++y){
    for(int x=0; x < PIECE_W; ++x){
      int dx = piece_x + x;
      int dy = piece_y + y;
      if((dx < 0 || dx > GRID_W) || (dy < 0 || dy > GRID_H))
        continue;
      else if(piece[y*PIECE_W+x] == 1)
        grid[dy*GRID_W+dx] = piece_colors[piece_id];
    }
  }

};


void remove_piece_from_grid(){
  for(int y=0; y < PIECE_H; ++y){
    for(int x=0; x < PIECE_W; ++x){
      int dx = piece_x + x;
      int dy = piece_y + y;
      if((dx < 0 || dx > GRID_W) || (dy < 0 || dy > GRID_H))
        continue;
      else if(piece[y*PIECE_W+x] == 1)
        grid[dy*GRID_W+dx] = 0;
    }
  }

};


int is_right_pressed(int dx){
  return (dx < -JOYSTICK_DEAD_ZONE) || (digitalRead(button_right) == LOW);
}

int is_left_pressed(int dx){
  return (dx > JOYSTICK_DEAD_ZONE) || (digitalRead(button_left) == LOW);
}

int check_left_border(){
  if((piece_x - 1) >= 0){
    return 1;
  }

  int overflow = -(piece_x - 1);
  for(int y=0; y < PIECE_H; y++){
    for(int x=0; x < overflow; x++){
      if(piece[y*PIECE_W+x] != 0)
        return 0;
    }

  }
  return 1;
}

int check_right_border(){
  if(piece_x + PIECE_W < GRID_W){
    return 1;
  }

  /*                 Calculo do overflow
   *
   * Devemos calcular o quando a peça sai do grid, para isso devemos calcular a coordenada
   * da extremidade direita da peça com;
   *
   *    xend = piece_x + PIECE_W + 1
   *
   * agora precisamos calcular o quanto a peça saiu do grid;
   *
   *    delx = xend - GRID_W
   *
   * se subtrairmos delx de PIECE_W, encontramos o valor do overflow, isso eh;
   *
   *    overflow = PIECE_W - delx
   *    overflow = PIECE_W - (xend - GRID_W)
   *    overflow = PIECE_W - (piece_x + PIECE_W + 1) + GRID_W
   *    overflow = GRID_W - (piece_x + 1)
   *
   */

  int overflow = GRID_W - (piece_x + 1);
  for(int y=0; y < PIECE_H; y++){
    for(int x=overflow; x < PIECE_W; x++){
      if(piece[y*PIECE_W+x] != 0){
        return 0;
      }
    }
  }
  return 1;
}

bool check_botton_border(){
  if((piece_y + PIECE_H) < GRID_H){
    return true;
  }

  int overflow = GRID_H - (piece_y + 1);
  for(int y=overflow; y < PIECE_H; y++){
    for(int x=0; x < PIECE_W; x++){
      if(piece[y*PIECE_W+x] != 0){
        return false;
      }
    }
  }
  return true;
}

bool has_collision(int dx, int dy){
  for(int y=piece_y+dy, j=0; y < GRID_H && j < PIECE_H; y++, j++){
    if(y < 0)
      continue;
    for(int x=piece_x+dx, i=0; x < GRID_W && i < PIECE_W; x++, i++){
      if(x < 0)
        continue;
      if((grid[y * GRID_W + x] > 0) && (piece[j * PIECE_W + i] > 0))
        return 1;
    }
  }
  return 0;
}

bool can_rotate(){
  int old_rotation = piece_rotation;
  int old_piece_x = piece_x, old_piece_y = piece_y;

  piece_rotation = (piece_rotation + 1) % NUM_ROTATION;
  update_piece();

  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
    return true;
  }

  piece_x = old_piece_x - 1;
  piece_y = old_piece_y;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
    return true;
  }

  piece_x = old_piece_x + 1;
  piece_y = old_piece_y;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y - 1;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y + 1;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x - 2;
  piece_y = old_piece_y;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x + 2;
  piece_y = old_piece_y;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y - 2;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y + 2;
  if(check_left_border() && check_right_border() && !has_collision(0, 0)){
   return true;
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y;
  piece_rotation = old_rotation;
  return false;
}


#ifndef UNIT_TEST
int main(){

  return 0;
}
#endif


#ifdef ENABLE_TEST
uint8_t *get_test_piece(){
  return piece;
}

void clear_piece(){
  for(int i=0; i < LED_COUNT; i++)
    piece[i] = 0;
}
#endif
