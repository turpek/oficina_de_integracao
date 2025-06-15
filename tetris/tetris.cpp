#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "GButton.h"
#include "Chrono.h"
#include "tetris.h"


int btn_pause = 7;
int btn_left = 8;
int btn_right = 9;
int btn_down = 10;
int btn_up = 11;
int btn_start = 12;
int joystick_x = A0;
int joystick_y = A1;


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
 {-1, +1},
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

unsigned long fall_delay = INITIAL_FALL_DELAY;
unsigned long last_fall_delay = 0;
unsigned long lock_delay = INITIAL_LOCK_DELAY;
unsigned long last_lock_delay = 0;
static bool locking = false;
static bool piece_moved = false;
static bool score_check = false;
int score = 0;
int top_score = 0;
int count_row = 0;
int level = 0;

int top_row = GRID_H - 1;
uint32_t grid[GRID_COUNT] = {0};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

GButton button_up;
GButton button_down;
GButton button_right;
GButton button_left;
GButton button_start;
GButton button_pause;
GJoystick joystick = GJoystick(A0, A1, JOYSTICK_DEAD_ZONE, DEBOUNCE_TIME);

Chrono moveTimer;

uint8_t bag[NUM_PIECE_TYPES];
uint8_t bag_index = 0;

void shuffle_bag() {
  // Fisher-Yates
  for (int i = NUM_PIECE_TYPES - 1; i > 0; i--) {
    int j = random(i + 1);
    uint8_t tmp = bag[i];
    bag[i] = bag[j];
    bag[j] = tmp;
  }
}


void init_bag() {
  for (uint8_t i = 0; i < NUM_PIECE_TYPES; i++) {
    bag[i] = i;
  }
  shuffle_bag();
  bag_index = 0;
}

uint8_t get_next_piece() {
  if (bag_index >= NUM_PIECE_TYPES) {
    init_bag(); // reembaralha
  }
  return bag[bag_index++];
}

void shift(uint8_t send_to_address, uint8_t send_this_data)
{
  digitalWrite(MAX7219_Chip_Select, LOW);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
  digitalWrite(MAX7219_Chip_Select, HIGH);
}

int mapY(int value) {
  return map(value, 1024, 0, 512, -512);
}

void configButton(){
  button_right.begin(btn_right, INPUT_PULLUP, DEBOUNCE_TIME);
  button_left.begin(btn_left, INPUT_PULLUP, DEBOUNCE_TIME);
  button_up.begin(btn_up, INPUT_PULLUP, DEBOUNCE_TIME);
  button_down.begin(btn_down, INPUT_PULLUP, DEBOUNCE_TIME);
  button_start.begin(btn_start, INPUT_PULLUP, DEBOUNCE_TIME);
  button_pause.begin(btn_pause, INPUT_PULLUP, DEBOUNCE_TIME);
  joystick.setMapY(mapY);
  joystick.setClickTime(300);
  joystick.setMultiClickInterval(350);
  joystick.setLongPressedTime(500);
}

void update_buttons(){
  button_right.update();
  button_left.update();
  button_up.update();
  button_down.update();
  button_start.update();
  button_pause.update();
  joystick.update();
}

bool has_piece_moved(){
  return piece_moved;
}

void set_piece_moved(){
  piece_moved = true;
}

void reset_piece_moved(){
  piece_moved = false;
}

void clear_grid(){
  for(int i=0; i < GRID_COUNT; i++){
    grid[i] = 0;
  }
}

void start_lock_delay(){
  if(!locking){
    locking = true;
    last_lock_delay = millis();
  }
}

void reset_lock_delay(){
  locking = false;
}

// Função para verificar se o jogo está no tempo de lock
bool is_lock_delay_active(){
  return locking;
}

// Função que verifica se o tempo de lock expirou
bool is_lock_delay_elapsed(){
  return is_lock_delay_active() && ((millis() - last_lock_delay) > lock_delay);
}

bool is_fall_delay_elapsed(){
  return (millis() - last_fall_delay) >= fall_delay;
}

void start_fall_delay(){
  last_fall_delay = millis();
}

