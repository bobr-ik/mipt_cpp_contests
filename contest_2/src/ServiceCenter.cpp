#include <string>
#include <algorithm>
#include <cctype>
#include "../include/ServiceCenter.hpp"

#include "../include/Errors.hpp"

ServiceCenter::ServiceCenter(std::string banword) : banword(banword) {}


bool ServiceCenter::containsCaseInsensitive(const std::string& str, const std::string& substr) {
    auto it = std::search(
        str.begin(), str.end(),
        substr.begin(), substr.end(),
        [](char ch1, char ch2) { 
            return std::tolower(ch1) == std::tolower(ch2); 
        }
    );
    return it != str.end();
}

void ServiceCenter::inspect(const InventoryItem& item) {
  if (containsCaseInsensitive(item.getName(), banword)) {
    throw InspectionError("Item with name " + item.getName() + " and id " + item.getId() +
                          " is not valid");
  }
}