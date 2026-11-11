#include "include/Fleet.hpp"
#include "include/ServiceCenter.hpp"
#include "include/CmdReader.hpp"
#include "include/Errors.hpp"

int main() {
  ServiceCenter service_center("Broken");
  Fleet fleet(service_center);
  CmdReader cmd_reader(fleet);

  try {
    while (true) {
      try {
        cmd_reader.ReadCmd();
      } catch (const FleetOperationError& e) {
        std::cout << "error: " << e.what() << '\n'; 
      }
    }
  } catch (const Quit&) {
  }

  return 0;
}