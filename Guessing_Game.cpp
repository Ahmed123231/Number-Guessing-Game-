/**
 * Author : Ahmed Atef Eid Eid 
 * Date   : 30-9-2024
 * Title  : Number Guessing Game Guessing_Game.cpp File
 */



#include <iostream>
#include <chrono>
#include <random>
#include "Guessing_Game.h"

/**
 * @brief Prints the welcome message for the game.
 * 
 * This function displays a message introducing the player to the 
 * guessing game and providing the range of the target number.
 */
void PrintWelcomeMessage(void) {
    /* Print game introduction */
    std::cout << "----------------------------------\n";
    std::cout << "Welcome To Number Guessing Game !!\n";
    std::cout << "Try to guess the number between 1 and 100.\n";
    std::cout << "----------------------------------\n";
}

/**
 * @brief Prompts the user to enter a valid guess between 1 and 100.
 * 
 * This function will continue to prompt the user until a valid number 
 * is entered. It checks for invalid input and ensures the guess is 
 * within the range.
 * 
 * @return unsigned char The valid number entered by the user.
 */
unsigned char GetNumberFromUser(void) {
    unsigned int EnteredNum = 0U; /* Variable to store user's guess */

    /* Infinite loop to continuously prompt user for valid input */
    while (true) {
        std::cout << "Enter Your Guess (1 to 100): ";
        std::cin >> EnteredNum; /* Take user input */

        /**
         * @brief Checks for valid input and ensures it is within the range.
         * If input is invalid, the function clears the error state and 
         * prompts the user to try again.
         */
        if (std::cin.fail() || (EnteredNum < 1U) || (EnteredNum > 100U)) {
            std::cin.clear();  /* Clear the error state of the stream */
            std::cin.ignore(10000U, '\n');  /* Ignore invalid input until '\n' */
            std::cout << "Invalid input! Please enter a number between 1 and 100.\n";
        } else {
            /* Return valid number cast to unsigned char */
            return static_cast<unsigned char>(EnteredNum); 
        }
    }
}

/**
 * @brief Generates a random number between 1 and 100.
 * 
 * This function uses a time-based seed to ensure that a unique 
 * random number is generated each time the game is played.
 * 
 * @return unsigned char The randomly generated number.
 */
unsigned char GenerateRandomNumber(void) {
    /* Seed the random number generator with the current time */
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count(); 
    std::mt19937 generator(seed); /* Initialize generator with the seed */
    std::uniform_int_distribution<> distribution(1, 100); /* Define range [1, 100] */

    /* Generate and return random number */
    return static_cast<unsigned char>(distribution(generator));
}

/**
 * @brief Prints feedback based on the user's guess.
 * 
 * This function compares the guessed number to the randomly generated 
 * number and provides feedback to guide the player.
 * 
 * @param[in] EnteredNum The number entered by the user.
 * @param[in] RandomNum The random number generated by the game.
 */
void PrintStatusMessage(unsigned char EnteredNum, unsigned char RandomNum) {
    /* Check if the guessed number matches the random number */
    if (EnteredNum == RandomNum) {
        std::cout << "Congratulations! You guessed the correct number!\n";
    } 
    /* Check if the guessed number is close (within 5) to the random number */
    else if (static_cast<unsigned char>(abs(EnteredNum - RandomNum)) <= 5U) {
        std::cout << "You're very close!\n";
    } 
    /* Check if the guessed number is moderately close (within 10) to the random number */
    else if (static_cast<unsigned char>(abs(EnteredNum - RandomNum)) <= 10U) {
        std::cout << "You're getting closer!\n";
    } 
    /* Notify the user that their guess is far off */
    else {
        std::cout << "Not even close. Keep trying!\n";
    }
}

/**
 * @brief Runs the guessing game algorithm.
 * 
 * This function continuously prompts the user for guesses until the 
 * correct number is guessed. It generates a random number at the 
 * beginning and provides feedback after each guess.
 */
void RunAlgorithm(void) {
    unsigned char RandomNum = GenerateRandomNumber(); /* Generate a random number */
    unsigned char User_EnteredNum;

    /* Loop until the user guesses the correct number */
    do {
        User_EnteredNum = GetNumberFromUser(); /* Get user's guess */
        PrintStatusMessage(User_EnteredNum, RandomNum); /* Print feedback based on the guess */

        /* Check if the user's guess is lower than the random number */
        if (User_EnteredNum < RandomNum) {
            std::cout << "Higher! Try again.\n";
        } 
        /* Check if the user's guess is higher than the random number */
        else if (User_EnteredNum > RandomNum) {
            std::cout << "Lower! Try again.\n";
        }
    } while (RandomNum != User_EnteredNum); /* Continue until the user guesses correctly */

    std::cout << "You Win !!!\n"; /* Print winning message */
}


