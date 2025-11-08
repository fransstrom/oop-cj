// PlayerEffects.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <chrono>
#include <cstdlib> // f�r rand()
#include <iostream>
#include <memory> // f�r std::unique_ptr och std::make_unique
#include <thread> // f�r sleep_for som l�ter oss pausa exekveringen
#include <vector>

#include "Effect.h"

// RAII = Resource Acquisition Is Initialization. Inneb�r: Resurser (minne,
// filer etc) kopplas till ett objekts livstid. N�r anv�nda uniqe_ptr? Du vill
// �ga ett ett dynamiskt allokerat objekt Ingen annan ska dela p� det �garskapet
// du vill att objektet automatiskt frig�rs n�r det g�r ur scope

// Device* d = new Device(); // Dynamisk allokering. Undvik detta om m�jligt!
// d->tick();
// delete d;

// Vi vill anv�nda en "fabrik" f�r att skapa effekter baserat p� en kod (1 =
// Slow, 2 = Burn) Returnerar en unik pekare till en Effect. Anv�nder unique_ptr
// f�r att hantera minnet automatiskt.
std::unique_ptr<Effect> makeEffect(EffectType type) {
  switch (type) {
  case EffectType::Slow:
    return std::make_unique<Slow>();
  case EffectType::Burn:
    return std::make_unique<Burn>();
  case EffectType::Heal:
    return std::make_unique<Heal>();
  case EffectType::Poison:
    return std::make_unique<Poison>();
  default:
    return nullptr;
  }
}

int main() {
  // V�rt huvudprogram:
  // Vi b�rjar med att skapa och lagra n�gra effekter i en vektor.
  std::vector<std::unique_ptr<Effect>> effects;
  effects.push_back(makeEffect(EffectType::Slow));
  effects.push_back(makeEffect(EffectType::Burn));
  effects.push_back(makeEffect(EffectType::Heal));
  effects.push_back(makeEffect(EffectType::Poison));

  // Skapa en spelare
  Player player1(
      "Mister Hero"); // Vanligt objekt p� stacken. Player-objektet kommer att
                      // f�rst�ras automatiskt n�r det g�r ur scope, d.v.s. n�r
                      // vi l�mnar main-funktionen.
  Player player2("Villain"); // Vanligt objekt p� stacken. Player-objektet
                             // kommer att f�rst�ras automatiskt n�r det g�r ur
                             // scope, d.v.s. n�r vi l�mnar main-funktionen.

  // N�r vill vi anv�nda smarta pekare?
  // N�r vi vill lagra flera objekt i en container (vektor, lista etc)
  // auto playerPtr = std::make_unique<Player>("Mister Hero");

  std::cout << player1.getName() << " enters the chamber of doom with "
            << player1.getHealth() << " health and speed " << player1.getSpeed()
            << "...\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  std::cout << player2.getName() << " enters the chamber of doom with "
            << player2.getHealth() << " health and speed " << player2.getSpeed()
            << "...\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));

  // Applicera alla effekter p� spelaren
  for (const auto &effect : effects) {
    effect->apply(player1);
    effect->apply(player2);
  }

  // Genererar random effekter och applicerar dem tills spelaren �r d�d
  std::cout << "\nApplying random effects until player is defeated:\n";
  while (player1.getHealth() > 0 && player2.getHealth() > 0) {
    std::cout << player1.getName() << "s tur! V�lj handling:\n";
    std::cout << "1. Attack\n2. Effekt (Slow/Burn)\n> ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
      player2.takeDamage(10);
    } else if (choice == 2) {
      EffectType type = static_cast<EffectType>((rand()%4)+1);
      auto effect = makeEffect(type);
      effect->apply(player2);
    }
    std::swap(player1, player2); // byt tur
  }

  // N�r vi kommer hit, avslutas funktionen och vektorn g�r ur scope och alla
  // unika pekare frig�rs automatiskt.
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
