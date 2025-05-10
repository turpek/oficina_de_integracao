#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>


void transform_grid(uint32_t expect_grid[], uint32_t expect_map[], uint32_t color, int size);

extern uint32_t map_piece_S_rx0[];
extern uint32_t map_piece_S_rx1[];
extern uint32_t map_piece_S_rx2[];
extern uint32_t map_piece_S_rx3[];
extern uint32_t map_piece_S_rx0_movX1Y0[];
extern uint32_t map_piece_S_rx0_movX0Y1[];
extern uint32_t map_piece_S_rx0_movX1Y1[];
extern uint32_t map_piece_S_rx0_movX1Y1[];
extern uint32_t map_piece_S_rx0_movX_1Y0[];
extern uint32_t map_piece_S_rx0_movX0Y_1[];
extern uint32_t map_piece_S_rx0_movX_1Y_1[];
extern uint32_t map_piece_S_rx0_movX_1_Y_1[];

extern uint32_t map_piece_S_rx0_movX5Y14[];
extern uint32_t map_piece_S_rx0_movX6Y14[];
extern uint32_t map_piece_S_rx0_movX5Y15[];
extern uint32_t map_piece_S_rx0_movX6Y15[];

extern uint32_t map_rotation_L_OR[];
extern uint32_t map_rotation_L_R2[];
extern uint32_t map_rotation_shift_2x[];

#endif
