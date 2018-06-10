#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } //Constructor to reset the game

void FBullCowGame::Reset(){ // Reset the game OR default initialize all the memebers
	constexpr int MAX_TRIES = 10;
	MyMaxTry = MAX_TRIES;
	bIsGameWon = false;
	const std::string HiddenWord = "lake";
	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;
	return;
}

//Return number of MaxTries available
int FBullCowGame::GetMaxTries() const{
	TMap <int, int> WordLengthToMaxTries { { 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 } }; //Map to return Max try according to length of the word
	return WordLengthToMaxTries[FBullCowGame::MyHiddenWord.length()];
}

//Return the Current try count
int FBullCowGame::GetCurrentTry() const{
	//int MaxTries = GetMaxTries();
	return MyCurrentTry;
}


//Check if game is won?
bool FBullCowGame::IsGameWon() const{
	return bIsGameWon;
}

//Check the validity of the entered Guess according to instructions
EWordStatus FBullCowGame::CheckGuessValidity(std::string Guess) const{
	if (Guess.length() != MyHiddenWord.length()) {
		return EWordStatus::WORD_LENGTH;
	}
	else if (!IsIsogram(Guess)){ return EWordStatus::NOT_ISOGRAM; }
	else if (!IsLowercase(Guess)) { return EWordStatus::NOT_LOWERCASE; }
	else
	{
		return EWordStatus::OK;
	}
}

//Submit the Guess and Check the Bulls and Cows Counts
FBullCowCount FBullCowGame::SubmitGuess(std::string Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int HiddenWordLength = MyHiddenWord.length();
	for (int MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		for (int GChar = 0; GChar < HiddenWordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

//Return Length of the hidden word
int FBullCowGame::GetHiddenWordLength() {
	return MyHiddenWord.length();
}

//to check if Guess is Isogram or not
bool FBullCowGame::IsIsogram(std::string Guess) const {
	if (Guess.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true; //add the letter to map
		}
	}
}

//to check if Guess letters are all in Lower Case 
bool FBullCowGame::IsLowercase(std::string Guess) const {
	if (Guess.length() <= 1) { return true; }
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}