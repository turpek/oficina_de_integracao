#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NUM_PIECE_TYPES     7
#define NUM_ROTATION        4

// Definição do tamanho do grid, ou seja, do tamanho da matriz de LEDs
#define GRID_W 4
#define GRID_H 4
#define LED_COUNT (GRID_H * GRID_W)
#define LED_PIN 6

//Dimensões das peças
#define PIECE_W 4
#define PIECE_H 4


uint16_t piece_I[NUM_ROTATION] = {0x0F00, 0x2222, 0x00F0, 0x4444};
uint16_t piece_L[NUM_ROTATION] = {0x2E00, 0x4460, 0x0E80, 0xC440};
uint16_t piece_J[NUM_ROTATION] = {0x8E00, 0x6440, 0x0E20, 0x44C0};
uint16_t piece_T[NUM_ROTATION] = {0x4E00, 0x4640, 0x0E40, 0x4C40};
uint16_t piece_S[NUM_ROTATION] = {0x6C00, 0x4620, 0x06C0, 0x8C40};
uint16_t piece_Z[NUM_ROTATION] = {0xC600, 0x2640, 0x0C60, 0x4C80};
uint16_t piece_O[NUM_ROTATION] = {0xCC00, 0xCC00, 0xCC00, 0xCC00};

uint16_t* pieces[NUM_PIECE_TYPES] = {
  piece_S,
  piece_Z,
  piece_L,
  piece_J,
  piece_O,
  piece_T,
  piece_I,
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
int piece_x = 0;
int piece_y = 0;

uint32_t grid[LED_COUNT] = {0};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void decodePiece(uint8_t *piece, const uint16_t bitmask){
  for(int i=0, bshift=15; i<15; i++, bshift--){
    piece[i] = bitmask >> bshift & 1;
  }
}

void clear_grid(){
  for(int i=0; i < LED_COUNT; i++){
    grid[i] = 0;
  }
}

void add_piece_to_grid(){
  uint8_t piece[16] = {0};
  decodePiece(piece, pieces[piece_id][piece_rotation]);

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

void show_grid(){
  for(int i=0; i < LED_COUNT; i++){
    strip.setPixelColor(i, grid[i]);
  }
  strip.show();
  clear_grid();
}

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  add_piece_to_grid();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(piece_id=0; piece_id < NUM_PIECE_TYPES; piece_id++){
    for(piece_rotation=0; piece_rotation < NUM_ROTATION; piece_rotation++){
      add_piece_to_grid();
      show_grid();
      delay(500);
    }
  }
  piece_id = 0;
  piece_rotation = 0;
}
