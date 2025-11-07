// PlayerEffects.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <chrono>
#include <cstdlib> // för rand()
#include <iostream>
#include <memory> // för std::unique_ptr och std::make_unique
#include <thread> // för sleep_for som låter oss pausa exekveringen
#include <vector>

#include "Effect.h"

// RAII = Resource Acquisition Is Initialization. Innebär: Resurser (minne,
// filer etc) kopplas till ett objekts livstid. När använda uniqe_ptr? Du vill
// äga ett ett dynamiskt allokerat objekt Ingen annan ska dela på det ägarskapet
// du vill att objektet automatiskt frigörs när det går ur scope

// Device* d = new Device(); // Dynamisk allokering. Undvik detta om möjligt!
// d->tick();
// delete d;

// Vi vill använda en "fabrik" för att skapa effekter baserat på en kod (1 =
// Slow, 2 = Burn) Returnerar en unik pekare till en Effect. Använder unique_ptr
// för att hantera minnet automatiskt.
std::unique_ptr<Effect> makeEffect(EffectType type) {
  switch (type) {
  case EffectType::Slow:
    return std::make_unique<Slow>();
  case EffectType::Burn:
    return std::make_unique<Burn>();
  case EffectType::Heal:
    return std::make_unique<Heal>();
  default:
    return nullptr;
  }
}

int main() {
  // Vårt huvudprogram:
  // Vi börjar med att skapa och lagra några effekter i en vektor.
  std::vector<std::unique_ptr<Effect>> effects;
  effects.push_back(makeEffect(EffectType::Slow));
  effects.push_back(makeEffect(EffectType::Burn));

  // Skapa en spelare
  Player player1(
      "Mister Hero"); // Vanligt objekt på stacken. Player-objektet kommer att
                      // förstöras automatiskt när det går ur scope, d.v.s. när
                      // vi lämnar main-funktionen.
  Player player2("Villain"); // Vanligt objekt på stacken. Player-objektet
                             // kommer att förstöras automatiskt när det går ur
                             // scope, d.v.s. när vi lämnar main-funktionen.

  // När vill vi använda smarta pekare?
  // När vi vill lagra flera objekt i en container (vektor, lista etc)
  // auto playerPtr = std::make_unique<Player>("Mister Hero");

  std::cout << player1.getName() << " enters the chamber of doom with "
            << player1.getHealth() << " health and speed " << player1.getSpeed()
            << "...\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  std::cout << player2.getName() << " enters the chamber of doom with "
            << player2.getHealth() << " health and speed " << player2.getSpeed()
            << "...\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));

  // Applicera alla effekter på spelaren
  for (const auto &effect : effects) {
    effect->apply(player1);
    effect->apply(player2);
  }

  // Genererar random effekter och applicerar dem tills spelaren är död
  std::cout << "\nApplying random effects until player is defeated:\n";
  while (player1.getHealth() > 0 && player2.getHealth() > 0) {
    std::cout << player1.getName() << "s tur! Välj handling:\n";
    std::cout << "1. Attack\n2. Effekt (Slow/Burn)\n> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
      player2.takeDamage(10);
    } else if (choice == 2) {
      EffectType type = static_cast<EffectType>((rand()%3)+1);
      auto effect = makeEffect(type);
      effect->apply(player2);
    }
    std::swap(player1, player2); // byt tur
  }

  // När vi kommer hit, avslutas funktionen och vektorn går ur scope och alla
  // unika pekare frigörs automatiskt.
  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
