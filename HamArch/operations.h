
#ifndef LABWORK6_1SUKHARIK__OPERATIONS_H_
#define LABWORK6_1SUKHARIK__OPERATIONS_H_
#include "parcer.h"
#include "iostream"
#include <fstream>
#include <cstdint>
#include "cstring"
#include "vector"
void AddToArchive(std::string& filename, std::string& archname, Arguments& parameters);

void CreateArchive(Arguments& parameters);

void ExtractAll(std::string& out, Arguments& parameters);

bool IsName(std::string& filename);

void Merge(Arguments& parameters);

void Delete(std::string& inp, std::string& out, Arguments& parameters);

void Extract(std::string& inp, std::string& out, Arguments& parameters);

void Append(std::string& archive, std::string& archive2, Arguments& parameters);

void List(std::string& archive,Arguments& parameters);

void Create(std::string& archive, Arguments& parameters);

#endif //LABWORK6_1SUKHARIK__OPERATIONS_H_
