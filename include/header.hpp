// Copyright 2018 Your Name <your_email>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <stdlib.h>
#include <any>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <streambuf>
#include <string>
#include <vector>

class Json {
 public:
  void add_element(const std::string& x, std::string key, size_t& i);
  void add_element_in_ar(const std::string& x, size_t& i);
  Json();
  explicit Json(const std::string& s);
  bool is_array() const;
  bool is_object() const;
  std::any& operator[](const std::string& key);
  std::any& operator[](int index);
  static Json parse(const std::string& s);
  static Json parseFile(const std::string& path_to_file);

 private:
  std::map<std::string, std::any> data;
  std::vector<std::any> ar;
};

#endif  // INCLUDE_HEADER_HPP_
