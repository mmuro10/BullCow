// Fill out your copyright notice in the Description page of Project Settings.

#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	Isograms = GetValidWords(Words);

	//For having the word list in a .txt file
	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	FFileHelper::LoadFileToStringArray(Words, *WordListPath);
	
	GameSetup();	//setting up game
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    ClearScreen();

	if (bGameOver)
	{
		ClearScreen();
		GameSetup();
	}
	else
	{
		ProcessGuess(PlayerInput);
	}
}

//initiates the game
void UBullCowCartridge::GameSetup()
{
	//Set the Hidden word
	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line

	//Welcome player
	PrintLine(TEXT("Welcome to Bull Cows!"));
	PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
	PrintLine(TEXT("You have %i trys."), Lives);
	PrintLine(TEXT("What is your guess? Press enter to continue..."));
}

void UBullCowCartridge::GameOver()
{
	bGameOver = true;

	PrintLine(TEXT("GAME OVER!"));
	PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
	PrintLine(TEXT("Press Enter to play again."));
	
}



void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	//check user input
	if (HiddenWord == Guess)
	{
		ClearScreen();
		PrintLine(TEXT("You've guessed the isogram!!!"));
		PrintLine(TEXT("Press Enter to play again."));
		bGameOver = true;
		return;
	}
	
	//remove a life
	--Lives;
	
	//check if lives > zero
	if (Lives <= 0)
	{
		GameOver();
		return;
	}
	
	// Show the player Bulls and Cows
	

	//Check right number of characters
	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(Guess);	
		PrintLine(TEXT("The hidden word has %i letters."), HiddenWord.Len()); //TODO 
		PrintLine(TEXT("You have %i trys left."), Lives);
		return;
	}
	
	//Check if isogram
	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
		PrintLine(TEXT("You have %i trys left."), Lives);
	}
	
	else
	{
		PrintLine(Guess);
		PrintLine(TEXT("You have %i trys left."), Lives);
		return;
	}
	/*
	int32 Bulls, Cows;
	GetBullCows(Guess, Bulls, Cows);

	PrintLine(TEXT("You hae %i Bulls and %i Cows"), Bulls, Cows);*/
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for (int32 Index = 0; Index < Word.Len(); Index++)
	{
		for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[Index] == Word[Comparison])
			{
				return false;
			}
		}
	} 
	return true; 
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;

	for (FString Word: WordList)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}
	
		return ValidWords;
}

/*
void UBullCowCartridge::GetBullCows(const FString & Guess, int32 & BullCount, int32 & CowCount) const
{
	BullCount = 0;
	CowCount = 0;

	//for ever index of guess is same as index hiddenword BullCount++
		//else CowCount++
	for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
	{
		if (Guess[GuessIndex] == HiddenWord[GuessIndex])
		{
			BullCount++;
			continue;
		}

		for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
		{
			if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
			{
				CowCount++;
			}
		}
	}
}
*/