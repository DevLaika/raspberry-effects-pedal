#include <string>
#include <regex>
#include <iostream>

namespace pedalconfig
{
  std::string get_value_by_key(std::string string, std::string key)
  {
    std::regex regex("(^|\\n)" + key + "(\n( {2})+\\S+)*");
    std::smatch match;
    std::regex_search(string, match, regex);
    std::string value = match.str();

    std::regex replace_begin_regex("^\\n");
    value = std::regex_replace(value, replace_begin_regex, "");

    std::regex replace_name_regex("^\\S+\\n?");
    std::regex replace_spaces_regex("(^|\\n) {2}");
    value = std::regex_replace(value, replace_name_regex, "");
    value = std::regex_replace(value, replace_spaces_regex, "\n");
    value = std::regex_replace(value, replace_begin_regex, "");

    return value;
  }

  std::string get_first_head_value(std::string string)
  {
    std::smatch match;
    std::regex regex("^\\S+");
    std::regex_search(string, match, regex);
    std::string head = match.str();

    return head;
  }

  std::string get_first_body_value(std::string string)
  {
    std::regex replace_name_regex("^\\S+\\n?");
    std::regex replace_spaces_regex("(^|\\n) {2}");
    std::regex replace_begin_regex("^\\n");
    string = std::regex_replace(string, replace_name_regex, "");
    string = std::regex_replace(string, replace_spaces_regex, "\n");
    string = std::regex_replace(string, replace_begin_regex, "");

    return string;
  }
}
