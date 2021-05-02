#ifndef UTIL
#define UTIL

#include <string>
#include <regex>
#include <iostream>

namespace pedalconfig
{
  std::string get_body_by_head(std::string string, std::string key);

  std::string get_first_head_value(std::string string);

  std::string get_first_body_value(std::string string);
}

#endif // !UTIL