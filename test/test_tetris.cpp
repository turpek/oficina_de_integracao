#include "Unity/unity.h"
#include "tetris/tetris.h"
#include "test/test_utils.h"
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
};

void tearDown(void){};

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

void test_add_piece_to_grid_Piece_S_rx0(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 0;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx0, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx1(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 1;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx1, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}


void test_add_piece_to_grid_Piece_S_rx2(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 2;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx2, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
}

void test_add_piece_to_grid_Piece_S_rx3(){
  uint32_t expect_grid[LED_COUNT] = {0};
  piece_id = 0;
  piece_rotation = 3;
  add_piece_to_grid();
  transform_grid(expect_grid, map_piece_S_rx3, piece_colors[piece_id], LED_COUNT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(expect_grid, grid, LED_COUNT);
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


  RUN_TEST(test_add_piece_to_grid_Piece_S_rx0);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx1);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx2);
  RUN_TEST(test_add_piece_to_grid_Piece_S_rx3);
  return UNITY_END();

}
