#include "hamming_coding.h"

std::string CheckBlock(std::string& a) {
  int n = a.size();
  int wrong = 0;
  for (int i = 1; i < a.size(); i *= 2) {

    int count = 0;
    for (int j = i - 1; j < n; j += 2 * i) {
      for (int k = j; k < j + i && k < n; k++) {
        if (k > (i - 1) && a[k] == '1') {
          count ^= 1;
        }
      }
    }
    if (!((count == 1 && a[i - 1] == '1') || (count == 0 && a[i - 1] == '0'))) {
      wrong += i;
    }
  }
  if (wrong > n) {
    std::cout << "I CANT FIX MISTAKE";
    return "";
  }
  if (wrong > 0) {
    if (a[wrong - 1] == '0') {
      a[wrong - 1] = '1';
    } else {
      a[wrong - 1] = '0';
    }
  }
  std::string final;
  for (int j = 1; j <= a.size(); j *= 2) {
    a[j - 1] = '-';
  }
  for (int j = 0; j < a.size(); j++) {
    if (a[j] != '-') {
      final.push_back(a[j]);
    }
  }
  return final;

}

std::string CheckHamming(std::string& a, int size_of_block) {

  std::string ans;
  int i = 0;
  while (i < a.size()) {
    std::string block;
    int couner = 0;
    int start_block = 0;

    int index = 1;
    while (couner < size_of_block && i < a.size()) {
      block.push_back(a[i]);
      if ((index - 1) != start_block) {
        couner++;
      } else {
        index *= 2;
      }
      i++;
      start_block++;
    }
    ans += CheckBlock(block);

  }

  return ans;

}

std::string SetBits(std::string& a) {
  int n = a.size();
  int m = 2;
  std::string final;

  while (pow(2, m) <= n + m + 1) {
    if (pow(2, m) < n + m + 1) {
      m++;
    } else {
      break;
    }
  }
  int curr_ch_bit = 1;
  int curr_bit = 0;
  for (int i = 0; i < (n + m); i++) {
    if (i != (curr_ch_bit - 1)) {
      final.push_back(a[curr_bit]);
      curr_bit++;
    } else {
      curr_ch_bit *= 2;
      final.push_back('-');
    }
  }

  for (int i = 1; i < final.size(); i *= 2) {
    int count = 0;
    for (int j = i - 1; j < final.size(); j += 2 * i) {
      for (int k = j; k < j + i && k < final.size(); k++) {
        if (k > (i - 1) && final[k] == '1') {
          count ^= 1;
        }
      }
    }
    if (count == 1) {
      final[i - 1] = '1';
    } else {
      final[i - 1] = '0';
    }
  }
  return final;
}

std::string MakeHamming(std::string& a, int size_of_block) {
  std::string ans;
  for (int i = 0; i < a.size(); i += size_of_block) {
    std::string block;
    for (int j = i; j < (i + size_of_block) && j < a.size(); j++) {
      block.push_back(a[j]);
    }
    ans += SetBits(block);
  }
  return ans;

}
