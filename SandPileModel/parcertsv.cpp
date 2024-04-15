#include "parcer.h"

void ParsingTsv(Matrix& matriks, Arguments& parameters, Iteration& iter) {
  int16_t x;
  int16_t y;
  int16_t x_symb;
  int16_t y_symbol;
  uint64_t three_symbol;
  uint64_t amount_of_grains;
  const char *file_name = parameters.input_file_name;
  matriks.max_width = 0;
  matriks.max_heigh = 0;
  std::ifstream file1;
  file1.open(file_name);

  if (!file1.is_open()) {
    std::cout << "FILE NOT OPENED1";
    return;
  } else {
    while (!file1.eof()) {
      file1 >> x_symb >> y_symbol >> three_symbol;
      if (!file1) {
        break;
      }
      if (x_symb > matriks.max_width) {
        matriks.max_width = x_symb;

      }
      if (y_symbol > matriks.max_heigh) {
        matriks.max_heigh = y_symbol;
      }
    }
  }

  matriks.max_width += 1;
  matriks.max_heigh += 1;
  uint64_t **colors1 = new uint64_t *[matriks.max_width]{};
  matriks.matrix = colors1;

  for (int16_t i = 0; i < (matriks.max_width); i++) {
    matriks.matrix[i] = new uint64_t[matriks.max_heigh]{};
  }

  file1.clear();
  file1.seekg(std::ios::beg);

  if (!file1.is_open()) {
    std::cout << "FILE NOT OPENED2";
    return;
  } else {
    while (!file1.eof()) {
      file1 >> x >> y >> amount_of_grains;
      if (!file1) {
        break;
      }
      matriks.matrix[x][y] = amount_of_grains;
      if (amount_of_grains >= 4) {
        iter.amount_of_not_ruined_cells++;
      }
    }
  }
}
