#include "database.h"

bool IsCityInDatabase(std::string name_of_city, std::string database_name) {
  std::ifstream OurDatabase(database_name);
  nlohmann::json data = nlohmann::json::parse(OurDatabase);
  OurDatabase.close();
  return data.contains(name_of_city);
}

nlohmann::json ParseWeatherForOneCity(std::string name_of_city) {
  std::cout << "1";
  cpr::Response
      city_request = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"}, cpr::Parameters{{"name", name_of_city}},
                              cpr::Header{{"X-Api-Key", "MERhjr93E191dx68quD9gQ==ygvssTWHfrtWmLqO"}});
  std::cout << "2";

  std::string for_parse = city_request.text.substr(1, city_request.text.size() - 2);
  std::cout << for_parse;
  nlohmann::json parsed_json = nlohmann::json::parse(for_parse);

  nlohmann::json latitude = parsed_json["latitude"];
  nlohmann::json longitude = parsed_json["longitude"];

  int count_of_days = 16;

  cpr::Response weather_request = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                           cpr::Parameters{{"latitude", latitude.dump()},
                                                           {"longitude", longitude.dump()},
                                                           {"hourly", "windspeed_10m"},
                                                           {"hourly", "winddirection_10m"},
                                                           {"hourly", "weathercode"},
                                                           {"hourly", "temperature_2m"},
                                                           {"hourly", "apparent_temperature"},
                                                           {"hourly", "relativehumidity_2m"},
                                                           {"hourly", "precipitation"},
                                                           {"hourly", "visibility"},
                                                           {"forecast_days", std::to_string(count_of_days)}});
  nlohmann::json json_forecast = nlohmann::json::parse(weather_request.text);

  return json_forecast;

}

void AddCityToDatabase(std::string name_of_city, std::string database_name) {

  std::ifstream OurDatabase(database_name);
  if (!OurDatabase.is_open()) {
    std::cout << "CHECK JSON DATABASE FILE";
    return;
  }
  nlohmann::json city = nlohmann::json::parse(OurDatabase);
  OurDatabase.close();
  nlohmann::json forecast = ParseWeatherForOneCity(name_of_city);

  int i2 = 0;
  for (int all_days = 0; all_days < 384; all_days += 24) {

    city[name_of_city].push_back({});
    city[name_of_city][i2]["data"] = forecast["hourly"]["time"][all_days];

    city[name_of_city][i2]["night"]["windspeed_10m"] = forecast["hourly"]["windspeed_10m"][all_days];
    city[name_of_city][i2]["night"]["winddirection_10m"] = forecast["hourly"]["winddirection_10m"][all_days];
    city[name_of_city][i2]["night"]["weathercode"] = forecast["hourly"]["weathercode"][all_days];
    city[name_of_city][i2]["night"]["temperature_2m"] = forecast["hourly"]["temperature_2m"][all_days];
    city[name_of_city][i2]["night"]["apparent_temperature"] = forecast["hourly"]["apparent_temperature"][all_days];
    city[name_of_city][i2]["night"]["relativehumidity_2m"] = forecast["hourly"]["relativehumidity_2m"][all_days];
    city[name_of_city][i2]["night"]["precipitation"] = forecast["hourly"]["precipitation"][all_days];
    city[name_of_city][i2]["night"]["visibility"] = forecast["hourly"]["visibility"][all_days];

    city[name_of_city][i2]["morning"]["windspeed_10m"] = forecast["hourly"]["windspeed_10m"][all_days + 6];
    city[name_of_city][i2]["morning"]["winddirection_10m"] = forecast["hourly"]["winddirection_10m"][all_days + 6];
    city[name_of_city][i2]["morning"]["weathercode"] = forecast["hourly"]["weathercode"][all_days + 6];
    city[name_of_city][i2]["morning"]["temperature_2m"] = forecast["hourly"]["temperature_2m"][all_days + 6];
    city[name_of_city][i2]["morning"]["apparent_temperature"] =
        forecast["hourly"]["apparent_temperature"][all_days + 6];
    city[name_of_city][i2]["morning"]["relativehumidity_2m"] =
        forecast["hourly"]["relativehumidity_2m"][all_days + 6];
    city[name_of_city][i2]["morning"]["precipitation"] = forecast["hourly"]["precipitation"][all_days + 6];
    city[name_of_city][i2]["morning"]["visibility"] = forecast["hourly"]["visibility"][all_days + 6];

    city[name_of_city][i2]["midday"]["windspeed_10m"] = forecast["hourly"]["windspeed_10m"][all_days + 12];
    city[name_of_city][i2]["midday"]["winddirection_10m"] = forecast["hourly"]["winddirection_10m"][all_days + 12];
    city[name_of_city][i2]["midday"]["weathercode"] = forecast["hourly"]["weathercode"][all_days + 12];
    city[name_of_city][i2]["midday"]["temperature_2m"] = forecast["hourly"]["temperature_2m"][all_days + 12];
    city[name_of_city][i2]["midday"]["apparent_temperature"] =
        forecast["hourly"]["apparent_temperature"][all_days + 12];
    city[name_of_city][i2]["midday"]["relativehumidity_2m"] =
        forecast["hourly"]["relativehumidity_2m"][all_days + 12];
    city[name_of_city][i2]["midday"]["precipitation"] = forecast["hourly"]["precipitation"][all_days + 12];
    city[name_of_city][i2]["midday"]["visibility"] = forecast["hourly"]["visibility"][all_days + 12];

    city[name_of_city][i2]["evening"]["windspeed_10m"] = forecast["hourly"]["windspeed_10m"][all_days + 18];
    city[name_of_city][i2]["evening"]["winddirection_10m"] = forecast["hourly"]["winddirection_10m"][all_days + 18];
    city[name_of_city][i2]["evening"]["weathercode"] = forecast["hourly"]["weathercode"][all_days + 18];
    city[name_of_city][i2]["evening"]["temperature_2m"] = forecast["hourly"]["temperature_2m"][all_days + 18];
    city[name_of_city][i2]["evening"]["apparent_temperature"] =
        forecast["hourly"]["apparent_temperature"][all_days + 18];
    city[name_of_city][i2]["evening"]["relativehumidity_2m"] =
        forecast["hourly"]["relativehumidity_2m"][all_days + 18];
    city[name_of_city][i2]["evening"]["precipitation"] = forecast["hourly"]["precipitation"][all_days + 18];
    city[name_of_city][i2]["evening"]["visibility"] = forecast["hourly"]["visibility"][all_days + 18];
    i2++;
  }

  std::ofstream OurDatabase2(database_name);
  OurDatabase2 << std::setw(4) << city;
  OurDatabase2.close();

}

void AddCitiesToConfig(std::vector<std::string>& all_cities, std::string name_of_config) {
  std::ifstream OurDatabase(name_of_config);
  nlohmann::json data = nlohmann::json::parse(OurDatabase);
  data["cities"] = all_cities;
  OurDatabase.close();

  std::ofstream OurDatabase2(name_of_config);
  OurDatabase2 << std::setw(4) << data;
  OurDatabase2.close();

}

nlohmann::json ExtractCityInformation(std::string name_of_city, std::string database_name) {
  std::ifstream OurDatabase(database_name);
  nlohmann::json data = nlohmann::json::parse(OurDatabase);
  nlohmann::json city_info = data[name_of_city];
  OurDatabase.close();
  return city_info;
}

nlohmann::json ParseConfig(std::string name_of_config) {
  std::ifstream OurDatabase(name_of_config);
  nlohmann::json data = nlohmann::json::parse(OurDatabase);
  OurDatabase.close();
  return data;
}
