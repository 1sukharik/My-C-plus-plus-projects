
#include "interface.h"

std::string WiindDirection(int direction) {
  if (direction >= 22 & direction <= 67) {
    return "↗";
  } else if (direction > 67 & direction < 112) {
    return "→";
  } else if (direction >= 112 & direction <= 157) {
    return "↘";
  } else if (direction > 157 & direction < 202) {
    return "↓";
  } else if (direction >= 202 & direction <= 247) {
    return "↙";
  } else if (direction > 247 & direction < 292) {
    return "←";
  } else if (direction >= 292 & direction < 337) {
    return "↖";
  } else {
    return "↑";
  }
}

void Printer(CurrCity& curr_city) {
  using namespace ftxui;

  std::vector<std::string> cities;
  nlohmann::json parsed_config = ParseConfig("config.json");
  cities = parsed_config["cities"];

  nlohmann::json city_info = ExtractCityInformation(cities[curr_city.curr_city], parsed_config["database_file"]);
  std::string time_data;

  for (int i = 0; i < curr_city.number_of_days; i++) {
    city_info[i]["data"].get_to(time_data);

    city_info[i]["morning"]["precipitation"].get_to(curr_city.pr_morning);
    city_info[i]["morning"]["relativehumidity_2m"].get_to(curr_city.rh_morning);
    city_info[i]["morning"]["visibility"].get_to(curr_city.v_morning);
    city_info[i]["morning"]["weathercode"].get_to(curr_city.wec_morning);
    city_info[i]["morning"]["winddirection_10m"].get_to(curr_city.wd_morning);
    city_info[i]["morning"]["windspeed_10m"].get_to(curr_city.ws_morning);
    city_info[i]["morning"]["temperature_2m"].get_to(curr_city.temp_morning);

    city_info[i]["midday"]["precipitation"].get_to(curr_city.pr_midday);
    city_info[i]["midday"]["relativehumidity_2m"].get_to(curr_city.rh_midday);
    city_info[i]["midday"]["visibility"].get_to(curr_city.v_midday);
    city_info[i]["midday"]["weathercode"].get_to(curr_city.wec_midday);
    city_info[i]["midday"]["winddirection_10m"].get_to(curr_city.wd_midday);
    city_info[i]["midday"]["windspeed_10m"].get_to(curr_city.ws_midday);
    city_info[i]["midday"]["temperature_2m"].get_to(curr_city.temp_midday);

    city_info[i]["evening"]["precipitation"].get_to(curr_city.pr_evening);
    city_info[i]["evening"]["relativehumidity_2m"].get_to(curr_city.rh_evening);
    city_info[i]["evening"]["visibility"].get_to(curr_city.v_evening);
    city_info[i]["evening"]["weathercode"].get_to(curr_city.wec_evening);
    city_info[i]["evening"]["winddirection_10m"].get_to(curr_city.wd_evening);
    city_info[i]["evening"]["windspeed_10m"].get_to(curr_city.ws_evening);
    city_info[i]["evening"]["temperature_2m"].get_to(curr_city.temp_evening);

    city_info[i]["night"]["precipitation"].get_to(curr_city.pr_night);
    city_info[i]["night"]["relativehumidity_2m"].get_to(curr_city.rh_night);
    city_info[i]["night"]["visibility"].get_to(curr_city.v_night);
    city_info[i]["night"]["weathercode"].get_to(curr_city.wec_night);
    city_info[i]["night"]["winddirection_10m"].get_to(curr_city.wd_night);
    city_info[i]["night"]["windspeed_10m"].get_to(curr_city.ws_night);
    city_info[i]["night"]["temperature_2m"].get_to(curr_city.temp_night);

    std::string header = "WEATHER FORECAST IN " + cities[curr_city.curr_city] + " " + time_data.substr(0, 10);
    auto info = window(center(text(
                           header)),
                       hbox({{window(center(text("morning")), hbox({vbox({
                                                                             text(Symbols.find(CodesDefinitions.find(
                                                                                 curr_city.wec_morning)->second)->second[0]),
                                                                             text(Symbols.find(CodesDefinitions.find(
                                                                                 curr_city.wec_morning)->second)->second[1]),
                                                                             text(Symbols.find(CodesDefinitions.find(
                                                                                 curr_city.wec_morning)->second)->second[2]),
                                                                             text(Symbols.find(CodesDefinitions.find(
                                                                                 curr_city.wec_morning)->second)->second[3]),
                                                                             text(Symbols.find(CodesDefinitions.find(
                                                                                 curr_city.wec_morning)->second)->second[4])
                                                                         }),

                                                                    vbox({
                                                                             text(CodesDefinitions.find(curr_city.wec_morning)->second),
                                                                             text(std::to_string(curr_city.temp_morning)
                                                                                      + " °C"),
                                                                             text(WiindDirection(curr_city.wd_morning)
                                                                                      + std::to_string(curr_city.ws_morning)
                                                                                      + "km/h"),

                                                                             text(std::to_string(curr_city.v_morning)
                                                                                      + "m"),
                                                                             text(std::to_string(curr_city.pr_morning)
                                                                                      + "mm | "
                                                                                      + std::to_string(curr_city.rh_morning)
                                                                                      + "%")

                                                                         })})

                       )}, {window(center(text("midday")), hbox({vbox({
                                                                          text(Symbols.find(CodesDefinitions.find(
                                                                              curr_city.wec_midday)->second)->second[0]),
                                                                          text(Symbols.find(CodesDefinitions.find(
                                                                              curr_city.wec_midday)->second)->second[1]),
                                                                          text(Symbols.find(CodesDefinitions.find(
                                                                              curr_city.wec_midday)->second)->second[2]),
                                                                          text(Symbols.find(CodesDefinitions.find(
                                                                              curr_city.wec_midday)->second)->second[3]),
                                                                          text(Symbols.find(CodesDefinitions.find(
                                                                              curr_city.wec_midday)->second)->second[4])
                                                                      }),

                                                                 vbox({
                                                                          text(CodesDefinitions.find(curr_city.wec_midday)->second),
                                                                          text(std::to_string(curr_city.temp_midday)
                                                                                   + " °C"),
                                                                          text(WiindDirection(curr_city.wd_midday)
                                                                                   + std::to_string(curr_city.ws_midday)
                                                                                   + "km/h"),

                                                                          text(
                                                                              std::to_string(curr_city.v_midday) + "m"),
                                                                          text(std::to_string(curr_city.pr_midday)
                                                                                   + "mm | "
                                                                                   + std::to_string(curr_city.rh_midday)
                                                                                   + "%")
                                                                      })})

                       )}, {window(center(text("evening")), hbox({vbox({
                                                                           text(Symbols.find(CodesDefinitions.find(
                                                                               curr_city.wec_evening)->second)->second[0]),
                                                                           text(Symbols.find(CodesDefinitions.find(
                                                                               curr_city.wec_evening)->second)->second[1]),
                                                                           text(Symbols.find(CodesDefinitions.find(
                                                                               curr_city.wec_evening)->second)->second[2]),
                                                                           text(Symbols.find(CodesDefinitions.find(
                                                                               curr_city.wec_evening)->second)->second[3]),
                                                                           text(Symbols.find(CodesDefinitions.find(
                                                                               curr_city.wec_evening)->second)->second[4])
                                                                       }),

                                                                  vbox({
                                                                           text(CodesDefinitions.find(curr_city.wec_evening)->second),
                                                                           text(std::to_string(curr_city.temp_evening)
                                                                                    + " °C"),
                                                                           text(WiindDirection(curr_city.wd_evening)
                                                                                    + std::to_string(curr_city.ws_evening)
                                                                                    + "km/h"),

                                                                           text(std::to_string(curr_city.v_evening)
                                                                                    + "m"),
                                                                           text(std::to_string(curr_city.pr_evening)
                                                                                    + "mm | "
                                                                                    + std::to_string(curr_city.rh_evening)
                                                                                    + "%")
                                                                       })})

                       )}, {window(center(text("night")), hbox({vbox({
                                                                         text(Symbols.find(CodesDefinitions.find(
                                                                             curr_city.wec_night)->second)->second[0]),
                                                                         text(Symbols.find(CodesDefinitions.find(
                                                                             curr_city.wec_night)->second)->second[1]),
                                                                         text(Symbols.find(CodesDefinitions.find(
                                                                             curr_city.wec_night)->second)->second[2]),
                                                                         text(Symbols.find(CodesDefinitions.find(
                                                                             curr_city.wec_night)->second)->second[3]),
                                                                         text(Symbols.find(CodesDefinitions.find(
                                                                             curr_city.wec_night)->second)->second[4])
                                                                     }),

                                                                vbox({
                                                                         text(CodesDefinitions.find(curr_city.wec_night)->second),
                                                                         text(std::to_string(curr_city.temp_night)
                                                                                  + " °C"),
                                                                         text(WiindDirection(curr_city.wd_night)
                                                                                  + std::to_string(curr_city.ws_night)
                                                                                  + "km/h"),

                                                                         text(std::to_string(curr_city.v_night) + "m"),
                                                                         text(std::to_string(curr_city.pr_night)
                                                                                  + "mm | "
                                                                                  + std::to_string(curr_city.rh_night)
                                                                                  + "%")
                                                                     })})

                       )}})  //
    );

    auto screen = Screen::Create(Dimension::Fit(info), Dimension::Fit(info));
    Render(screen, info);
    screen.Print();
    std::cout << "\n";

  }

}

CurrCity Next(CurrCity& curr_city) {
  if ((curr_city.curr_city + 1) >= curr_city.number_of_cities) {
    curr_city.curr_city = 0;
  } else {
    curr_city.curr_city++;
  }

  return curr_city;
}

CurrCity Prev(CurrCity& curr_city) {
  if ((curr_city.curr_city - 1) < 0) {
    curr_city.curr_city = curr_city.number_of_cities - 1;
  } else {
    curr_city.curr_city--;
  }

  return curr_city;

}

CurrCity Plus(CurrCity& curr_city) {
  if ((curr_city.number_of_days + 1) > 16) {
    curr_city.number_of_days = 1;
  } else {
    curr_city.number_of_days++;
  }

  return curr_city;

}

CurrCity Minus(CurrCity& curr_city) {
  if ((curr_city.number_of_days - 1) <= 0) {
    curr_city.number_of_days = 16;
  } else {
    curr_city.number_of_days--;
  }

  return curr_city;
}
