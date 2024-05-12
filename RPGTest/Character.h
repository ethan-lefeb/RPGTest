#pragma once
#include <string>

class Character
{
public:

	std::string characterName;
	int characterStrength;
	int characterWeakness;
	int characterHealth;
	int characterMaxHealth = 100;
	int characterMana = 30;

	bool currentTurn;

	int recentDamage;
	int attackElement;

	int oncomingDamage;
	int oncomingElement;
	bool isGuarding = false;

	bool damageResistance;
	bool damageWeakness;

	void characterAttack(int attackType);

	void characterHeal();

	void characterGuard();

	void receiveDamage(int oncomingDamage, int oncomingElement);

	void enemyAttack(int attackType);

	void enemyHeal();

	void enemyGuard();
};

