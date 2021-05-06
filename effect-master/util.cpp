#include "util.h"

std::string pedalconfig::get_body_by_head(std::string string, std::string key)
{
  std::regex regex("(^|\\r?\\n)" + key + "(\\r?\\n( {2})+\\S+)*");
  std::smatch match;
  std::regex_search(string, match, regex);
  std::string body = match.str();

  std::regex replace_begin_regex("^\\r?\\n");
  body = std::regex_replace(body, replace_begin_regex, "");

  std::regex replace_name_regex("^\\S+\\r?\\n?");
  std::regex replace_spaces_regex("(^|\\r?\\n) {2}");
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
  std::regex replace_head_regex("^\\S+\\r?\\n?");
  std::regex replace_indent_regex("(^|\\r?\\n) {2}");
  std::regex replace_starting_newline_regex("^\\r?\\n");
  std::string string_without_head = std::regex_replace(string, replace_head_regex, "");
  std::string string_without_head_and_indent = std::regex_replace(string_without_head, replace_indent_regex, "\n");
  std::string string_without_head_and_indent_and_starting_newline = std::regex_replace(string_without_head_and_indent, replace_starting_newline_regex, "");

  return string_without_head_and_indent_and_starting_newline;
}

std::string pedalconfig::indent(std::string string)
{
  std::regex regex("^|\\r?\\n  ");
  std::string return_string = std::regex_replace(string, regex, "  ");
  return return_string;
}

std::vector<std::string> pedalconfig::get_vector_of_values_by_head(std::string string, std::string key)
{

  std::regex regex("(?!\\r?\\n)" + key + "(\\r?\\n( {2})+\\S+)*");
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
