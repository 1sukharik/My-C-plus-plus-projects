#ifndef LABWORK32_LABWORK3_1SUKHARIK_ITERATION_H_
#define LABWORK32_LABWORK3_1SUKHARIK_ITERATION_H_

#include "parcer.h"

#include "image.h"

uint64_t **MoreMemoryHeigh(uint64_t **arr, bool flag, int16_t w, int16_t h);
uint64_t **MoreMemoryWidth(uint64_t **arr, bool flag, int16_t w, int16_t h);
void Iterations(Arguments& parameters, Iteration& iter, Matrix& matriks);
void CountingInappropriate(Iteration& iter, Matrix& matriks, int i, int j);

#endif //LABWORK32_LABWORK3_1SUKHARIK_ITERATION_H_
