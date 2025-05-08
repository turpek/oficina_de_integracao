#include "Unity/unity.h"
#include "tetris/tetris.h"
#include "test/test_utils.h"
#include "tetris/Mock_Arduino.h"
#include <iostream>
using namespace std;

#define GRID_W 8
#define GRID_H 16
#define LED_COUNT (GRID_W * GRID_H)

void setUp(void){
  clear_grid();
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 0;
  clear_piece();
};

void tearDown(void){
  pin_values[button_right] = HIGH;
  pin_values[button_left] = HIGH;
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

  for (int i = 0; i < LED_COUNT; ++i) {
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
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

/***************** TESTE DA FUNÇÃO `add_piece_to_grid` *********************/

void test_add_piece_to_grid_Piece_S_rx1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx2(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 2;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx2, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx3(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 3;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx3, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX1Y0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX1Y0, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX0Y1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX0Y1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX1Y1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX1Y1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx0_movX_1Y0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = 0;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX_1Y0, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX0Y_1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = -1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX0Y_1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX_1Y_1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = -1;
  update_piece();
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX_1_Y_1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX5Y14(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 5;
  piece_y = 14;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX5Y14, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX6Y14(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 6;
  piece_y = 14;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX6Y14, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX5Y15(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 5;
  piece_y = 15;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX5Y15, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx0_movX6Y15(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 6;
  piece_y = 15;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0_movX6Y15, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

/***************** TESTE DA FUNÇÃO `add_piece_to_grid` *********************/

void test_remove_piece_from_grid_Piece_S_rx0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);

}

void test_remove_piece_from_grid_Piece_S_rx1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx1, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);

}
void test_remove_piece_from_grid_Piece_S_rx2(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 2;
  update_piece();
  transform_grid(grid, map_piece_S_rx2, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);

}

void test_remove_piece_from_grid_Piece_S_rx3(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_piece_S_rx3, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX1Y0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX1Y0, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX0Y1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX0Y1, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX1Y1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  piece_y = 1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX1Y1, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}


void test_remove_piece_from_grid_Piece_S_rx0_movX_1Y0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = -1;
  piece_y = 0;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX_1Y0, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_remove_piece_from_grid_Piece_S_rx0_movX0Y_1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 0;
  piece_y = -1;
  update_piece();
  transform_grid(grid, map_piece_S_rx0_movX0Y_1, piece_colors[piece_id], LED_COUNT);
  remove_piece_from_grid();
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
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

void test_check_left_border_Piece_S_rx0_mov_X0(){
  piece_id = 0;
  piece_rotation = 0;
  int expect_left_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border());
}

void test_check_left_border_Piece_S_rx0_mov_X1(){
  piece_id = 0;
  piece_rotation = 0;
  piece_x = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border());
}

void test_check_left_border_Piece_S_rx1_mov_X0(){
  piece_id = 0;
  piece_rotation = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border());
}

void test_check_left_border_Piece_S_rx1_mov_X1(){
  piece_id = 0;
  piece_rotation = 1;
  piece_x = 1;
  int expect_left_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border());
}

void test_check_left_border_Piece_S_rx1_mov_X_1(){
  piece_id = 0;
  piece_rotation = 1;
  piece_x = -1;
  int expect_left_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_left_border, check_left_border());
}

void test_check_right_border_Piece_S_rx0_mov_X3(){
  piece_id = 0;
  piece_x = 3;
  piece_rotation = 0;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_right_border_Piece_S_rx0_mov_X4(){
  piece_id = 0;
  piece_x = 4;
  piece_rotation = 0;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_right_border_Piece_S_rx0_mov_X5(){
  piece_id = 0;
  piece_x = 5;
  piece_rotation = 0;
  int expect_right_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_right_border_Piece_S_rx3_mov_X3(){
  piece_id = 0;
  piece_x = 3;
  piece_rotation = 3;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_right_border_Piece_S_rx3_mov_X5(){
  piece_id = 0;
  piece_x = 5;
  piece_rotation = 3;
  int expect_right_border = 1;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_right_border_Piece_S_rx3_mov_X6(){
  piece_id = 0;
  piece_x = 6;
  piece_rotation = 3;
  int expect_right_border = 0;
  update_piece();
  TEST_ASSERT_EQUAL_INT(expect_right_border, check_right_border());
}

void test_check_botton_border_Piece_S_rx0_mov_Y12(){
  piece_id = 0;
  piece_y = 12;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border());
}

void test_check_botton_border_Piece_S_rx0_mov_Y13(){
  piece_id = 0;
  piece_y = 13;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border());
}

void test_check_botton_border_Piece_S_rx0_mov_Y14(){
  piece_id = 0;
  piece_y = 14;
  update_piece();
  int expect_botton_border = 0;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border());
}

void test_check_botton_border_Piece_I_rx1_mov_Y11(){
  piece_id = 6;
  piece_y = 11;
  piece_rotation = 1;
  update_piece();
  int expect_botton_border = 1;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border());
}

void test_check_botton_border_Piece_I_rx1_mov_Y12(){
  piece_id = 6;
  piece_y = 12;
  piece_rotation = 1;
  update_piece();
  int expect_botton_border = 0;
  TEST_ASSERT_EQUAL_INT(expect_botton_border, check_botton_border());
}

void test_has_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX3Y13(){
  piece_y = 14;
  piece_id = 5;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();

  piece_x = 3;
  piece_y = 14;
  piece_id = 1;
  update_piece();

  int expect_collision = 0;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_collision(-1, 0));
}

