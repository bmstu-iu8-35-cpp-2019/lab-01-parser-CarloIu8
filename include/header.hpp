// Copyright 2018 Your Name <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <stdlib.h>
#include <any>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string copy_figure_skobka(
    const std::string& s,
    size_t& index)  //Копирование куска строки от символа с номером index до
                    //такого-же закрывающего символа
{
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

std::string copy_chislo(
    const std::string& s,
    size_t& index)  //Копирование куска строки от символа с номером index до
                    //такого-же закрывающего символа
{
  std::string x;
  size_t k = 1;
  while (s[index] > 47 && s[index] < 58) {
    x += s[index];
    index++;
  }
  return x;
}

std::string copy_kavichki(
    const std::string& s,
    size_t& index)  //Копирование куска строки от символа с номером index до
                    //такого-же закрывающего символа
{
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

std::string copy_kvadrat_skobka(
    const std::string& s,
    size_t& index)  //Копирование куска строки от символа с номером index до
                    //такого-же закрывающего символа
{
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
  // Конструктор из строки, содержащей Json-данные.
  Json(const std::string& s) {
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
  // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив.
  // Иначе false.
  bool is_array() const { return ar.size(); }
  // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект.
  // Иначе false.
  bool is_object() const { return data.size(); }

  // Метод возвращает значение по ключу key, если экземпляр является
  // JSON-объектом. Значение может иметь один из следующих типов: Json,
  // std::string, double, bool или быть пустым. Если экземпляр является
  // JSON-массивом, генерируется исключение.
  std::any& operator[](const std::string& key) { return data[key]; }

  // Метод возвращает значение по индексу index, если экземпляр является
  // JSON-массивом. Значение может иметь один из следующих типов: Json,
  // std::string, double, bool или быть пустым. Если экземпляр является
  // JSON-объектом, генерируется исключение.
  std::any& operator[](int index) { return ar[index]; }
  // Метод возвращает объект класса Json из строки, содержащей Json-данные.
  static Json parse(const std::string& s) { return Json(s); }

  // Метод возвращает объекта класса Json из файла, содержащего Json-данные в
  // текстовом формате.
  // static Json parseFile(const std::string& path_to_file);
 private:
  std::map<std::string, std::any> data;
  std::vector<std::any> ar;
};
#endif  // INCLUDE_HEADER_HPP_
