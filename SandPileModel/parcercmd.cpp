#include "parcer.h"
const int minimum_parameters = 2;
const int maximum_parameters = 9;
void Parsing(int argc, char **argv, Arguments& parameters) {
  if ((argc < minimum_parameters) || (argc > maximum_parameters)) {
    std::cout << "NOT NECESSARY AMOUNT OF PARAMETRS";
    return;
  } else {
    int i = 1;
    while (i < argc) {
      char *arg;
      arg = argv[i];
      if (!(strcmp(arg, "-i")) || !(strcmp(arg, "--input"))) {
        if ((i + 1) < argc) {
          parameters.input_file_name = argv[i + 1];

        } else {
          std::cout << "NO INPUT FILE";
          return;
        }
      } else if (!(strcmp(arg, "-o")) || !(strcmp(arg, "--output"))) {
        if ((i + 1) < argc) {
          parameters.output_file_name = argv[i + 1];

        } else {
          std::cout << "NO OUTPUT FILE";
          return;
        }
      } else if (!(strcmp(arg, "-f")) || !(strcmp(arg, "--freq"))) {
        if ((i + 1) < argc) {
          parameters.freq = std::stoi(argv[i + 1]);

        } else {
          std::cout << "NO FREQ PARAMETR";
          return;
        }
      } else if (!(strcmp(arg, "-m")) || !(strcmp(arg, "--max-iter"))) {
        if ((i + 1) < argc) {
          parameters.iterations = std::stoi(argv[i + 1]);

        } else {
          std::cout << "NO ITERATION PARAMETR";
          return;
        }
      }
      i += 2;
    }
  }

}
