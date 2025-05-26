#include "Unity/unity.h"
#include "tetris/tetris.h"
#include "test/test_utils.h"
#include "tetris/Mock_Arduino.h"
#include <iostream>
using namespace std;


void setUp(void){
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 0;
  clear_piece();
  pin_values[button_right] = HIGH;
  pin_values[button_left] = HIGH;
  pin_values[button_down] = HIGH;
  pin_values[button_up] = HIGH;
  mock_analog_x = JOYSTICK_CENTER;
  mock_analog_y = JOYSTICK_CENTER;
  current_time = 500;
  last_fall_delay = 0;
  last_lock_delay = 0;
  reset_lock_delay();
  reset_piece_moved();
  clear_grid();
};

void tearDown(void){
  clear_grid();
  clear_piece();
};

void show_piece(uint8_t *piece){

  for (int i = 0; i < 16; ++i) {
    cout << static_cast<int>(piece[i]);  // Tabulação para organizar melhor
    if((i + 1) % 4 == 0) {
      cout << endl;  // Quebra a linha a cada 4 elementos
    }
  }

}

void show_grid(uint32_t *grid){

  for (int i = 0; i < GRID_COUNT; ++i) {
    int val = grid[i];
    if(val != 0)
      val = 1;
    cout << val;  // Tabulação para organizar melhor
    if((i + 1) % 8 == 0) {
      cout << endl;  // Quebra a linha a cada 8 elementos
    }
  }

}

void test_decodePiece_I_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_I[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_I_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0
  };

  decodePiece(piece, piece_I[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_I_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_I[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_I_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0
  };
  decodePiece(piece, piece_I[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_L_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };

  decodePiece(piece, piece_L[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_L_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
  };

  decodePiece(piece, piece_L[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_L_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0
  };

  decodePiece(piece, piece_L[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_L_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };

  decodePiece(piece, piece_L[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_J_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_J[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);

}


void test_decodePiece_J_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_J[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);

}


void test_decodePiece_J_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_J[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_J_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_J[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_T_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_T[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_T_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_T[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_T_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_T[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}



void test_decodePiece_T_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_T[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_S_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_S[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_S_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_S[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_S_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_S[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);

}
void test_decodePiece_S_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_S[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_Z_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_Z[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_Z_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_Z[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_Z_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_Z[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_Z_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_Z[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_O_rx0(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_O[0]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}


void test_decodePiece_O_rx1(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_O[1]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_O_rx2(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_O[2]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}

void test_decodePiece_O_rx3(){
  uint8_t piece[16] = {0};
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  decodePiece(piece, piece_O[3]);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, piece, 16);
}



/***************** TESTES DA FUNÇÃO `update_piece` *************************/

void test_update_piece_S_rx0(){
  uint8_t expect_piece[16] = {
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  };
  piece_id = 0;
  piece_rotation = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, get_test_piece(), 16);
}

void test_update_piece_S_rx1(){
  uint8_t expect_piece[16] = {
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0
  };
  piece_id = 0;
  piece_rotation = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, get_test_piece(), 16);
}

void test_update_piece_L_rx3(){
  uint8_t expect_piece[16] = {
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
  };
  piece_id = 2;
  piece_rotation = 3;
  update_piece();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_piece, get_test_piece(), 16);
}

void test_add_piece_to_grid_Piece_S_rx0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

/***************** TESTE DA FUNÇÃO `add_piece_to_grid` *********************/

void test_add_piece_to_grid_Piece_S_rx1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx1, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx2(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 2;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx2, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx3(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 3;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx3, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX1Y0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX1Y0, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX0Y1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX0Y1, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX1Y1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX1Y1, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx0_movX_1Y0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX_1Y0, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX0Y_1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = -1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX0Y_1, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX_1Y_1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = -1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX_1_Y_1, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX5Y14(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 5;
  piece_y = 14;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX5Y14, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX6Y14(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 6;
  piece_y = 14;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX6Y14, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX5Y15(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 5;
  piece_y = 15;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX5Y15, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX6Y15(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 6;
  piece_y = 15;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX6Y15, piece_colors[piece_id], GRID_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

/***************** TESTE DA FUNÇÃO `add_piece_to_grid` *********************/

void test_remove_piece_from_grid_Piece_S_rx0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);

}

void test_remove_piece_from_grid_Piece_S_rx1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx1, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);

}
void test_remove_piece_from_grid_Piece_S_rx2(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 2;
  update_piece();
  transform_grid(grid, map_piece_S_rx2, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);

}

void test_remove_piece_from_grid_Piece_S_rx3(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_piece_S_rx3, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX1Y0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX1Y0, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX0Y1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX0Y1, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX1Y1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX1Y1, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}


void test_remove_piece_from_grid_Piece_S_rx0_movX_1Y0(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX_1Y0, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX0Y_1(){
  uint32_t expect_grid[GRID_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = -1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX0Y_1, piece_colors[piece_id], GRID_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, GRID_COUNT);
}

void test_is_right_pressed_right_button_not_pressed(){
  pin_values[button_right] = HIGH;
  int expect_right_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_right_pressed, is_right_pressed(0));
}

void test_is_right_pressed_right_button_pressed(){
  pin_values[button_right] = LOW;
  int expect_right_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_right_pressed, is_right_pressed(0));
}

void test_is_right_pressed_by_joystick_DX_0(){
  int expect_right_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_right_pressed, is_right_pressed(0));
}

void test_is_right_pressed_by_joystick_DX_30(){
  int expect_right_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_right_pressed, is_right_pressed(-30));
}

void test_is_right_pressed_by_joystick_DX_31(){
  int expect_right_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_right_pressed, is_right_pressed(-31));
}

void test_is_left_pressed_left_button_not_pressed(){
  pin_values[button_left] = HIGH;
  int expect_left_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_left_pressed, is_left_pressed(0));
}

void test_is_left_pressed_left_button_pressed(){
  pin_values[button_left] = LOW;
  int expect_left_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_pressed, is_left_pressed(0));
}

void test_is_left_pressed_by_joystick_DX_0(){
  int expect_left_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_left_pressed, is_left_pressed(0));
}

void test_is_left_pressed_by_joystick_DX_30(){
  int expect_left_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_left_pressed, is_left_pressed(30));
}

void test_is_left_pressed_by_joystick_DX_31(){
  int expect_left_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_pressed, is_left_pressed(31));
}


void test_is_down_pressed_down_button_not_pressed(){
  pin_values[button_down] = HIGH;
  int expect_down_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_down_pressed, is_down_pressed(0));
}


void test_is_down_pressed_down_button_pressed(){
  pin_values[button_down] = LOW;
  int expect_down_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_down_pressed, is_down_pressed(0));
}

void test_is_down_pressed_by_joystick_DY_0(){
  int expect_down_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_down_pressed, is_down_pressed(0));

}

void test_is_down_pressed_by_joystick_DY_30(){
  int expect_down_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_down_pressed, is_down_pressed(-30));
}

void test_is_down_pressed_by_joystick_DY_31(){
  int expect_down_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_down_pressed, is_down_pressed(-31));
}


void test_is_up_pressed_up_button_not_pressed(){
  pin_values[button_up] = HIGH;
  int expect_up_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_up_pressed, is_up_pressed(0));
}

void test_is_up_pressed_up_button_pressed(){
  pin_values[button_up] = LOW;
  int expect_up_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_up_pressed, is_up_pressed(0));
}

