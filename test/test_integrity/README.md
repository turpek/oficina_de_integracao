## Descrição dos arquivos

### test_pecas.ino

Código escrito para testar a função **`add_piece_to_grid`** em uma simulação, para isso criamos uma 'matriz' de led do tipo *ws2812*  em série, de forma a forma uma matriz 4x4, com isso simulamos todas as peças e todas as rotações possíveis.

Com esse código também é possível fazer o teste em uma matriz de LEDS real, para isso deve-se trocar os valores de `GRID_W` e `GRID_H` pela dimensão real da matriz.
