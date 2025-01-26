#include "interface.h"

using json = nlohmann::json;
using namespace ftxui;

int main(int argc, char **argv) {

  std::cout << "WRITE CITIES:\n";
  std::string city_enter = "";

  nlohmann::json config_parsed = ParseConfig("config.json");
  std::ofstream OurDatabase2(config_parsed["database_file"]);
  OurDatabase2 << "{}";
  OurDatabase2.close();

  std::vector<std::string> all_cities;
  CurrCity curr_city;
  while (city_enter != "end") {
    std::getline(std::cin, city_enter);
    if (city_enter != "end") {
      all_cities.push_back(city_enter);
      AddCityToDatabase(city_enter, config_parsed["database_file"]);
      curr_city.number_of_cities++;

    }
  }
  AddCitiesToConfig(all_cities, "config.json");

  bool ex = false;
  while (!ex) {
    system("CLS");
    Printer(curr_city);
    int ch = getch();

    switch (ch) {
      case 110:curr_city = Next(curr_city);//n
        break;
      case 112:curr_city = Prev(curr_city);//p
        break;
      case 43:curr_city = Plus(curr_city);//+
        break;
      case 45:curr_city = Minus(curr_city);//-
        break;
      case 27:ex = true;
        break;

    }
  }
}
