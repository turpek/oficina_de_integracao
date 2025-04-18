#include "Unity/unity.h"
#include "tetris/tetris.h"
#include <iostream>
using namespace std;


void setUp(void){};

void tearDown(void){};

void show_piece(uint8_t *piece){

  for (int i = 0; i < 16; ++i) {
    cout << static_cast<int>(piece[i]);  // Tabulação para organizar melhor
    if((i + 1) % 4 == 0) {
      cout << endl;  // Quebra a linha a cada 4 elementos
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
  return UNITY_END();

}