bool can_fall(){
  return !is_lock_delay_active() && is_fall_delay_elapsed();
}


void update_top_row(){
  if(top_row > piece_y){
    top_row = piece_y;
  }
}

void set_score_check(){
  score_check = true;
}

void reset_score_check(){
  score_check = false;
}

bool can_score_check(){
  return score_check;
}

int grid_index(int x, int y){
  return (y * GRID_W) + x;
}

void show_grid(){

  for(int x=0, i=grid_index(0, 4); x < LED_COUNT; x++, i++){
    strip.setPixelColor(x, grid[i]);
  }
  strip.show();
}

void decodePiece(uint8_t *piece, const uint16_t bitmask){
  for(int i=0, bshift=15; i<16; i++, bshift--){
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
      if((dx < 0 || dx >= GRID_W) || (dy < 0 || dy >= GRID_H))
        continue;
      else if(piece[y*PIECE_W+x] == 1)
        grid[grid_index(dx, dy)] = piece_colors[piece_id];
    }
  }
}


void remove_piece_from_grid(){
  for(int y=0; y < PIECE_H; ++y){
    for(int x=0; x < PIECE_W; ++x){
      int dx = piece_x + x;
      int dy = piece_y + y;
      if((dx < 0 || dx >= GRID_W) || (dy < 0 || dy >= GRID_H))
        continue;
      else if(piece[y*PIECE_W+x] == 1)
        grid[grid_index(dx, dy)] = 0;
    }
  }

};


void clear_row(int y){
  if(y < 0 || y >= GRID_H){
    return;
  }

  for(int x=0; x < GRID_W; x++){
    grid[grid_index(x,  y)] = 0;
  }
}

bool row_is_full(int y){
  for(int x=0; x < GRID_W; x++){
    if(grid[grid_index(x, y)] == 0){
      return 0;
    }
  }
  return 1;
}

void push_rows(int y, int dy, int rows){
  if(y >= GRID_H || dy < 1){
    return;
  }
  for(int j=0; j < rows; j++, y--){
    if((y - dy) < 0){
      break;
    }
    for(int x=0; x < GRID_W; x++){
      grid[grid_index(x, y)] = grid[grid_index(x, y - dy)];
    }
  }

  // Devemos apagar as dy linhas abaixo da peça mais ao top do grid
  y = top_row;
  for(int j=0; j < dy; j++, y++){
    clear_row(y);
  }
  // Agora `top_row` deve ser atualizada, ja que o grid desceu dy vezes
  top_row = y;
}

void collapse_rows(int y, int dy, int rows){
  if(y >= GRID_H || dy < 1){
    return;
  }
  for(int j=0; j < rows; j++, y--){
    if((y - dy) < 0){
      continue;
    }
    for(int x=0; x < GRID_W; x++){
      grid[grid_index(x, y)] = grid[grid_index(x, y - dy)];
    }
  }
}

int clear_rows(){
  int y=piece_y, rows=0;
  for(int dy=0; dy < PIECE_H; dy++){
    if((y + dy) >= GRID_H){
      continue;
    }
    else if(row_is_full(y + dy)){
      rows++;
      collapse_rows(y + dy, 1, dy);
    }
  }

  push_rows(y+rows-1, rows, y-top_row);
  return rows;
}

bool is_right_pressed(){
  return joystick.right.isPressed() || button_right.isPressed();
}

bool is_left_pressed(){
  return joystick.left.isPressed() || button_left.isPressed();
}

bool is_down_pressed(){
  return joystick.down.isPressed() || button_down.isPressed();
}

bool is_up_pressed(){
  return joystick.up.isPressed() || button_up.isPressed();
}

bool is_up_just_pressed(){
  return (joystick.up.justPressed() && !button_up.isPressed()) ||
    (button_up.justPressed() && !joystick.up.isPressed());
}

bool is_start_pressed(){
  return button_start.isClick();
}

bool is_pause_pressed(){
  return button_pause.isClick();
}

