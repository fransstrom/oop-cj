#pragma once
#include "Player.h"
#include <iostream>

enum class EffectType { Slow = 1, Burn = 2, Heal = 3, Poison = 4 };

struct Effect {
  virtual ~Effect() = default; // M�ste ha virtuell destruktor i bas-klasser.
  virtual void
  apply(Player &player) = 0; // Ren virtuell funktion. "= 0" betyder att den
                             // m�ste implementeras i subklasser.
};

struct Slow : Effect {
  void apply(Player &player) override {
    std::cout << "Slowing " << player.getName() << "...\n";
    player.changeSpeed(-1); // S�nk spelarens hastighet med 10%
  }
};

struct Burn : Effect {
  void apply(Player &player) override {
    std::cout << "Burning " << player.getName() << "!\n";
    player.takeDamage(5); // G�r 5 skada
  }
};

struct Heal : Effect {
  void apply(Player &player) override{
    std::cout << "Healing "<< player.getName() << "!\n";
    player.heal(4);
  }
};

struct Poison : Effect {
  void apply(Player &player) override{
    std::cout << "Poisoning " << player.getName() << "!\n";
    for (int i = 0; i < 3; i++)
    player.poison(3);
    
  }
};
