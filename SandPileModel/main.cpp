#include "parcer.h"
#include "iteration.h"

int main(int argc, char **argv) {
  Arguments parameters;
  Matrix matriks;
  Iteration iter;
  Parsing(argc, argv, parameters);
  ParsingTsv(matriks, parameters, iter);
  Iterations(parameters, iter, matriks);


}
