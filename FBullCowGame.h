#pragma once
#include"stdafx.h"
#include<string>

//Create a datatype to count Bulls and Cows
struct FBullCowCount {
	int Bulls = 0;
	int Cows = 0;
};

enum class EWordStatus //Enumerations to increase the readability
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	NOT_LOWERCASE,
	WORD_LENGTH
};

class FBullCowGame {
public:
	FBullCowGame();
	void Reset(); // to reset
	int GetMaxTries() const; //Get Maximum Tries
	int GetCurrentTry() const; //Get Current Try
	bool IsGameWon() const; //To check the status of Game
	EWordStatus CheckGuessValidity(std::string) const; //To check the Status of game
	FBullCowCount SubmitGuess(std::string); //To submit Guess
	int GetHiddenWordLength() ;//To get Length of the word to find

private:
	int MyCurrentTry; //For CurrentTryCount
	int MyMaxTry; //For Number of Tries available
	std::string MyHiddenWord ; //To store Word to be guessed
	bool bIsGameWon; //to Check the status of Game Won or not
	bool IsIsogram(std::string) const;
	bool IsLowercase(std::string) const;
	//bool IsIsogram(std::string);
};