void test_is_up_pressed_by_joystick_DY0(){
  int expect_up_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_up_pressed, is_up_pressed(0));
}

void test_is_up_pressed_by_joystick_DY30(){
  int expect_up_pressed = 0;
  TEST_ASSERT_EQUAL_INT(expect_up_pressed, is_up_pressed(30));
}

void test_is_up_pressed_by_joystick_DY31(){
  int expect_up_pressed = 1;
  TEST_ASSERT_EQUAL_INT(expect_up_pressed, is_up_pressed(31));
}

void test_check_left_border_Piece_S_rx0_mov_X0(){
  piece_id = 0;
  piece_rotation = 0;
  int expect_left_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border(1));
}

void test_check_left_border_Piece_S_rx0_mov_X1(){
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border(1));
}

void test_check_left_border_Piece_S_rx1_mov_X0(){
  piece_id = 0;
  piece_rotation = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border(1));
}

void test_check_left_border_Piece_S_rx1_mov_X1(){
  piece_id = 0;
  piece_rotation = 1;
  piece_x = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border(1));
}

void test_check_left_border_Piece_S_rx1_mov_X_1(){
  piece_id = 0;
  piece_rotation = 1;
  piece_x = -1;
  int expect_left_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border(1));
}

void test_check_right_border_Piece_S_rx0_mov_X3(){
  piece_id = 0;
  piece_x = 3;
  piece_rotation = 0;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_right_border_Piece_S_rx0_mov_X4(){
  piece_id = 0;
  piece_x = 4;
  piece_rotation = 0;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_right_border_Piece_S_rx0_mov_X5(){
  piece_id = 0;
  piece_x = 5;
  piece_rotation = 0;
  int expect_right_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_right_border_Piece_S_rx3_mov_X3(){
  piece_id = 0;
  piece_x = 3;
  piece_rotation = 3;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_right_border_Piece_S_rx3_mov_X5(){
  piece_id = 0;
  piece_x = 5;
  piece_rotation = 3;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_right_border_Piece_S_rx3_mov_X6(){
  piece_id = 0;
  piece_x = 6;
  piece_rotation = 3;
  int expect_right_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border(1));
}

void test_check_botton_border_Piece_S_rx0_mov_Y12(){
  piece_id = 0;
  piece_y = 16;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border(1));
}

void test_check_botton_border_Piece_S_rx0_mov_Y13(){
  piece_id = 0;
  piece_y = 17;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border(1));
}

void test_check_botton_border_Piece_S_rx0_mov_Y14(){
  piece_id = 0;
  piece_y = 18;
  update_piece();
  int expect_botton_border = 0;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border(1));
}

void test_check_botton_border_Piece_I_rx1_mov_Y11(){
  piece_id = 6;
  piece_y = 15;
  piece_rotation = 1;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border(1));
}

