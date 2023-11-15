#pragma once 

#include <stdexcept>
#include <string>
#include <unordered_map>

namespace program_options
{
  void parse(int, char*[]);
  int get_num(std::string);
  bool has_arg(std::string);
  int get_arg(std::string);
}
