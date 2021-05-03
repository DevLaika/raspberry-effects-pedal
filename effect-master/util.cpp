#include "util.h"

std::string pedalconfig::get_body_by_head(std::string string, std::string key)
{
  std::regex regex("(^|\\n)" + key + "(\n( {2})+\\S+)*");
  std::smatch match;
  std::regex_search(string, match, regex);
  std::string body = match.str();

  std::regex replace_begin_regex("^\\n");
  body = std::regex_replace(body, replace_begin_regex, "");

  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  body = std::regex_replace(body, replace_name_regex, "");
  body = std::regex_replace(body, replace_spaces_regex, "\n");
  body = std::regex_replace(body, replace_begin_regex, "");

  return body;
}

std::string pedalconfig::get_first_head_value(std::string string)
{
  std::smatch match;
  std::regex regex("^\\S+");
  std::regex_search(string, match, regex);
  std::string head = match.str();

  return head;
}

std::string pedalconfig::get_first_body_value(std::string string)
{
  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  std::regex replace_begin_regex("^\\n");
  string = std::regex_replace(string, replace_name_regex, "");
  string = std::regex_replace(string, replace_spaces_regex, "\n");
  string = std::regex_replace(string, replace_begin_regex, "");

  return string;
}

std::vector<std::string> pedalconfig::get_vector_of_values_by_head(std::string string, std::string key)
{

  std::regex regex("(?!\\n)" + key + "(\n( {2})+\\S+)*");
  std::sregex_iterator it(string.begin(), string.end(), regex);
  std::sregex_iterator end;
  std::vector<std::string> strings;
  while (it != end)
  {
    strings.push_back(it->str());
    it++;
  }
  return strings;
}