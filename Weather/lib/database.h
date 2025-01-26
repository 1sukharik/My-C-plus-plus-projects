#ifndef LABWORK7_1SUKHARIK__DATABASE_H_
#define LABWORK7_1SUKHARIK__DATABASE_H_

#include "fstream"
#include "iostream"

#include "nlohmann/json.hpp"
#include "cpr/cpr.h"

bool IsCityInDatabase(std::string name_of_city, std::string database_name);
void AddCityToDatabase(std::string name_of_city, std::string database_name);
void AddCitiesToConfig(std::vector<std::string>& all_cities, std::string database_name);
nlohmann::json ParseWeatherForOneCity(std::string name_of_city);
nlohmann::json ExtractCityInformation(std::string name_of_city, std::string database_name);
nlohmann::json ParseConfig(std::string name_of_config);

#endif //LABWORK7_1SUKHARIK__DATABASE_H_
