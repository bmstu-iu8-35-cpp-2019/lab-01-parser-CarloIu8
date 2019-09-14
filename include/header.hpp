// Copyright 2018 Your Name <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <stdlib.h>
#include <any>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string copy_figure_skobka(const std::string& s, size_t& index) {
  std::string x;
  size_t k = 1;
  x += s[index];
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
  x += s[index];
  index++;
  return x;
}

std::string copy_chislo(const std::string& s, size_t& index, bool& dble) {
  dble = false;
  std::string x;
  if (s[0] == '.') throw std::exception();
  int flag = 0;
  while ((s[index] > 47 && s[index] < 58) || s[index] == '.') {
    if (s[0] == '.') {
      flag++;
    }
    x += s[index];
    index++;
  }
  if (flag == 1) {
    dble = true;
  }
  if (flag > 1) {
    throw std::exception();
  }
  return x;
}

std::string copy_kavichki(const std::string& s, size_t& index) {
  std::string x;
  size_t k = 1;
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
  x += s[index];
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
  x += s[index];
  index++;
  return x;
}

std::string read_from_file(const string& path) {
  std::string str;
  std::string line;
  std::ifstream fin(path);
  if (fin.is_open()) {
    while (getline(fin, line)) {
      str += line;
    }
  }
  fin.close();
  std::string m;
  size_t i = 0;
  while (i < str.length()) {
    if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') m += str[i] i++;
  }
  return str;
}

class Json {
 public:
  Json() = default;
  explicit Json(const std::string& s) {
    std::string str;
    size_t k = 0;
    while (k < s.length()) {
      if (s[k] == ' ' || s[k] == '\t' || s[k] == '\n') {
        k++;
      } else {
        str += s[k];
        k++;
      }
    }
    if (str[0] != '{' && str[0] != '[') throw std::exception();
    if (str[0] == '{') {
      size_t m = 0;
      size_t i = 0;
      i++;
      std::string key;
      std::string x;
      x = str;
      while (i < x.length()) {
        if (x[i] != '\"') {
          throw std::exception();
        } else {
          key = copy_kavichki(x, i);
          if (x[i] != ':') {
            throw std::exception();
          } else {
            i++;
            if (x[i] == '\"') {
              std::string info;
              info = copy_kavichki(x, i);
              data.emplace(key, info);
            }
            if (x[i] == 't') {
              data.emplace(key, true);
              i += 4;
            }
            if (x[i] == 'f') {
              data.emplace(key, false);
              i += 5;
            }
            if (x[i] > 47 && x[i] < 58) {
              std::string info;
              bool flag;
              info = copy_chislo(x, i, flag);
              if (flag) {
                double a;
                a = stof(info);
                data.emplace(key, a);
              } else {
                int a;
                a = stoi(info);
                data.emplace(key, a);
              }
            }
            if (x[i] == '{') {
              std::string m;
              m = copy_figure_skobka(x, i);
              data.emplace(key, Json(m));
            }
            if (x[i] == '[') {
              std::string m;
              m = copy_kvadrat_skobka(x, i);
              data.emplace(key, Json(m));
            }

            if (str[i] != ',' && str[i] != '}' && str[i] != ']' &&
                i != str.length()) {
              throw std::exception();
            } else {
              i++;
              key = "";
              continue;
            }
          }
        }
      }
    }
    if (str[0] == '[') {
      std::string x = s;
      size_t i = 1;
      x = str;
      while (i < x.length()) {
        if (x[i] == '\"') {
          std::string info;
          info = copy_kavichki(x, i);
        }
        if (x[i] == 't') {
          i += 4;
          ar.push_back(true);
        }
        if (x[i] == 'f') {
          ar.push_back(false);
          i += 5;
        }
        if (x[i] > 47 && x[i] < 58) {
          std::string info;
          bool flag;
          info = copy_chislo(x, i, flag);
          if (flag) {
            double a;
            a = stof(info);
            ar.push_back(a);
          } else {
            int a;
            a = stoi(info);
            ar.push_back(a);
          }
          if (x[i] == '{') {
            std::string m;
            m = copy_figure_skobka(x, i);
            ar.push_back(Json(m));
          }
          if (x[i] == '[') {
            std::string m;
            m = copy_kvadrat_skobka(x, i);
            ar.push_back(Json(x));
          }
          if (str[i] != ',' && str[i] != '}' && str[i] != ']' &&
              i != str.length()) {
            throw std::exception();
          } else {
            i++;
            continue;
          }
        }
      }
    }
  }
  bool is_array() const { return ar.size(); }

  bool is_object() const { return data.size(); }

  std::any& operator[](const std::string& key) { return data[key]; }

  std::any& operator[](int index) { return ar[index]; }
  static Json parse(const std::string& s) { return Json(s); }
  static Json parseFile(const std::string& path_to_file) {
    s = read_from_file(path_to_file);
    return Json(s)
  }

 private:
  std::map<std::string, std::any> data;
  std::vector<std::any> ar;
};

#endif  // INCLUDE_HEADER_HPP_
