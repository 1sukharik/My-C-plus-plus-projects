#ifndef LABWORK32_LABWORK3_1SUKHARIK_PARCER_H_
#define LABWORK32_LABWORK3_1SUKHARIK_PARCER_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdint>
#include "vector"

struct Arguments {
  const char* input_file_name;
  const char* output_file_name;
  int iterations = 0;
  int freq;
};

struct Matrix {
  int16_t max_heigh;
  int16_t max_width;
  uint64_t** matrix;
};
struct Iteration {
  int amount_of_not_ruined_cells = 0;
  std::vector<std::vector<int>> coordinates;
};

void Parsing(int argc, char **argv, Arguments& parameters);
void ParsingTsv(Matrix& matriks, Arguments& parameters, Iteration& iter);

#endif //LABWORK32_LABWORK3_1SUKHARIK_PARCER_H_
