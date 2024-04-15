#include "parcer.h"
#include "operations.h"

const int START_INDEX_FOR_FILE = 7;

void Parsing(int argc, char **argv) {
  Arguments parameters;
  parameters.is_creating_new_archive = false;
  int i = 0;
  while (i < argc) {
    char *arg;
    arg = argv[i];

    if (!(strcmp(arg, "-c")) || !(strcmp(arg, "--create"))) {
      parameters.is_creating_new_archive = true;

      i++;
    } else if (!(strcmp(arg, "-f")) || !(strncmp(arg, "--file", 6))) {
      if (parameters.is_creating_new_archive) {
        std::string arch_name;
        if (argv[i][1] == '-') {
          for (int j = START_INDEX_FOR_FILE; j < strlen(argv[i]); j++) {
            arch_name += argv[i][j];
          }
        } else {
          arch_name = argv[i + 1];
          i++;
        }
        parameters.curr_archive = arch_name;
//        Create(parameters.curr_archive, parameters);
        parameters.is_creating_new_archive = false;
        i++;
      } else {
        std::string arch_name;
        if (argv[i][1] == '-') {
          for (int j = START_INDEX_FOR_FILE; j < strlen(argv[i]); j++) {
            arch_name += argv[i][j];
          }
          i++;
        } else {
          arch_name = argv[i + 1];
          i += 2;
        }
        parameters.curr_archive = arch_name;
      }

    } else if (!(strcmp(arg, "-l")) || !(strcmp(arg, "--list"))) {
      parameters.is_show_archive = true;
      i++;

    } else if (!(strcmp(arg, "-x")) || !(strcmp(arg, "--extract"))) {
      parameters.is_extract = true;
      if (argv[i + 1][0] == '-') {
        parameters.is_extract_all = true;
        i++;
      } else {
        parameters.extract_file = argv[i + 1];
        i += 2;
      }

    } else if (!(strcmp(arg, "-s")) || !(strcmp(arg, "--blocksize"))) {
      parameters.hamm_block_size = std::stoi(argv[i + 1]);
      i += 2;

    } else if (!(strcmp(arg, "-a")) || !(strcmp(arg, "--append"))) {
      parameters.is_append_file = true;
      parameters.append_file = argv[i + 1];
      i += 2;

    } else if (!(strcmp(arg, "-d")) || !(strcmp(arg, "--delete"))) {
      parameters.is_delete_file = true;
      parameters.delete_file = argv[i + 1];
      i += 2;

    } else if (!(strcmp(arg, "-A")) || !(strcmp(arg, "--concatenate"))) {
      parameters.merge_first = argv[i + 1];
      parameters.merge_second = argv[i + 2];
      parameters.is_concatenate = true;
      i += 2;

    } else {
      i++;
    }

  }
}
