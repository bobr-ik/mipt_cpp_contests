#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "Errors.hpp"
#include "Fleet.hpp"

class CmdReader {
 private:
  Fleet& fleet;
  std::unordered_map<std::string, std::function<void()>> commands;

  template <typename... Args>
  void readArgs(Args&... args) {
    if (!(std::cin >> ... >> args)) {
      throw InvalidArgument("Invalid or missing arguments");
    }
  }

 public:
  CmdReader(Fleet& fleet);

  void ReadCmd();
};