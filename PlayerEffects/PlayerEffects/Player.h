#pragma once
#include <string>

class Player
{
public:
	Player(const std::string& n, int h, int s); // Konstruktor
	Player(const std::string& n); // �verlagrad konstruktor, n�r vi bara vill ange namn f�r ny spelare
	~Player() = default; // Standarddestruktor. Beh�vs bara om vi anv�nder r�a pekare i klassen, d.v.s. allokerar minne dynamiskt.

	const std::string& getName() const;
	int getHealth() const;
	int getSpeed() const;

	void takeDamage(int dmg);
	void heal(int hp);
	void changeSpeed(int delta);
	void poison(int dmg);
	void status(int dmg);
	

private:
	std::string name;
	int health;
	int speed;

	bool isPoisoned = false;
	int poisonTurns = 0;
	int poisonDamage = 0;
};


