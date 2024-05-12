#include <iostream>
#include "Character.h" // Assuming Character.h is the header file for the Character class

int main() {
    Character playerCharacter;
    Character enemyCharacter;
    std::string playerName;
    int playerDifficulty;
    int playerElement;

    std::cout << "Hello, mighty warrior! What is your name? \n";
    std::cin >> playerName;
    playerCharacter.characterName = playerName;

    std::cout << "\nGreetings, " << playerCharacter.characterName << "! \n";
    std::cout << "\nAre you a steadfast knight of steel (0), does your heart burn with passion (1), are you cool as ice (2), do you flow like wind (3), or are you grounded (4)?\n";
    std::cin >> playerElement;

    if (playerElement == 0) {
        playerCharacter.characterStrength = 0;
        playerCharacter.characterWeakness = 5;
    }
    else if (playerElement == 1) {
        playerCharacter.characterStrength = 1;
        playerCharacter.characterWeakness = 2;
    }
    else if (playerElement == 2) {
        playerCharacter.characterStrength = 2;
        playerCharacter.characterWeakness = 1;
    }
    else if (playerElement == 3) {
        playerCharacter.characterStrength = 3;
        playerCharacter.characterWeakness = 4;
    }
    else if (playerElement == 4) {
        playerCharacter.characterStrength = 4;
        playerCharacter.characterWeakness = 3;
    }

    std::cout << "\nWould you like an easy game (1), the /recommended/ moderately difficult game (2), or a difficult game? (3) \n";
    std::cin >> playerDifficulty;

    if (playerDifficulty == 1) {
        playerCharacter.characterHealth = 100;
        enemyCharacter.characterHealth = 50;
        enemyCharacter.characterWeakness = 0;
        enemyCharacter.characterStrength = 5;
    }
    else if (playerDifficulty == 2) {
        playerCharacter.characterHealth = 75;
        enemyCharacter.characterHealth = 75;
        enemyCharacter.characterWeakness = 2;
        enemyCharacter.characterStrength = 1;
    }
    else if (playerDifficulty == 3) {
        playerCharacter.characterHealth = 50;
        enemyCharacter.characterHealth = 100;
        enemyCharacter.characterStrength = 0;
        enemyCharacter.characterWeakness = 5;
    }

    
    while (playerCharacter.characterHealth > 0 && enemyCharacter.characterHealth > 0) {
        if (playerCharacter.currentTurn) {
            int choice;

            std::cout << "\nYour health: " << playerCharacter.characterHealth;
            std::cout << "\nYour Mana: " << playerCharacter.characterMana;
            std::cout << "\nEnemy's Health: " << enemyCharacter.characterHealth;
            std::cout << "\nEnemy's Mana: " << enemyCharacter.characterMana;

            std::cout << "\n\n1. Attack\n2. Guard\n3. Heal\nEnter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                playerCharacter.characterAttack(playerCharacter.attackElement);
                enemyCharacter.receiveDamage(playerCharacter.recentDamage, playerCharacter.characterStrength);
                break;
            case 2:
                playerCharacter.characterGuard();
                break;
            case 3:
                playerCharacter.characterHeal();
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }

            playerCharacter.currentTurn = false;
        }
        else {
            // Enemy turn
            srand(static_cast<unsigned int>(time(0)));
            int enemyChoice = rand() % 5 + 1; // Random choice between 1, 2, and 3

            switch (enemyChoice) {
            case 1:
                std::cout << "The enemy attacks!" << std::endl;
                enemyCharacter.enemyAttack(enemyCharacter.attackElement);
                playerCharacter.receiveDamage(enemyCharacter.recentDamage, enemyCharacter.characterStrength);
                break;
            case 2:
                std::cout << "The enemy guards!" << std::endl;
                enemyCharacter.enemyGuard();
                break;
            case 3:
                std::cout << "The enemy heals!" << std::endl;
                enemyCharacter.enemyHeal();
                break;
            case 4:
                std::cout << "The enemy attacks!" << std::endl;
                enemyCharacter.enemyAttack(enemyCharacter.attackElement);
                playerCharacter.receiveDamage(enemyCharacter.recentDamage, enemyCharacter.characterStrength);
                break;
            case 5:
                std::cout << "The enemy attacks!" << std::endl;
                enemyCharacter.enemyAttack(enemyCharacter.attackElement);
                playerCharacter.receiveDamage(enemyCharacter.recentDamage, enemyCharacter.characterStrength);
                break;
            }

            playerCharacter.currentTurn = true;
        
        }
    }

    // Game over
    if (playerCharacter.characterHealth <= 0) {
        std::cout << "You have been defeated!" << std::endl;
    }
    else {
        std::cout << "Victory is yours!" << std::endl;
    }

    return 0;
}