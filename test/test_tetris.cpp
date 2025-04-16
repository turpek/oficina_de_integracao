#include "Unity/unity.h"
#include "tetris/tetris.h"


void setUp(void){};

void tearDown(void){};


void test_decodePiece_I(){
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


int main(){
  UNITY_BEGIN();
  RUN_TEST(test_decodePiece_I);
  return UNITY_END();

}