int check_left_border(int dx){
  if((piece_x - dx) >= 0){
    return 1;
  }

  int overflow = -(piece_x - dx);
  for(int y=0; y < PIECE_H; y++){
    for(int x=0; x < overflow; x++){
      if(piece[y*PIECE_W+x] != 0)
        return 0;
    }

  }
  return 1;
}

int check_right_border(int dx){
  if(piece_x + PIECE_W < GRID_W){
    return 1;
  }

  /*                 Calculo do overflow
   *
   * Devemos calcular o quando a peça sai do grid, para isso devemos calcular a coordenada
   * da extremidade direita da peça com;
   *
   *    xend = piece_x + PIECE_W + dx
   *
   * agora precisamos calcular o quanto a peça saiu do grid;
   *
   *    delx = xend - GRID_W
   *
   * se subtrairmos delx de PIECE_W, encontramos o valor do overflow, isso eh;
   *
   *    overflow = PIECE_W - delx
   *    overflow = PIECE_W - (xend - GRID_W)
   *    overflow = PIECE_W - (piece_x + PIECE_W + dx) + GRID_W
   *    overflow = GRID_W - (piece_x + dx)
   *
   */

  int overflow = GRID_W - (piece_x + dx);
  for(int y=0; y < PIECE_H; y++){
    for(int x=overflow; x < PIECE_W; x++){
      if(piece[y*PIECE_W+x] != 0){
        return 0;
      }
    }
  }
  return 1;
}

bool check_botton_border(int dy){
  if((piece_y + PIECE_H) < GRID_H){
    return true;
  }

  int overflow = GRID_H - (piece_y + dy);
  for(int y=overflow; y < PIECE_H; y++){
    for(int x=0; x < PIECE_W; x++){
      if(piece[y*PIECE_W+x] != 0){
        return false;
      }
    }
  }
  return true;
}

bool has_no_collision(int dx, int dy){
  for(int y=piece_y+dy, j=0; y < GRID_H && j < PIECE_H; y++, j++){
    if(y < 0)
      continue;
    for(int x=piece_x+dx, i=0; x < GRID_W && i < PIECE_W; x++, i++){
      if(x < 0)
        continue;
      if((grid[grid_index(x, y)] > 0) && (piece[j * PIECE_W + i] > 0))
        return 0;
    }
  }
  return 1;
}


bool _check_rotate(int old_piece_x, int old_piece_y, const int8_t kicks[][2], int num_kicks){
  for(int i=0; i< num_kicks; i++){
    piece_x = old_piece_x + kicks[i][0];
    piece_y = old_piece_y + kicks[i][1];
    if(check_left_border(0) && check_right_border(0) &&
        check_botton_border(0) && has_no_collision(0, 0)){
      return true;
    }
  }

  return false;
}

