#ifndef LABWORK7_1SUKHARIK__INTERFACE_H_
#define LABWORK7_1SUKHARIK__INTERFACE_H_

#include "database.h"

#include <string>

#include <unordered_map>

#include "unistd.h"
#include <conio.h>

#include <stdlib.h>  // for EXIT_SUCCESS
#include <memory>    // for allocator, __shared_ptr_access
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, Element, operator|, window, flex, vbox

struct CurrCity {
  int curr_city;
  int number_of_days;
  int number_of_cities;
  int temp_morning;
  int temp_midday;
  int temp_evening;
  int temp_night;

  int wd_morning;
  int wd_midday;
  int wd_evening;
  int wd_night;

  int ws_morning;
  int ws_midday;
  int ws_evening;
  int ws_night;

  int wec_morning;
  int wec_midday;
  int wec_evening;
  int wec_night;

  int pr_morning;
  int pr_midday;
  int pr_evening;
  int pr_night;

  int rh_morning;
  int rh_midday;
  int rh_evening;
  int rh_night;

  int v_morning;
  int v_midday;
  int v_evening;
  int v_night;

  CurrCity() {
    curr_city = 0;
    number_of_days = 1;
    number_of_cities = 0;
  }
};

const std::unordered_map<int, std::string> CodesDefinitions = {{0, "Ясно"}, {1, "Малооблачно"},
                                                               {2, "Облачно"}, {3, "Пасмурно"},
                                                               {45, "Туман"}, {48, "Изморозь"},
                                                               {51, "Легкий моросящий дождь"},
                                                               {53, "Легкий моросящий дождь"},
                                                               {55, "Средний моросящий дождь"},
                                                               {56, "Моросящий дождь со снегом"},
                                                               {57, "Моросящий дождь со снегом"},
                                                               {61, "Легкий дождь"}, {63, "Дождь"},
                                                               {65, "Сильный дождь"},
                                                               {66, "Легкий дождь со снегом"}, {67, "Дождь со снегом"},
                                                               {71, "Небольшой снег"}, {73, "Снег"},
                                                               {75, "Сильный снег"},
                                                               {77, "Лёгкий снег"},
                                                               {80, "Небольшой ливень"}, {81, "Ливень"},
                                                               {82, "Сильный ливень"},
                                                               {85, "Снегопад"}, {86, "Сильный снегопад"},
                                                               {95, "Гроза"},
                                                               {96, "Гроза с незначительным градом"},
                                                               {99, "Гроза с градом"}
};

const std::unordered_map<std::string, std::vector<std::string>> Symbols = {
    {"Неизвестно", {
        "    .-.      ",
        "     __)     ",
        "    (        ",
        "     `-’     ",
        "      •      "
    }},
    {"Облачно", {
        "             ",
        "     .--.    ",
        "  .-(    ).  ",
        " (___.__)__) ",
        "             "
    }},
    {"Ясно", {
        "    \\   /    ",
        "     .-.      ",
        "  ― (   ) ―  ",
        "     `-’      ",
        "    /   \\    "
    }},
    {"Малооблачно", {
        "   \\  /      ",
        " _ /\"\".-.    ",
        "   \\_(   ).  ",
        "   /(___(__) ",
        "             "
    }},
    {"Пасмурно", {
        "             ",
        "     .--.    ",
        "  .-(    ).  ",
        " (___.__)__) ",
        "             "
    }},
    {"Легкий моросящий дождь", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "     ‘ ‘ ‘ ‘ ",
        "    ‘ ‘ ‘ ‘  "
    }},
    {"Средний моросящий дождь", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "     ‘ ‘ ‘ ‘ ",
        "    ‘ ‘ ‘ ‘  "
    }},
    {"Сильно моросящий дождь", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "   ‚‘‚‘‚‘‚‘  ",
        "   ‚’‚’‚’‚’  "
    }},

    {"Легкий дождь со снегом", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "    * * * *  ",
        "   * * * *   "
    }},
    {"Моросящий дождь со снегом", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "     ‘ * ‘ * ",
        "    * ‘ * ‘  "
    }},
    {"Дождь со снегом", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "    ‘ * ‘ *  ",
        "   * ‘ * ‘   "
    }},
    {"Легкий дождь", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "    ‘ ‘ ‘ ‘  ",
        "   ‘ ‘ ‘ ‘   "
    }},
    {"Дождь", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "    ‘ ‘ ‘ ‘  ",
        "   ‘ ‘ ‘ ‘   "
    }},
    {"Сильный дождь", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "  ‚‘‚‘‚‘‚‘   ",
        "  ‚’‚’‚’‚’   "
    }},
    {"Ливень", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "  ‚‘‚‘‚‘‚‘   ",
        "  ‚’‚’‚’‚’   "
    }},
    {"Небольшой ливень", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "  ‚‘‚‘‚‘‚‘   ",
        "  ‚’‚’‚’‚’   "
    }},
    {"Сильный ливень", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "  ‚‘‚‘‚‘‚‘   ",
        "  ‚’‚’‚’‚’   "
    }},
    {"Небольшой снег", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "    *  *  *  ",
        "   *  *  *   "
    }},
    {"Снег", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "   * * * *   ",
        "  * * * *    "
    }},
    {"Сильный снег", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "   * * * *   ",
        "  * * * *    "
    }},
    {"Снегопад", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "   * * * *   ",
        "  * * * *    "
    }},
    {"Сильный снегопад", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "   * * * *   ",
        "  * * * *    "
    }},
    {"Лёгкий снег", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "   * * * *   ",
        "  * * * *    "
    }},
    {"Гроза", {
        "     .-.     ",
        "    (   ).   ",
        "   (___(__)  ",
        "  ‚‘⚡‘‚⚡‚‘   ",
        "  ‚’‚’⚡’‚’   "
    }},
    {"Гроза с незначительным градом", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "     *⚡*⚡*   ",
        "    *  *  *  "
    }},
    {"Гроза с градом", {
        " _`/\"\".-.    ",
        "  ,\\_(   ).  ",
        "   /(___(__) ",
        "     *⚡*⚡*   ",
        "    *  *  *  "
    }},
    {"Туман", {
        "             ",
        " _ - _ - _ - ",
        "  _ - _ - _  ",
        " _ - _ - _ - ",
        "             "
    }},
    {"Изморозь", {
        "             ",
        " _ - _ - _ - ",
        "  _ - _ - _  ",
        " _ - _ - _ - ",
        "             "
    }}
};

std::string WiindDirection(int direction);
void Printer(CurrCity& curr_city);
CurrCity Next(CurrCity& curr_city);
CurrCity Prev(CurrCity& curr_city);
CurrCity Plus(CurrCity& curr_city);
CurrCity Minus(CurrCity& curr_city);

#endif //LABWORK7_1SUKHARIK__INTERFACE_H_
