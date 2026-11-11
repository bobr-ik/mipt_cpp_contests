#include "../include/CmdReader.hpp"

#include <iostream>
#include <string>

#include "../include/Errors.hpp"
#include "../include/Things.hpp"
#include "../include/Transport.hpp"

CmdReader::CmdReader(Fleet& fleet) : fleet(fleet) {
  commands["list"] = [this]() { this->fleet.printList(); };

  commands["focus"] = [this]() {
    std::string id;
    std::cin >> id;
    this->fleet.focus(id);
  };

  commands["show_focus"] = [this]() {
    auto item = this->fleet.getFocusItem();

    if (auto ptr = item.lock()) {
      std::cout << *ptr << '\n';
    } else {
      std::cout << "Expired\n";
    }
  };

  commands["quit"] = []() { throw Quit("quit"); };

  commands["novice"] = [this]() { this->fleet.printNovice(); };

  commands["log"] = [this]() { this->fleet.printLog(); };

  commands["recent"] = [this]() { this->fleet.printRecent(); };

  commands["remove"] = [this]() {
    std::string id;
    std::cin >> id;
    this->fleet.remove(id);
  };

  commands["energy"] = [this]() { std::cout << this->fleet.getEnergy() << '\n'; };

  commands["add"] = [this]() {
    std::string type;
    std::cin >> type;

    std::string id;
    std::string name;
    double difficulty_score;
    double energy_consumption;

    if (type == "bike") {
      std::cin >> id >> name >> difficulty_score;
      this->fleet.addItem(std::make_unique<Bike>(id, name, difficulty_score));

    } else if (type == "ebike") {
      std::cin >> id >> name >> energy_consumption >> difficulty_score;
      this->fleet.addItem(std::make_unique<EBike>(id, name, difficulty_score, energy_consumption));

    } else if (type == "scooter") {
      std::cin >> id >> name >> energy_consumption >> difficulty_score;
      this->fleet.addItem(
          std::make_unique<Scooter>(id, name, difficulty_score, energy_consumption));

    } else if (type == "helmet") {
      std::cin >> id >> name;
      this->fleet.addItem(std::make_unique<Helmet>(id, name));

    } else if (type == "dockstation") {
      std::cin >> id >> name >> energy_consumption;
      this->fleet.addItem(std::make_unique<DockStation>(id, name, energy_consumption));

    } else {
      throw InvalidArgument(type);
    }
  };
}

void CmdReader::ReadCmd() {
  std::string cmd;

  if (!(std::cin >> cmd)) {
    throw Quit("terminated");
  }

  auto it = commands.find(cmd);

  if (it == commands.end()) {
    throw InvalidOperation(cmd);
  }

  it->second();
}