bool try_rotate(){
  static constexpr int8_t kicks[NUM_KICKS][2] = {{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
  static constexpr int8_t kicks_I[NUM_KICKS_I][2] = {{-2, 0}, {2, 0}, {0, -2}};

  int old_piece_x = piece_x, old_piece_y = piece_y;
  int old_rotation = piece_rotation;

  piece_rotation = (piece_rotation + 1) % NUM_ROTATION;
  update_piece();
  if(_check_rotate(old_piece_x, old_piece_y, kicks, NUM_KICKS)){
    return true;
  }

  if(piece_id == PIECE_I){
    if(_check_rotate(old_piece_x, old_piece_y, kicks_I, NUM_KICKS_I)){
      return true;
    }
  }

  piece_x = old_piece_x;
  piece_y = old_piece_y;
  piece_rotation = old_rotation;
  update_piece();
  return false;
}

bool try_soft_drop(){
  static unsigned long restore_fall_delay = fall_delay;
  static bool is_soft_drop = false;

  if(button_down.justPressed()){
    restore_fall_delay = fall_delay;
    fall_delay = fall_delay / SOFT_DROP_FACTOR;
    is_soft_drop = true;
  }
  else if(button_down.justReleased()){
    fall_delay = restore_fall_delay;
    is_soft_drop = false;
  }
  return is_soft_drop;
}

void react_to_player(){

  if(moveTimer.hasPassed(MOVE_DELAY)){
    update_buttons();
    remove_piece_from_grid();
    if(is_left_pressed() && check_left_border(1) && has_no_collision(-1, 0)){
      piece_x--;
      set_piece_moved();
    }
    if(is_right_pressed() && check_right_border(1) && has_no_collision(1, 0)){
      piece_x++;
      set_piece_moved();
    }
    if(is_up_just_pressed()){
      try_rotate();
      set_piece_moved();
    }
    try_soft_drop();
    add_piece_to_grid();

    if(has_piece_moved()){
      show_grid();
      moveTimer.restart();
    }
  }
}

bool spawn_piece(){
  piece_id = get_next_piece();
  piece_x = INITIAL_PIECE_X;
  piece_y = INITIAL_PIECE_Y;
  piece_rotation = INITIAL_PIECE_ROTATION;
  update_piece();
  if(!has_no_collision(0, 0)){
    return false;
  }
  add_piece_to_grid();
  show_grid();

  reset_lock_delay();
  reset_score_check();
  start_fall_delay();
  return true;
}

void game_over_loop_leds(){
  for(int i=LED_COUNT - 1; i>=0 ;i--){
    strip.setPixelColor(i, strip.Color(0,150,0));
    strip.show();
    delay(10);
  }
}

void game_over(){
  game_over_loop_leds();
  delay(100);
  do{
    delay(50);
  }while(!is_start_pressed());
  clear_grid();
  setup();
}

void pause_game(){
  if(is_pause_pressed()){
    delay(300);
    do{
      delay(50);
    }while(!is_pause_pressed());
  }
  delay(100);
}

bool can_level_up(){
  return count_row > 0 && (count_row % 10 == 0);
}

int get_score(int rows){
  switch(rows){
    case 1: return 10;  // Single
    case 2: return 30;  // Double
    case 3: return 50;  // Triple
    case 4: return 80;  // Tetris
    default: return 0;
  }
}

void update_score(){

  int rows = clear_rows();
  count_row += rows;
  score += get_score(rows);

  int score_1 = score - (  ( score/10 ) * 10  );
  int score_2 = ((score - (  ( score/100 ) * 100  )) - score_1)/10;
  int score_3 = ((score - (  ( score/1000 ) * 1000  )) - score_1 - score_2)/100;
  int score_4 = (score - score_1 - score_2 - score_3) / 1000;

  shift(0x08, score_4);
  shift(0x07, score_3);
  shift(0x06, score_2);
  shift(0x05, score_1);

  if(can_level_up()){
    fall_delay -= 100;
  }

}


void update_game_state(){
  remove_piece_from_grid();
  if(can_fall()){
    if(check_botton_border(1) && has_no_collision(0, 1)){
      piece_y++;
      start_fall_delay();
    }
    else{
      start_lock_delay();
    }
    add_piece_to_grid();
    show_grid();
  }
  else if(is_lock_delay_active()){
    if(check_botton_border(1) && has_no_collision(0, 1)){
      start_fall_delay();
      reset_lock_delay();
    }
    else if(is_lock_delay_elapsed()){
      set_score_check();
    }
  }

  add_piece_to_grid();
  if(can_score_check()){
    update_top_row();
    update_score();
    if(!spawn_piece()){
      game_over();
    }
  }
}

void setup(){

  strip.begin();
  strip.show();
  configButton();

  // configura o barramento do MAX7219
  pinMode(MAX7219_Data_IN, OUTPUT);
  pinMode(MAX7219_Clock,   OUTPUT);
  pinMode(MAX7219_Chip_Select, OUTPUT);
  for(uint8_t i = 1; i <= 8; i++){
    shift(i, 0x00); // envia 0 para o dígito i, apagando ele
  }

  randomSeed(analogRead(joystick_y)+analogRead(2)+analogRead(3));
  init_bag();
  spawn_piece();
  count_row = 0;
  level = 0;
  score = 0;
  fall_delay = INITIAL_FALL_DELAY;
}

void loop(){
  react_to_player();
  update_game_state();
  pause_game();
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
  for(int i=0; i < 16; i++)
    piece[i] = 0;
}
#endif
