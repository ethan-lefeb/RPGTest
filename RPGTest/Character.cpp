#include "Character.h"
#include <time.h>
#include <iostream>
#include <cctype> // for std::tolower

const int HEAL_AMOUNT = 10;
const int MANA_COST_HEAL = 5;
const int MANA_GAIN_GUARD = 5;

bool getUserInput(const std::string& message) {
    char choice;
    std::cout << message << " (y/n): ";
    std::cin >> choice;
    return std::tolower(choice) == 'y';
}

void printMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void Character::enemyAttack(int attackType) {
    attackType = attackElement;
    srand(static_cast<unsigned int>(time(0)));
    recentDamage = rand() % 40; 
}

void Character::enemyHeal() {
    if (characterMana >= MANA_COST_HEAL) {
        characterMana -= MANA_COST_HEAL;
        characterHealth += HEAL_AMOUNT;
        if (characterHealth > characterMaxHealth) {
            characterHealth = characterMaxHealth;
        }
    }
}

void Character::enemyGuard() {
    isGuarding = true;
    characterMana += MANA_GAIN_GUARD;
}

void Character::characterAttack(int attackType) {
    if (getUserInput("Would you like to strike your opponent?")) {
        attackType = attackElement;
        srand(time(NULL));
        recentDamage = rand() % 10;
        currentTurn = false;
    }
    else {
        printMessage("Very well. Refunding your turn.");
        currentTurn = true;
    }
}

void Character::characterHeal() {
    if (getUserInput("Would you like to heal? It will take " + std::to_string(MANA_COST_HEAL) + " mana!")) {
        if (characterMana >= MANA_COST_HEAL) {
            characterMana -= MANA_COST_HEAL;
            characterHealth += HEAL_AMOUNT;
            if (characterHealth > characterMaxHealth) {
                characterHealth = characterMaxHealth;
                printMessage("You've reached your max health!");
            }
            currentTurn = false;
        }
        else {
            printMessage("You don't have enough mana! You fumbled your words, and wasted a turn.");
            currentTurn = false;
        }
    }
    else {
        printMessage("Very well. Refunding your turn.");
        currentTurn = true;
    }
}

void Character::characterGuard() {
    if (getUserInput("Would you like to guard? You will recover " + std::to_string(MANA_GAIN_GUARD) + " mana!")) {
        isGuarding = true;
        characterMana += MANA_GAIN_GUARD;
        currentTurn = false;
    }
    else {
        printMessage("Very well. Refunding your turn.");
        currentTurn = true;
    }
}

void Character::receiveDamage(int oncomingDamage, int oncomingElement) {
    int finalDamage = oncomingDamage;

    // Check for weakness or resistance
    if (oncomingElement == characterWeakness) {
        finalDamage = static_cast<int>(finalDamage * 1.25);  // Increase damage by 25%
        damageWeakness = true;
        damageResistance = false;
    }
    else if (oncomingElement == characterStrength) {
        finalDamage = static_cast<int>(finalDamage * 0.75);  // Decrease damage by 25%
        damageWeakness = false;
        damageResistance = true;
    }
    else {
        damageWeakness = false;
        damageResistance = false;
    }

    // Apply guard mechanic
    if (isGuarding) {
        finalDamage /= 2;  // Reduce damage by half if guarding
    }

    characterHealth -= finalDamage;

    // Handle cases where character health goes below 0 or above max health
    if (characterHealth < 0) {
        characterHealth = 0;
    }
    else if (characterHealth > characterMaxHealth) {
        characterHealth = characterMaxHealth;
    }
}