void test_has_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX2Y13(){
  piece_y = 14;
  piece_id = 5;
  piece_rotation = 0;
  update_piece();
  add_piece_to_grid();

  piece_x = 2;
  piece_y = 14;
  piece_id = 1;
  update_piece();

  int expect_collision = 1;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_collision(-1, 0));
}

void test_has_collision_right_Piece_J_rx0_X3Y12_Piece_L_rx0_movX5Y13(){
  piece_x = 5;
  piece_y = 13;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 3;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 0;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_collision(1, 0));
}

void test_has_collision_right_Piece_J_rx0_X4Y12_Piece_L_rx0_movX5Y13(){
  piece_x = 5;
  piece_y = 13;
  piece_id = 2;
  update_piece();
  add_piece_to_grid();

  piece_x = 4;
  piece_y = 12;
  piece_id = 3;
  update_piece();
  int expect_collision = 1;
  TEST_ASSERT_EQUAL_INT(expect_collision, has_collision(1, 0));
}



void test_can_rotate_free(){
  piece_x = 2;
  piece_y = 2;
  piece_id = 2;
  piece_rotation = 0;
  update_piece();

  can_rotate();
  int expect_rotate =1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, 1);
}

void test_can_rotate_shift_left_1x(){
  piece_x = 5;
  piece_y = 9;
  piece_id = 2;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_shift_1x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_right_1x(){
  piece_x = 0;
  piece_y = 9;
  piece_id = 2;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_shift_1x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_up_1x(){
  piece_x = 4;
  piece_y = 10;
  piece_id = 2;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_shift_1x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_down_1x(){
  piece_x = 2;
  piece_y = 12;
  piece_id = 2;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_shift_1x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_left_2x(){
  piece_x = 5;
  piece_y = 7;
  piece_id = 6;
  piece_rotation = 3;
  update_piece();
  transform_grid(grid, map_rotation_shift_2x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  can_rotate();
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_right_2x(){
  piece_x = -1;
  piece_y = 9;
  piece_id = 6;
  piece_rotation = 1;
  update_piece();
  transform_grid(grid, map_rotation_shift_2x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
  //add_piece_to_grid();
  //show_grid(grid);
}

void test_can_rotate_shift_up_2x(){
  piece_x = 0;
  piece_y = 3;
  piece_id = 6;
  piece_rotation = 0;
  update_piece();
  transform_grid(grid, map_rotation_shift_2x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
}

void test_can_rotate_shift_down_2x(){
  piece_x = 0;
  piece_y = 4;
  piece_id = 6;
  piece_rotation = 2;
  update_piece();
  transform_grid(grid, map_rotation_shift_2x, piece_colors[piece_id], LED_COUNT);
  int expect_rotate = 1;
  TEST_ASSERT_EQUAL_INT(expect_rotate, can_rotate());
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

  RUN_TEST(test_has_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX3Y13);
  RUN_TEST(test_has_collision_left_Piece_T_rx0_X0Y13_Piece_Z_rx0_movX2Y13);
  RUN_TEST(test_has_collision_right_Piece_J_rx0_X3Y12_Piece_L_rx0_movX5Y13);
  RUN_TEST(test_has_collision_right_Piece_J_rx0_X4Y12_Piece_L_rx0_movX5Y13);
  
  RUN_TEST(test_can_rotate_free);  
  RUN_TEST(test_can_rotate_shift_left_1x);  
  RUN_TEST(test_can_rotate_shift_right_1x);  
  RUN_TEST(test_can_rotate_shift_up_1x);  
  RUN_TEST(test_can_rotate_shift_down_1x);  
  RUN_TEST(test_can_rotate_shift_left_2x);  
  RUN_TEST(test_can_rotate_shift_right_2x);  
  RUN_TEST(test_can_rotate_shift_up_2x);  
  RUN_TEST(test_can_rotate_shift_down_2x);  

  return UNITY_END();

}
