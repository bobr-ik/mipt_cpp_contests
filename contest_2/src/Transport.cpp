#include "../include/Transport.hpp"

//  Transport

Transport::Transport(std::string id, std::string name, double difficulty_score)
    : InventoryItem(id, name), difficulty_score(difficulty_score) {}

bool Transport::isForNovice() const { return difficulty_score <= 5; }

double Transport::getScore() const { return difficulty_score; }

// Bike

Bike::Bike(std::string id, std::string name, double difficulty_score)
    : Transport(id, name, difficulty_score) {}

std::string Bike::getDescription() const {
  
  std::string s_difficulty_score = std::to_string(difficulty_score);
  s_difficulty_score = s_difficulty_score.substr(0, s_difficulty_score.find('.') + 2);
  return "Bike. id: " + id + ", name: " + name +
         ", difficulty_score: " + s_difficulty_score;
}

// EBike

EBike::EBike(std::string id, std::string name, double difficulty_score, double energy_consumption)
    : Bike(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double EBike::getEnergyConsumption() const { return energy_consumption; }

std::string EBike::getDescription() const {
  
  std::string s_energy_consumption = std::to_string(energy_consumption);
  s_energy_consumption = s_energy_consumption.substr(0, s_energy_consumption.find('.') + 2);

  
  std::string s_difficulty_score = std::to_string(difficulty_score);
  s_difficulty_score = s_difficulty_score.substr(0, s_difficulty_score.find('.') + 2);

  return "EBike. id: " + id + ", name: " + name +
         ", difficulty_score: " + s_difficulty_score +
         ", energy_consumption: " + s_energy_consumption;
}

// Scooter

Scooter::Scooter(std::string id, std::string name, double difficulty_score,
                 double energy_consumption)
    : Transport(id, name, difficulty_score), EnergyConsumer(energy_consumption) {}

double Scooter::getEnergyConsumption() const { return energy_consumption; }

std::string Scooter::getDescription() const {
  std::string s_energy_consumption = std::to_string(energy_consumption);
  s_energy_consumption = s_energy_consumption.substr(0, s_energy_consumption.find('.') + 2);

  
  std::string s_difficulty_score = std::to_string(difficulty_score);
  s_difficulty_score = s_difficulty_score.substr(0, s_difficulty_score.find('.') + 2);

  return "Scooter. id: " + id + ", name: " + name +
         ", difficulty_score: " + s_difficulty_score +
         ", energy_consumption: " + s_energy_consumption;
}