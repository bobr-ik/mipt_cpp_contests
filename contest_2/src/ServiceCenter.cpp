#include "../include/ServiceCenter.hpp"

#include "../include/Errors.hpp"

void ServiceCenter::inspect(const InventoryItem& item) {
  if (containsCaseInsensitive(item.getName(), banword)) {
    throw InspectionError("Item with name " + item.getName() + " and id " + item.getId() +
                          " is not valid");
  }
}