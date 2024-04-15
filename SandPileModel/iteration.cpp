#include "parcer.h"
#include "image.h"
#include "iteration.h"

uint64_t **ExpandVertical(uint64_t **arr, bool flag, int16_t width, int16_t height) {
  uint64_t **added = new uint64_t *[width];
  for (int16_t i = 0; i < width; i++)
    added[i] = new uint64_t[height + 1]{};
  //добавление справа
  if (flag) {

    for (int16_t i = 0; i < width; i++) {
      for (int16_t j = 0; j < height; j++) {
        added[i][j] = arr[i][j];
      }
    }
  } else {
    for (int16_t i = 0; i < width; i++) {
      for (int16_t j = 1; j < height + 1; j++) {
        added[i][j] = arr[i][j - 1];
      }
    }
  }

  for (int16_t i = 0; i < width; i++) {
    arr[i] = new uint64_t[height]{};
  }
  delete[] arr;

  return added;
}

uint64_t **ExpandHorizontal(uint64_t **arr, bool flag, int16_t width, int16_t height) {
  uint64_t **added = new uint64_t *[width + 1];
  for (int16_t i = 0; i < (width + 1); i++)
    added[i] = new uint64_t[height]{};

  if (flag) {
    //добавление линии сверху
    for (int16_t i = 1; i < width + 1; i++) {
      for (int16_t j = 0; j < height; j++) {
        added[i][j] = arr[i - 1][j];
      }
    }

  } else {
    //добавление снизу
    for (int16_t i = 0; i < width; i++) {
      for (int16_t j = 0; j < height; j++) {
        if (i < width) {
          added[i][j] = arr[i][j];
        }
      }
    }
  }

  for (int16_t i = 0; i < width; i++) {
    arr[i] = new uint64_t[height]{};
  }
  delete[] arr;

  return added;
}

void CountingInappropriate(Iteration& iter, Matrix& matriks, int i, int j) {
  std::vector<int> b;

  for (int i1 = 0; i1 < iter.coordinates.size(); i1++) {
    while (iter.coordinates[i1].size() <= (j+1)) {
      iter.coordinates[i1].push_back(0);
    }
  }
  while (b.size() <= (j+1)) {
    b.push_back(0);
  }
  while (iter.coordinates.size() <= (i+1)) {
    iter.coordinates.push_back(b);
  }

  iter.amount_of_not_ruined_cells--;
  if (matriks.matrix[i][j] >= 4) {
    iter.amount_of_not_ruined_cells++;
  }
  if (matriks.matrix[i + 1][j] == 4) {
    iter.amount_of_not_ruined_cells++;
    iter.coordinates[i + 1][j] = 1;
  }
  if (matriks.matrix[i - 1][j] == 4) {
    iter.amount_of_not_ruined_cells++;
    iter.coordinates[i - 1][j] = 1;
  }
  if (matriks.matrix[i][j + 1] == 4) {
    iter.amount_of_not_ruined_cells++;
    iter.coordinates[i][j + 1] = 1;
  }
  if (matriks.matrix[i][j - 1] == 4) {
    iter.amount_of_not_ruined_cells++;
    iter.coordinates[i][j - 1] = 1;
  }

}

void Iterations(Arguments& parameters, Iteration& iter, Matrix& matriks) {

  int counter_for_frequency = 0;

  for (int curr_iteration = 0; curr_iteration < parameters.iterations; curr_iteration++) {
    if (iter.amount_of_not_ruined_cells > 0) {
      if (parameters.freq != 0) {
        std::cout << "ITERATION " << curr_iteration << '\n';
        if (counter_for_frequency % parameters.freq == 0) {
          MakingImage(matriks, parameters, counter_for_frequency);
        }
      }
      for (int16_t i = 0; i < matriks.max_width; i++) {
        for (int16_t j = 0; j < matriks.max_heigh; j++) {
          if ((matriks.matrix[i][j] >= 4)
              && ((iter.coordinates.size() > i && iter.coordinates[i].size() > j && iter.coordinates[i][j] == 0) || (
                  iter.coordinates.size() <= i) || (iter.coordinates.size() > i && iter.coordinates[i].size() <= j))) {


            if ((i - 1) < 0) {
              i += 1;
              matriks.matrix =
                  ExpandHorizontal(matriks.matrix, true, matriks.max_width, matriks.max_heigh);
              matriks.max_width++;

            }

            if ((i + 1) == matriks.max_width) {
              matriks.matrix =
                  ExpandHorizontal(matriks.matrix, false, matriks.max_width, matriks.max_heigh);
              matriks.max_width++;

            }

            if ((j + 1) == matriks.max_heigh) {
              matriks.matrix =
                  ExpandVertical(matriks.matrix, true, matriks.max_width, matriks.max_heigh);
              matriks.max_heigh++;

            }

            if ((j - 1) < 0) {
              j++;
              matriks.matrix =
                  ExpandVertical(matriks.matrix, false, matriks.max_width, matriks.max_heigh);
              matriks.max_heigh++;

            }

            matriks.matrix[i][j] -= 4;
            ++matriks.matrix[i + 1][j];
            ++matriks.matrix[i - 1][j];
            ++matriks.matrix[i][j + 1];
            ++matriks.matrix[i][j - 1];
            CountingInappropriate(iter, matriks, i, j);

          }
        }
      }
      counter_for_frequency++;

      iter.coordinates.clear();

    }

  }
  std::cout << "ITERATION " << counter_for_frequency << " " << std::endl;
  MakingImage(matriks, parameters, counter_for_frequency);
}
