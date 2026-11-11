#include <functional>
#include <string>
#include <unordered_map>

#include "Fleet.hpp"

class CmdReader {
 private:
  Fleet& fleet;
  std::unordered_map<std::string, std::function<void()>> commands;

 public:
  CmdReader(Fleet& fleet);

  void ReadCmd();
};