void test_check_botton_border_Piece_I_rx1_mov_Y12(){
  piece_id = 6;
  piece_y = 16;
  piece_rotation = 1;
  update_piece();
  int expect_botton_border = 0;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border(1));
}

void test_has_no_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX3Y13(){
  piece_y = 14;
  piece_id = 5;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();

  piece_x = 3;
  piece_y = 14;
  piece_id = 1;
  update_piece();

  int expect_collision = 1;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(-1, 0));
}

void test_has_no_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX2Y13(){
  piece_y = 14;
  piece_id = 5;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();

  piece_x = 2;
  piece_y = 14;
  piece_id = 1;
  update_piece();

  int expect_collision = 0;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(-1, 0));
}

void test_has_no_collision_right_Piece_J_rx0_X3Y12_Piece_L_rx0_movX5Y13(){
  piece_x = 5;
  piece_y = 13;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 3;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 1;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(1, 0));
}

void test_has_no_collision_right_Piece_J_rx0_X4Y12_Piece_L_rx0_movX5Y13(){
  piece_x = 5;
  piece_y = 13;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 4;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 0;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(1, 0));
}

void test_has_no_collision_fall_Piece_J_rx0_X1Y14_Piece_L_rx0_movX1Y12(){
  piece_x = 1;
  piece_y = 14;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 1;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 0;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(0, 1));
}

void test_has_no_collision_fall_Piece_J_rx0_X1Y14_Piece_L_rx0_movX0Y12(){
  piece_x = 1;
  piece_y = 14;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 0;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 1;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_no_collision(0, 1));
}


