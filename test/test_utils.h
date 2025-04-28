#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>


void transform_grid(uint32_t expect_grid[], uint32_t expect_map[], uint32_t color, int size);

extern uint32_t map_piece_S_rx0[];
extern uint32_t map_piece_S_rx1[];
extern uint32_t map_piece_S_rx2[];
extern uint32_t map_piece_S_rx3[];

#endif
