// Copyright 2018 Your Name <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <stdlib.h>
#include <any>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string copy_figure_skobka(const std::string& s, size_t& index) {
  std::string x;
  size_t k = 1;
  index++;
  bool flag = true;
  while (flag) {
    x += s[index];
    index++;
    if (s[index] == '{') {
      k++;
    }
    if (s[index] == '}') {
      k--;
      if (k == 0) flag = false;
    }
  }
  index++;
  return x;
}

std::string copy_chislo(const std::string& s, size_t& index) {
  std::string x;
  while (s[index] > 47 && s[index] < 58) {
    x += s[index];
    index++;
  }
  return x;
}

std::string copy_kavichki(const std::string& s, size_t& index) {
  std::string x;
  index++;
  bool flag = true;
  while (flag) {
    x += s[index];
    index++;
    if (s[index] == '\"') {
      flag = false;
    }
  }
  index++;
  return x;
}

std::string copy_kvadrat_skobka(const std::string& s, size_t& index) {
  std::string x;
  size_t k = 1;
  index++;
  bool flag = true;
  while (flag) {
    x += s[index];
    index++;
    if (s[index] == '[') {
      k++;
    }
    if (s[index] == ']') {
      k--;
      if (k == 0) flag = false;
    }
  }
  index++;
  return x;
}

class Json {
 public:
  Json() = default;

  Json object(const std::string& s) {
    std::string x;
    std::string info;
    std::string key;
    size_t i = 0;
    Json a;
    while (i < s.length()) {
      if (s[i] == '\"') {
        if (key == "") {
          key = copy_kavichki(s, i);
          i++;
          if (s[i] == '\"') {
            info = copy_kavichki(s, i);
            a.data.emplace(key, info);
          }
          if (s[i] == 't') {
            a.data.emplace(key, true);
          }
          if (s[i] == 'f') {
            a.data.emplace(key, false);
          }
          if (s[i] > 47 && s[i] < 58) {
            int n = 0;
            info = copy_chislo(s, i);
            n = stoi(info);
            a.data.emplace(key, n);
          }
          if (s[i] == '{') {
            x = copy_figure_skobka(s, i);
            a.data.emplace(key, object(x));
          }
          if (s[i] == '[') {
            x = copy_kvadrat_skobka(s, i);
            a.data.emplace(key, mass(x));
          }
          key = "";
        }
      }
      i++;
    }
    return a;
  }

  Json mass(const std::string& s) {
    std::string x;
    std::string info;
    size_t i = 0;
    Json a;
    std::vector<std::any> arr;
    while (i < s.length()) {
      if (s[i] == '\"') {
        info = copy_kavichki(s, i);
        a.ar.push_back(info);
      }
      if (s[i] == 't') {
        i += 4;
        a.ar.push_back(true);
      }
      if (s[i] == 'f') {
        a.ar.push_back(false);
        i += 5;
      }
      if (s[i] > 47 && s[i] < 58) {
        int n = 0;
        info = copy_chislo(s, i);
        n = stoi(info);
        a.ar.push_back(n);
      }
      if (s[i] == '{') {
        x = copy_figure_skobka(s, i);
        a.ar.push_back(object(x));
      }
      if (s[i] == '[') {
        x = copy_kvadrat_skobka(s, i);
        a.ar.push_back(mass(x));
      }
      i++;
    }
    return a;
  }
  explicit Json(const std::string& s) {
    if (s[0] == '{') {
      std::string x;
      std::string info;
      std::string key;
      size_t i = 0;
      Json a;
      while (i < s.length()) {
        if (s[i] == '\"') {
          if (key == "") {
            key = copy_kavichki(s, i);
            i++;
            if (s[i] == '\"') {
              info = copy_kavichki(s, i);
              data.emplace(key, info);
            }
            if (s[i] == 't') {
              data.emplace(key, true);
            }
            if (s[i] == 'f') {
              data.emplace(key, false);
            }
            if (s[i] > 47 && s[i] < 58) {
              int n = 0;
              info = copy_chislo(s, i);
              n = stoi(info);
              data.emplace(key, n);
            }
            if (s[i] == '{') {
              x = copy_figure_skobka(s, i);
              data.emplace(key, object(x));
            }
            if (s[i] == '[') {
              x = copy_kvadrat_skobka(s, i);

              data.emplace(key, mass(x));
            }
            key = "";
          }
        }
        i++;
      }
    }
    if (s[0] == '[') {
      std::string x;
      std::string info;
      size_t i = 1;
      Json a;
      std::vector<std::any> arr;
      while (i < s.length()) {
        if (s[i] == '\"') {
          info = copy_kavichki(s, i);
          ar.push_back(info);
        }
        if (s[i] == 't') {
          i += 4;
          ar.push_back(true);
        }
        if (s[i] == 'f') {
          ar.push_back(false);
          i += 5;
        }
        if (s[i] > 47 && s[i] < 58) {
          int n = 0;
          info = copy_chislo(s, i);
          n = stoi(info);
          ar.push_back(n);
        }
        if (s[i] == '{') {
          x = copy_figure_skobka(s, i);
          ar.push_back(object(x));
        }
        if (s[i] == '[') {
          x = copy_kvadrat_skobka(s, i);
          ar.push_back(mass(x));
        }
        i++;
      }
    }
  }

  /*void vivod() const
  {
          for (size_t i = 0; i < ar.size(); i++)
          {
                  std::cout << any_cast<int>(ar[i]);
          }
  }*/

  bool is_array() const { return ar.size(); }

  bool is_object() const { return data.size(); }

  std::any& operator[](const std::string& key) { return data[key]; }

  std::any& operator[](int index) { return ar[index]; }

  static Json parse(const std::string& s) { return Json(s); }

 private:
  std::map<std::string, std::any> data;
  std::vector<std::any> ar;
};
#endif  // INCLUDE_HEADER_HPP_
