#include "parcer.h"
#include "operations.h"

int main(int argc, char **argv) {
  Arguments parameters;
  Parsing(argc, argv, parameters);
  CreateArchive(parameters);
}