void test_try_rotate_L_test_1(){
  piece_x = 2;
  piece_y = 6;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();

  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_L_test_2(){
  piece_x = 1;
  piece_y = 17;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_L, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_L_test_3(){
  piece_x = 1;
  piece_y = 15;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_L, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_L_test_4(){
  piece_x = 4;
  piece_y = 17;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_L, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_L_test_5(){
  piece_x = 3;
  piece_y = 8;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_L, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_L_test_floor(){
  piece_x = 3;
  piece_y = 18;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_L, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_I_rx3_test_right_wall(){
  piece_x = 6;
  piece_y = 14;
  piece_id = 6;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_I, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_I_rx1_test_left_wall(){
  piece_x = -2;
  piece_y = 14;
  piece_id = 6;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_I, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_I_rx0_test_floor(){
  piece_x = 2;
  piece_y = 18;
  piece_id = 6;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_I, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}

void test_try_rotate_I_rx2_test_floor(){
  piece_x = 2;
  piece_y = 18;
  piece_id = 6;
  piece_rotation = 2;
  update_piece();
  transform_grid(grid, map_rotation_I, piece_colors[piece_id], GRID_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, try_rotate());
}


void test_is_fall_delay_elapsed_false_interval_less_than_fall_delay(){
  current_time = 999;
  TEST_ASSERT_FALSE(is_fall_delay_elapsed());
}

void test_is_fall_delay_elapsed_true_interval_equal_than_fall_delay(){
  current_time = 1000;
  TEST_ASSERT_TRUE(is_fall_delay_elapsed());
}

void test_is_fall_delay_elapsed_true_interval_greater_than_fall_delay(){
  current_time = 1001;
  TEST_ASSERT_TRUE(is_fall_delay_elapsed());
}


void test_is_fall_delay_elapsed_false_with_start_fall_timer(){
  current_time = 1279;
  start_fall_delay();
  current_time = 2143;
  TEST_ASSERT_FALSE(is_fall_delay_elapsed());
}

void test_is_fall_delay_elapsed_true_with_start_fall_timer(){
  current_time = 1279;
  start_fall_delay();
  current_time = 2343;
  TEST_ASSERT_TRUE(is_fall_delay_elapsed());
}

void test_has_piece_moved_default(){
  TEST_ASSERT_FALSE(has_piece_moved());
}

void test_has_piece_moved_set_true(){
  set_piece_moved();
  TEST_ASSERT_TRUE(has_piece_moved());
}

void test_has_piece_moved_set_false(){
  set_piece_moved();
  reset_piece_moved();
  TEST_ASSERT_FALSE(has_piece_moved());
}

void test_react_to_player_without_movements(){
  int expect_piece_x = 2;
  int expect_piece_y = 6;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 6;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_left_true(){
  int expect_piece_x = 1;
  int expect_piece_y = 6;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 6;

  update_piece();
  add_piece_to_grid();
  pin_values[button_left] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_left_true(){
  int expect_piece_x = 1;
  int expect_piece_y = 6;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 6;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  mock_analog_x = JOYSTICK_LEFT;
  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_left_collision(){
  int expect_piece_x = 1;
  int expect_piece_y = 13;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 13;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  pin_values[button_left] = LOW;
  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 9");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_left_collision(){
  int expect_piece_x = 1;
  int expect_piece_y = 13;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 13;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  mock_analog_x = JOYSTICK_LEFT;
  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 9");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_left_border(){
  int expect_piece_x = 0;
  int expect_piece_y = 4;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 4;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  pin_values[button_left] = LOW;
  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_left_border(){
  int expect_piece_x = 0;
  int expect_piece_y = 4;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 4;

  update_piece();
  add_piece_to_grid();
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  mock_analog_x = JOYSTICK_LEFT;
  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_right_true(){
  int expect_piece_x = 3;
  int expect_piece_y = 6;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 6;

  update_piece();
  add_piece_to_grid();
  pin_values[button_right] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 3");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}
void test_react_to_player_joystick_right_true(){
  int expect_piece_x = 3;
  int expect_piece_y = 6;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 6;

  update_piece();
  add_piece_to_grid();
  mock_analog_x = JOYSTICK_RIGHT;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 3");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_right_collision(){
  int expect_piece_x = 2;
  int expect_piece_y = 17;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 17;

  update_piece();
  add_piece_to_grid();
  pin_values[button_right] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 13");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_right_collision(){
  int expect_piece_x = 2;
  int expect_piece_y = 17;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 2;
  piece_y = 17;

  update_piece();
  add_piece_to_grid();
  mock_analog_x = JOYSTICK_RIGHT;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 2");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 13");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_right_border(){
  int expect_piece_x = 7;
  int expect_piece_y = 4;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 7;
  piece_y = 4;

  update_piece();
  add_piece_to_grid();
  pin_values[button_right] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 7");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_right_border(){
  int expect_piece_x = 7;
  int expect_piece_y = 4;
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 7;
  piece_y = 4;

  update_piece();
  add_piece_to_grid();
  mock_analog_x = JOYSTICK_RIGHT;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_x, piece_x, "expect_piece_x = 7");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_piece_y, piece_y, "expect_piece_y = 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_botton_up_true(){
  int expect_rotation = 1;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 4;
  piece_y = 8;

  update_piece();
  add_piece_to_grid();
  pin_values[button_up] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 1");
}

void test_react_to_player_joystick_up_true(){
  int expect_rotation = 1;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 4;
  piece_y = 8;

  update_piece();
  add_piece_to_grid();
  mock_analog_y = JOYSTICK_UP;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 1");
}

void test_react_to_player_botton_up_false(){
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 18;

  update_piece();
  add_piece_to_grid();
  pin_values[button_up] = LOW;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}

void test_react_to_player_joystick_up_false(){
  int expect_rotation = 0;

  piece_id = 6;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 18;

  update_piece();
  add_piece_to_grid();
  mock_analog_y = JOYSTICK_UP;
  transform_grid(grid, map_react, piece_colors[piece_id], GRID_COUNT);

  react_to_player();
  TEST_ASSERT_EQUAL_INT_MESSAGE(expect_rotation, piece_rotation, "expect_rotation = 0");
}


void test_is_lock_delay_active_default(){
  TEST_ASSERT_FALSE(is_lock_delay_active());
}

void test_is_lock_delay_active_false(){
  reset_lock_delay();
  TEST_ASSERT_FALSE(is_lock_delay_active());
}

void test_is_lock_delay_active_true(){
  start_lock_delay();
  TEST_ASSERT_TRUE(is_lock_delay_active());
}

void test_is_lock_delay_active_manually_disabled(){
  start_lock_delay();
  reset_lock_delay();
  TEST_ASSERT_FALSE(is_lock_delay_active());

}

void test_is_lock_delay_elapsed_false_with_lock_delay_disabled(){
  current_time = 200;
  start_lock_delay();
  reset_lock_delay();
  current_time = current_time + INITIAL_LOCK_DELAY + 1;
  TEST_ASSERT_FALSE(is_lock_delay_elapsed());
}

void test_is_lock_delay_elapsed_false_time_delta_less_than_lock_delay(){
  current_time = 200;
  start_lock_delay();
  current_time = current_time + 20;
  TEST_ASSERT_FALSE(is_lock_delay_elapsed());
}

void test_is_lock_delay_elapsed_false_time_delta_INITIAL_LOCK_DELAY(){
  current_time = 200;
  start_lock_delay();
  current_time = current_time + INITIAL_LOCK_DELAY;
  TEST_ASSERT_FALSE(is_lock_delay_elapsed());
}

void test_is_lock_delay_elapsed_true(){
  current_time = 200;
  start_lock_delay();
  current_time = current_time + INITIAL_LOCK_DELAY + 1;
  TEST_ASSERT_TRUE(is_lock_delay_elapsed());
}

void test_can_score_check_false_with_reset_score_check(){
  reset_score_check();
  TEST_ASSERT_FALSE(can_score_check());
}

void test_can_score_check_true_with_set_score_check(){
  set_score_check();
  TEST_ASSERT_TRUE(can_score_check());
}

void test_can_score_check_false_with_set_and_reset(){
  set_score_check();
  reset_score_check();
  TEST_ASSERT_FALSE(can_score_check());
}


void test_can_fall_false_with_lock_delay_disabled(){
  reset_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + 10;
  TEST_ASSERT_FALSE(can_fall());
}

void test_can_fall_false_with_lock_delay_active_with_fall_delay_false(){
  start_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + 10;
  TEST_ASSERT_FALSE(can_fall());
}

void test_can_fall_false_with_lock_delay_active_with_fall_delay_true(){
  start_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY;
  TEST_ASSERT_FALSE(can_fall());
}

void test_can_fall_true(){
  reset_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY;
  TEST_ASSERT_TRUE(can_fall());
}

void test_update_game_state_can_fall_false_with_lock_delay_and_fall_delay_false(){
  int expect_piece_y = 7;
  piece_id = 5;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 7;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);
  add_piece_to_grid();

  reset_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY - 1;

  update_game_state();
  TEST_ASSERT_EQUAL_INT(expect_piece_y, piece_y);
}

void test_update_game_state_can_fall_false_with_lock_delay_true_and_fall_delay_true(){
  int expect_piece_y = 7;
  piece_id = 5;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 7;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);
  add_piece_to_grid();

  start_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY;

  update_game_state();
  TEST_ASSERT_EQUAL_INT(expect_piece_y, piece_y);
}

void test_update_game_state_can_fall_false_with_lock_delay_true_and_fall_delay_false(){
  int expect_piece_y = 7;
  piece_id = 5;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 7;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);
  add_piece_to_grid();

  start_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY - 1;

  update_game_state();
  TEST_ASSERT_EQUAL_INT(expect_piece_y, piece_y);
}

void test_update_game_state_can_fall_true_with_lock_delay_false_and_fall_delay_true(){
  int expect_piece_y = 8;
  piece_id = 5;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 7;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);
  add_piece_to_grid();

  reset_lock_delay();
  current_time = 200;
  start_fall_delay();
  current_time = current_time + INITIAL_FALL_DELAY;

  update_game_state();
  TEST_ASSERT_EQUAL_INT(expect_piece_y, piece_y);
}

void test_update_game_state_is_lock_delay_active_true_has_collision(){
  piece_id = 5;
  piece_rotation = 2;
  piece_x = 3;
  piece_y = 13;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);

  reset_lock_delay();
  current_time = 200;
  current_time = current_time + INITIAL_FALL_DELAY;

  update_game_state();
  TEST_ASSERT_TRUE_MESSAGE(is_lock_delay_active(), "locking is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(can_fall(), "can_fall is FALSE");
}

void test_update_game_state_is_lock_delay_active_false_can_fall_false(){
  piece_id = 5;
  piece_rotation = 2;
  piece_x = 3;
  piece_y = 13;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);

  current_time = 200;
  reset_lock_delay();
  current_time = 300;

  remove_piece_from_grid();
  piece_x = piece_x + 1;
  update_game_state();

  current_time = 400;
  TEST_ASSERT_FALSE_MESSAGE(is_lock_delay_active(), "locking is FALSE");
  TEST_ASSERT_FALSE_MESSAGE(can_fall(), "can_fall is FALSE");
  TEST_ASSERT_FALSE_MESSAGE(can_score_check(), "can_score_check is FALSE");
}

void test_update_game_state_is_lock_delay_active_false_can_fall_true(){
  piece_id = 5;
  piece_rotation = 2;
  piece_x = 3;
  piece_y = 13;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);

  current_time = 200;
  reset_lock_delay();
  current_time = 300;

  remove_piece_from_grid();
  piece_x = piece_x + 1;
  update_game_state();

  current_time = current_time + INITIAL_FALL_DELAY;
  TEST_ASSERT_FALSE_MESSAGE(is_lock_delay_active(), "locking is FALSE");
  TEST_ASSERT_TRUE_MESSAGE(can_fall(), "can_fall is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(can_score_check(), "can_score_check is FALSE");
}

void test_update_game_state_is_lock_delay_active_with_lock_delay_elapsed_and_can_fall(){
  piece_id = 5;
  piece_rotation = 2;
  piece_x = 3;
  piece_y = 13;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);

  current_time = 200;
  reset_lock_delay();
  current_time = current_time + INITIAL_LOCK_DELAY + 1;

  remove_piece_from_grid();
  piece_x = piece_x + 1;
  update_game_state();

  current_time = current_time + INITIAL_FALL_DELAY;
  TEST_ASSERT_FALSE_MESSAGE(is_lock_delay_active(), "locking is FALSE");
  TEST_ASSERT_TRUE_MESSAGE(can_fall(), "can_fall is TRUE");
  TEST_ASSERT_FALSE_MESSAGE(can_score_check(), "can_score_check is FALSE");
}

void test_update_game_state_is_lock_delay_active_with_lock_delay_elapsed_and_no_can_fall(){
  int expect_piece_x = INITIAL_PIECE_X;
  int expect_piece_y = INITIAL_PIECE_Y;
  piece_id = 5;
  piece_rotation = 2;
  piece_x = 3;
  piece_y = 13;

  update_piece();
  transform_grid(grid, map_update_game, piece_colors[piece_id], GRID_COUNT);

  current_time = 200;
  start_lock_delay();
  current_time = current_time + INITIAL_LOCK_DELAY + 1;

  update_game_state();

  current_time = current_time + INITIAL_FALL_DELAY;
  TEST_ASSERT_TRUE_MESSAGE(is_lock_delay_active(), "locking is FALSE");
  TEST_ASSERT_FALSE_MESSAGE(can_fall(), "can_fall is FALSE");
  TEST_ASSERT_FALSE_MESSAGE(can_score_check(), "can_score_check is FALSE");
  TEST_ASSERT_EQUAL_INT(expect_piece_x, piece_x);
  TEST_ASSERT_EQUAL_INT(expect_piece_y, piece_y);
}

void test_clear_row_empty(){
  TEST_ASSERT_EQUAL_INT8_ARRAY(map_clear_all, grid, GRID_COUNT);
}

void test_clear_row_full(){
  piece_id = 6;
  piece_x = 0;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  piece_x = 4;
  add_piece_to_grid();
  clear_row(1);

  TEST_ASSERT_EQUAL_INT8_ARRAY(map_clear_all, grid, GRID_COUNT);
}

void test_clear_row_hole(){
  piece_id = 2;
  piece_x = 0;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  piece_x = 4;
  add_piece_to_grid();
  clear_row(0);
  clear_row(1);

  TEST_ASSERT_EQUAL_INT8_ARRAY(map_clear_all, grid, GRID_COUNT);
}

void test_push_rows_teste_1(){
  int y = GRID_H + PIECE_H - 1; 
  int dy = 1;
  int lines = 3;
  transform_grid(grid, map_push_rows_t1_frame_0, piece_colors[piece_id], GRID_COUNT);
  push_rows(y, dy, lines);
  TEST_ASSERT_EQUAL_INT8_ARRAY(map_push_rows_t1_frame_1, map_push_rows_t1_frame_0, GRID_COUNT);
}

void test_push_rows_teste_2(){
  int y = 16; 
  int dy = 2;
  int lines = 3;
  transform_grid(grid, map_push_rows_t2_frame_0, piece_colors[piece_id], GRID_COUNT);
  push_rows(y, dy, lines);
  TEST_ASSERT_EQUAL_INT8_ARRAY(map_push_rows_t2_frame_1, map_push_rows_t2_frame_0, GRID_COUNT);
}

void test_push_rows_teste_3(){
  int y = GRID_H + PIECE_H - 1; 
  int dy = 2;
  int lines = GRID_H;
  transform_grid(grid, map_push_rows_t2_frame_0, piece_colors[piece_id], GRID_COUNT);
  push_rows(y, dy, lines);
  TEST_ASSERT_EQUAL_INT8_ARRAY(map_push_rows_t2_frame_1, map_push_rows_t2_frame_0, GRID_COUNT);
}

int main(){
  UNITY_BEGIN();

  RUN_TEST(test_decodePiece_I_rx0);
  RUN_TEST(test_decodePiece_I_rx1);
  RUN_TEST(test_decodePiece_I_rx2);
  RUN_TEST(test_decodePiece_I_rx3);

  RUN_TEST(test_decodePiece_L_rx0);
  RUN_TEST(test_decodePiece_L_rx1);
  RUN_TEST(test_decodePiece_L_rx2);
  RUN_TEST(test_decodePiece_L_rx3);

  RUN_TEST(test_decodePiece_J_rx0);
  RUN_TEST(test_decodePiece_J_rx1);
  RUN_TEST(test_decodePiece_J_rx2);
  RUN_TEST(test_decodePiece_J_rx3);

  RUN_TEST(test_decodePiece_T_rx0);
  RUN_TEST(test_decodePiece_T_rx1);
  RUN_TEST(test_decodePiece_T_rx2);
  RUN_TEST(test_decodePiece_T_rx3);

  RUN_TEST(test_decodePiece_S_rx0);
  RUN_TEST(test_decodePiece_S_rx1);
  RUN_TEST(test_decodePiece_S_rx2);
  RUN_TEST(test_decodePiece_S_rx3);

  RUN_TEST(test_decodePiece_Z_rx0);
  RUN_TEST(test_decodePiece_Z_rx1);
  RUN_TEST(test_decodePiece_Z_rx2);
  RUN_TEST(test_decodePiece_Z_rx3);

  RUN_TEST(test_decodePiece_O_rx0);
  RUN_TEST(test_decodePiece_O_rx1);
  RUN_TEST(test_decodePiece_O_rx2);
  RUN_TEST(test_decodePiece_O_rx3);

  RUN_TEST(test_update_piece_S_rx0);
  RUN_TEST(test_update_piece_S_rx1);
  RUN_TEST(test_update_piece_L_rx3);

  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx1);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx2);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx3);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX1Y0);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX0Y1);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX1Y1);
  
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX_1Y0);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX0Y_1);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX_1Y_1);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX5Y14);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX6Y14);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX5Y15);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0_movX6Y15);

  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx1);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx2);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx3);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX1Y0);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX0Y1);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX1Y1);

  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX_1Y0);
  RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX0Y_1);
  //RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX_1Y_1);
  //RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX5Y14);
  //RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX6Y14);
  //RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX5Y15);
  //RUN_TEST(test_remove_piece_from_grid_Piece_S_rx0_movX6Y15);

  RUN_TEST(test_is_right_pressed_right_button_not_pressed);
  RUN_TEST(test_is_right_pressed_right_button_pressed);
  RUN_TEST(test_is_right_pressed_by_joystick_DX_0);
  RUN_TEST(test_is_right_pressed_by_joystick_DX_30);
  RUN_TEST(test_is_right_pressed_by_joystick_DX_31);

  RUN_TEST(test_is_left_pressed_left_button_not_pressed);
  RUN_TEST(test_is_left_pressed_left_button_pressed);
  RUN_TEST(test_is_left_pressed_by_joystick_DX_0);
  RUN_TEST(test_is_left_pressed_by_joystick_DX_30);
  RUN_TEST(test_is_left_pressed_by_joystick_DX_31);

  RUN_TEST(test_is_down_pressed_down_button_not_pressed);
  RUN_TEST(test_is_down_pressed_down_button_pressed);
  RUN_TEST(test_is_down_pressed_by_joystick_DY_0);
  RUN_TEST(test_is_down_pressed_by_joystick_DY_30);
  RUN_TEST(test_is_down_pressed_by_joystick_DY_31);

  RUN_TEST(test_is_up_pressed_up_button_not_pressed);
  RUN_TEST(test_is_up_pressed_up_button_pressed);
  RUN_TEST(test_is_up_pressed_by_joystick_DY0);
  RUN_TEST(test_is_up_pressed_by_joystick_DY30);
  RUN_TEST(test_is_up_pressed_by_joystick_DY31);

  RUN_TEST(test_check_left_border_Piece_S_rx0_mov_X0);
  RUN_TEST(test_check_left_border_Piece_S_rx0_mov_X1);
  RUN_TEST(test_check_left_border_Piece_S_rx1_mov_X0);
  RUN_TEST(test_check_left_border_Piece_S_rx1_mov_X1);
  RUN_TEST(test_check_left_border_Piece_S_rx1_mov_X_1);

  RUN_TEST(test_check_right_border_Piece_S_rx0_mov_X3);
  RUN_TEST(test_check_right_border_Piece_S_rx0_mov_X4);
  RUN_TEST(test_check_right_border_Piece_S_rx0_mov_X5);
  RUN_TEST(test_check_right_border_Piece_S_rx3_mov_X3);
  RUN_TEST(test_check_right_border_Piece_S_rx3_mov_X5);
  RUN_TEST(test_check_right_border_Piece_S_rx3_mov_X6);

  RUN_TEST(test_check_botton_border_Piece_S_rx0_mov_Y12);
  RUN_TEST(test_check_botton_border_Piece_S_rx0_mov_Y13);
  RUN_TEST(test_check_botton_border_Piece_S_rx0_mov_Y14);
  RUN_TEST(test_check_botton_border_Piece_I_rx1_mov_Y11);
  RUN_TEST(test_check_botton_border_Piece_I_rx1_mov_Y12);

  RUN_TEST(test_has_no_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX3Y13);
  RUN_TEST(test_has_no_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX2Y13);
  RUN_TEST(test_has_no_collision_right_Piece_J_rx0_X3Y12_Piece_L_rx0_movX5Y13);
  RUN_TEST(test_has_no_collision_right_Piece_J_rx0_X4Y12_Piece_L_rx0_movX5Y13);
  RUN_TEST(test_has_no_collision_fall_Piece_J_rx0_X1Y14_Piece_L_rx0_movX1Y12);
  RUN_TEST(test_has_no_collision_fall_Piece_J_rx0_X1Y14_Piece_L_rx0_movX0Y12);

  RUN_TEST(test_try_rotate_L_test_1);
  RUN_TEST(test_try_rotate_L_test_2);
  RUN_TEST(test_try_rotate_L_test_3);
  RUN_TEST(test_try_rotate_L_test_4);
  RUN_TEST(test_try_rotate_L_test_5);
  RUN_TEST(test_try_rotate_L_test_floor);

  RUN_TEST(test_try_rotate_I_rx3_test_right_wall);
  RUN_TEST(test_try_rotate_I_rx1_test_left_wall);
  RUN_TEST(test_try_rotate_I_rx0_test_floor);
  RUN_TEST(test_try_rotate_I_rx2_test_floor);

  RUN_TEST(test_is_fall_delay_elapsed_false_interval_less_than_fall_delay);
  RUN_TEST(test_is_fall_delay_elapsed_true_interval_equal_than_fall_delay);
  RUN_TEST(test_is_fall_delay_elapsed_true_interval_greater_than_fall_delay);
  RUN_TEST(test_is_fall_delay_elapsed_false_with_start_fall_timer);
  RUN_TEST(test_is_fall_delay_elapsed_true_with_start_fall_timer);

  RUN_TEST(test_has_piece_moved_default);
  RUN_TEST(test_has_piece_moved_set_true);
  RUN_TEST(test_has_piece_moved_set_false);

  RUN_TEST(test_react_to_player_without_movements);
  RUN_TEST(test_react_to_player_botton_left_true);
  RUN_TEST(test_react_to_player_joystick_left_true);
  RUN_TEST(test_react_to_player_botton_left_collision);
  RUN_TEST(test_react_to_player_joystick_left_collision);
  RUN_TEST(test_react_to_player_botton_left_border);
  RUN_TEST(test_react_to_player_joystick_left_border);
  RUN_TEST(test_react_to_player_botton_right_true);
  RUN_TEST(test_react_to_player_joystick_right_true);
  RUN_TEST(test_react_to_player_botton_right_collision);
  RUN_TEST(test_react_to_player_joystick_right_collision);
  RUN_TEST(test_react_to_player_botton_right_border);
  RUN_TEST(test_react_to_player_joystick_right_border);
  RUN_TEST(test_react_to_player_botton_up_true);
  RUN_TEST(test_react_to_player_joystick_up_true);
  RUN_TEST(test_react_to_player_botton_up_false);
  RUN_TEST(test_react_to_player_joystick_up_false);

  RUN_TEST(test_is_lock_delay_active_default);
  RUN_TEST(test_is_lock_delay_active_false);
  RUN_TEST(test_is_lock_delay_active_true);
  RUN_TEST(test_is_lock_delay_active_manually_disabled);

  RUN_TEST(test_is_lock_delay_elapsed_false_with_lock_delay_disabled);
  RUN_TEST(test_is_lock_delay_elapsed_false_time_delta_less_than_lock_delay);
  RUN_TEST(test_is_lock_delay_elapsed_false_time_delta_INITIAL_LOCK_DELAY);
  RUN_TEST(test_is_lock_delay_elapsed_true);

  RUN_TEST(test_can_score_check_false_with_reset_score_check);
  RUN_TEST(test_can_score_check_true_with_set_score_check);
  RUN_TEST(test_can_score_check_false_with_set_and_reset);

  RUN_TEST(test_can_fall_false_with_lock_delay_disabled);
  RUN_TEST(test_can_fall_false_with_lock_delay_active_with_fall_delay_false);
  RUN_TEST(test_can_fall_false_with_lock_delay_active_with_fall_delay_true);
  RUN_TEST(test_can_fall_true);

  RUN_TEST(test_update_game_state_can_fall_false_with_lock_delay_and_fall_delay_false);
  RUN_TEST(test_update_game_state_can_fall_false_with_lock_delay_true_and_fall_delay_true);
  RUN_TEST(test_update_game_state_can_fall_false_with_lock_delay_true_and_fall_delay_false);
  RUN_TEST(test_update_game_state_can_fall_true_with_lock_delay_false_and_fall_delay_true);
  RUN_TEST(test_update_game_state_is_lock_delay_active_true_has_collision);
  RUN_TEST(test_update_game_state_is_lock_delay_active_false_can_fall_false);
  RUN_TEST(test_update_game_state_is_lock_delay_active_false_can_fall_true);
  RUN_TEST(test_update_game_state_is_lock_delay_active_with_lock_delay_elapsed_and_can_fall);
 // RUN_TEST(test_update_game_state_is_lock_delay_active_with_lock_delay_elapsed_and_no_can_fall);

  RUN_TEST(test_clear_row_empty);
  RUN_TEST(test_clear_row_full);
  RUN_TEST(test_clear_row_hole);

  RUN_TEST(test_push_rows_teste_1);
  RUN_TEST(test_push_rows_teste_2);
  RUN_TEST(test_push_rows_teste_3);
  return UNITY_END();

}
