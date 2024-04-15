#include "operations.h"
#include "hamming_coding.h"

bool IsName(std::string& filename) {
  for (int i = 0; i < filename.size(); i++) {
    if (filename[i] == '.') {
      return true;
    }
  }
  return false;

}
void CreateArchive(Arguments& parameters) {
  if (parameters.is_delete_file) {
    Delete(parameters.delete_file, parameters.curr_archive, parameters);
    parameters.delete_file = false;

  } else if (parameters.is_concatenate) {
    Merge(parameters);
    parameters.is_concatenate = false;

  } else if (parameters.is_append_file) {
    AddToArchive(parameters.append_file, parameters.curr_archive, parameters);
    parameters.is_append_file = false;

  } else if (parameters.is_extract_all) {
    ExtractAll(parameters.curr_archive, parameters);
    parameters.is_extract_all = false;

  } else if (parameters.is_show_archive) {
    List(parameters.curr_archive, parameters);
    parameters.is_show_archive = false;

  } else if (parameters.is_extract) {
    Extract(parameters.extract_file, parameters.curr_archive, parameters);
    parameters.extract_file = false;
  }
}
void AddToArchive(std::string& file_name, std::string& arch_name, Arguments& parameters) {
  std::ifstream file(file_name, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "I CANT OPEN THIS FILE: " << file_name << std::endl;
    return;
  }

  file.seekg(0, std::ios::end);
  int file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  char *all_information = new char[file_size];
  file.read(all_information, file_size);
  file.close();
  std::string binary_string;

  std::ofstream output_file(arch_name, std::ios::binary | std::ofstream::app);
  output_file << file_name << "\n";
  for (int i = 0; i < file_size; i++) {
    std::bitset<8> binary_representation(all_information[i]);
    binary_string += binary_representation.to_string();
  }
  if (parameters.hamm_block_size == 0) {
    parameters.hamm_block_size = binary_string.size();
  }
  if (parameters.hamm_block_size == 0) {
    output_file << binary_string.size() << "\n";
  } else {
    output_file << parameters.hamm_block_size << "\n";
  }
  binary_string = MakeHamming(binary_string, parameters.hamm_block_size);
  binary_string += "$\n";
  output_file << binary_string;
  output_file.close();

  delete[] all_information;

}

void Append(std::string& archive, std::string& archive2, Arguments& parameters) {
  AddToArchive(archive, parameters.curr_archive, parameters);
  AddToArchive(archive2, parameters.curr_archive, parameters);

}

void Merge(Arguments& parameters) {
  Append(parameters.merge_first, parameters.merge_second, parameters);
}

void DeleteFile(const std::string& file_name) {
  std::string path = file_name;
  if (std::remove(path.c_str()) != 0) {
    std::cerr << "I CANT DELETE THIS FILE: " << file_name << std::endl;
  }
}

void Delete(std::string& output_file, std::string& input_file, Arguments& parameters) {
  std::string binary_string;
  std::string name_of_file;

  std::string help_file_name = "vinikogdaneназовётеtakфke.txt";

  std::ofstream help_file(help_file_name);

  std::ifstream archive(input_file);
  while (!archive.eof()) {
    std::getline(archive, name_of_file);
    if (name_of_file == output_file) {

      char symbol;
      archive.get(symbol);
      std::getline(archive, name_of_file);
      while (symbol != '$') {
        binary_string += symbol;
        archive.get(symbol);
      }
      archive.get(symbol);
    } else {
      if (name_of_file != "") {
        help_file << name_of_file << "\n";
      }
    }

  }

  if (archive.is_open()) {
    archive.close();
  } else {
    std::cout << "I CANT OPEN FILE" << std::endl;
    return;
  }

  help_file.close();

  std::ifstream help_file1(help_file_name);

  DeleteFile(input_file);

  std::ofstream input_archive(input_file);

  while (!help_file1.eof()) {
    std::getline(help_file1, name_of_file);
    if (name_of_file != "") {
      input_archive << name_of_file << "\n";
    }
  }
  help_file1.close();
  DeleteFile(help_file_name);
  input_archive.close();

}

void Extract(std::string& output_file, std::string& input_file, Arguments& parameters) {
  std::string binary_string;
  std::string name_of_file;

  std::string help_file_name = "vinikogdaneназовётеtakфke.txt";

  std::ofstream help_file(help_file_name);

  std::ifstream archive(input_file);
  while (!archive.eof()) {
    std::getline(archive, name_of_file);
    if (name_of_file == output_file) {

      char symbol;
      std::getline(archive, name_of_file);
      parameters.hamm_block_size = std::stoi(name_of_file);
      archive.get(symbol);

      while (symbol != '$') {
        binary_string += symbol;
        archive.get(symbol);
      }
      archive.get(symbol);
    } else {
      if (name_of_file != "") {
        help_file << name_of_file << "\n";
      }
    }

  }

  if (archive.is_open()) {
    archive.close();
  } else {
    std::cout << "I CANT CREATE FILE" << std::endl;
    return;
  }

  help_file.close();

  std::ifstream help_file1(help_file_name);

  DeleteFile(input_file);

  std::ofstream input_archive(input_file);

  while (!help_file1.eof()) {
    std::getline(help_file1, name_of_file);
    if (name_of_file != "") {
      input_archive << name_of_file << "\n";
    }
  }
  help_file1.close();
  DeleteFile(help_file_name);
  binary_string = CheckHamming(binary_string, parameters.hamm_block_size);

  std::ofstream outputed_file(output_file, std::ios::binary);
  if (outputed_file.is_open()) {
    for (int i = 0; i < binary_string.size(); i += 8) {
      std::string byte_string = binary_string.substr(i, 8);
      char byte = static_cast<char>(std::stoi(byte_string, nullptr, 2));
      outputed_file.write(&byte, 1);
    }
    outputed_file.close();
  } else {
    std::cout << "I CANT CREATE FILE\n";
    return;
  }
}

void ExtractAll(std::string& input_file, Arguments& parameters) {
  std::vector<std::string> file_names;
  std::string name_of_file;
  std::ifstream inp_file(input_file);
  while (!inp_file.eof()) {
    std::getline(inp_file, name_of_file);
    if (IsName(name_of_file)) {
      file_names.push_back(name_of_file);
    }
  }
  inp_file.close();
  for (int j = 0; j < file_names.size(); j++) {
    Extract(file_names[j], input_file, parameters);
  }

}

void Create(std::string& archive, Arguments& parameters) {
  std::ofstream output(archive + ".haf", std::ios::binary);
  output.close();
}

void List(std::string& archive, Arguments& parameters) {
  std::string name_of_file;
  std::ifstream inp_file(archive);
  while (!inp_file.eof()) {
    std::getline(inp_file, name_of_file);
    if (IsName(name_of_file)) {
      std::cout << name_of_file << " ";
    }
  }
  inp_file.close();
}
