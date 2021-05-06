#ifndef UTIL
#define UTIL

#include <iostream>
#include <string>
#include <regex>

namespace pedalconfig
{
  std::string get_body_by_head(std::string string, std::string key);

  std::string get_first_head_value(std::string string);

  std::string get_first_body_value(std::string string);

  std::string indent(std::string string);

  std::vector<std::string> get_vector_of_values_by_head(std::string string, std::string key);
}

#endif // !UTIL
