// bullsAndCowsGame.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "FBullCowGame.h"

using namespace std;

bool AskPlayAgain();
void PrintIntro();
void PlayGame();
string GetValidGuess();

FBullCowGame BCGame;  //Variable BCGame to access through the whole program

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskPlayAgain();
	} while (bPlayAgain);
	return 0;
}

//Ask User to play again or not
bool AskPlayAgain() {
	char ask;
	cout << "Do you Want to play again ? press (y/n) : ";
	cin >> ask;
	cout << endl;
	if(ask == 'y') {
		system("CLS");
		return true;
	}
	else {
		cout << "****Thank You For Playing****" << endl;
			return false;
	}
}

//Print Intro
void PrintIntro() {
	/*std::cout << "MM                   MM                                     \n";
	std::cout << "MMM+                8MM                                     \n";
	std::cout << "MMMMMM            :MMM                        MM,     ZMM   \n";
	std::cout << "ZMMM+MMMM+       MMMM                         MMMO  MMMMM   \n";
	std::cout << "   MMM  MMMMMMMMMMMN                            MMMMMMMZ    \n";
	std::cout << "    MMMMM   MMMMMMMMM                        ZMMMZMZ, MMMMMM\n";
	std::cout << "      $MMD  MMM    MMMMMMM         MMMMMMMMMMMMM         MMM\n";
	std::cout << "777MMMMDI               I7MMM~  7MMMIIIIIII+                \n";
	std::cout << "MMM?                       MMM +MM                          \n";
	std::cout << "                           ZMM +M+                          \n";
	std::cout << "        B U L L S          MMM  MM            C O W S       \n";
	std::cout << "                     MMMMMMMO    MMMMMMM                    \n";
	std::cout << "               ZMMMMMMMM               MMMMM                \n";
	std::cout << "             MMMM                         MMMMM             \n";
	std::cout << "            MMM                               MMMMM         \n";
	std::cout << "           MMO                                   MM,        \n";*/
	cout << "****Welcome to Bull and Cow Game****" << endl << endl;
	std::cout << "         }   {         ___ " << std::endl;
	std::cout << "         (o o)        (o o) " << std::endl;
	std::cout << "  /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << " / | BULL |0            0|  COW | \\  " << std::endl;
	std::cout << "*  |----- |              | -----|  *  " << std::endl;
	std::cout << "   ^      ^              ^      ^     " << std::endl;
	cout << "To win, Try to guess the "<< BCGame.GetHiddenWordLength() <<" letter isogram I'm thinking Of\n"<<endl;
	cout << "Instructions :" << endl;
	cout << "* Bull Count shows that the entered word contains number of letters which are right and at right position\n";
	cout << "* Cow shows that the entered word contains number of letters which are right but at wrong postion\n";
	cout << "* Use only Isogram Word \n";
	cout << "* You have only " << BCGame.GetMaxTries() << " Tries" << endl;
	cout << "* Word is having only "<< BCGame.GetHiddenWordLength()<<" letters\n";
	cout << "* Use only LowerCase Letters\n" << endl;
	cout << "\nWide area with Silent Water" << endl;
}

// start the game
void PlayGame() {
	BCGame.Reset();
	//get maximum number of tries
	int MaxTries = BCGame.GetMaxTries();
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		string Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		cout << "Bulls : " << BullCowCount.Bulls <<"\t";
		cout << "Cows : " << BullCowCount.Cows << endl;
		cout << endl;
	}
	if (BCGame.IsGameWon()) {
		cout << "\n\n*****CONGRATULATIONS YOU WON*****\n\n";
	}
	else {
		cout << "SORRY YOU ARE OUT OF TRIES, PLEASE TRY AGAIN\n" << endl;
	}
}

//Get the Guess from Player
string GetValidGuess() {
	EWordStatus Status = EWordStatus::INVALID_STATUS;
	do {
		int CurrentTry = BCGame.GetCurrentTry();
		string Guess;
		cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ",";
		cout << " Enter your guess : " ;
		cin >> Guess;
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EWordStatus::NOT_ISOGRAM:
			cout << "Enter an Isogram word\n" << endl;
			break;
		case EWordStatus::WORD_LENGTH:
			cout << "Please Enter a word of " << BCGame.GetHiddenWordLength() << " letter\n"<< endl;
			break;
		case EWordStatus::NOT_LOWERCASE:
			cout << "Use small letters only\n" << endl;
			break;
		default:
			return Guess;
		}
	} while (Status != EWordStatus::OK); // Loop untill we get a valid Guess
}
