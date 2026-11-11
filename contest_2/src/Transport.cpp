#include "../include/Transport.hpp"

#include <iomanip>
#include <sstream>

#include "../include/Errors.hpp"
//  Transport

Transport::Transport(std::string id, std::string name, double difficulty_score)
    : InventoryItem(id, name), difficulty_score(difficulty_score) {
  if (difficulty_score > 10 || difficulty_score < 0) {
    throw InvalidArgument("invalid difficulty score ");
  }
}

bool Transport::isForNovice() const { return difficulty_score <= 5; }

double Transport::getScore() const { return difficulty_score; }

// Bike

Bike::Bike(std::string id, std::string name, double difficulty_score)
    : Transport(id, name, difficulty_score) {}

std::string Bike::getDescription() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1);

  oss << "Bike. id: " << id << ", name: " << name << ", difficulty_score: " << difficulty_score;

  return oss.str();
}

// EBike

EBike::EBike(std::string id, std::string name, double difficulty_score, double energy_consumption)
    : Bike(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double EBike::getEnergyConsumption() const { return energy_consumption; }

std::string EBike::getDescription() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1);

  oss << "EBike. id: " << id << ", name: " << name << ", difficulty_score: " << difficulty_score
      << ", energy_consumption: " << energy_consumption;

  return oss.str();
}

// Scooter

Scooter::Scooter(std::string id, std::string name, double difficulty_score,
                 double energy_consumption)
    : Transport(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double Scooter::getEnergyConsumption() const { return energy_consumption; }

std::string Scooter::getDescription() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(1);

  oss << "Scooter. id: " << id << ", name: " << name << ", difficulty_score: " << difficulty_score
      << ", energy_consumption: " << energy_consumption;

  return oss.str();
}