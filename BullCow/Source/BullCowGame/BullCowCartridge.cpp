// Fill out your copyright notice in the Description page of Project Settings.

#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
	FFileHelper::LoadFileToStringArray(Words, *WordListPath);
	//GetValidWords(Words);
	
	GameSetup();	//setting up game

	PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line
	PrintLine(TEXT("There are %i validwords."), GetValidWords(Words).Num());


	
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

	 //If gameover do clearscreen() reset game.
		//else check PlayerGuess 

	if (bGameOver)
	{
		ClearScreen();
		GameSetup();
	}
	else
	{
		ProcessGuess(Input);
	}
}

//initiates the game
void UBullCowCartridge::GameSetup()
{
	//Set the Hidden word
	HiddenWord = TEXT("Cake");
	Lives = HiddenWord.Len();
	bGameOver = false;

	//Welcome player
	PrintLine(TEXT("Welcome to Bull Cows!"));
	PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
	PrintLine(TEXT("You have %i trys."), Lives);
	PrintLine(TEXT("What is your guess? Press enter to continue..."));

	/* const TCHAR HW[] = (TEXT("cake"));
		HW; */

	
}

void UBullCowCartridge::GameOver()
{
	bGameOver = true;

	PrintLine(TEXT("GAME OVER!"));
	PrintLine(TEXT("The hidden word was %s."), *HiddenWord);
	PrintLine(TEXT("Press Enter to play again."));
	
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (HiddenWord == Guess)
	{
		ClearScreen();
		PrintLine(TEXT("You've guessed the isogram!!!"));
		PrintLine(TEXT("Press Enter to play again."));
		bGameOver = true;
		return;
	}
	--Lives;
	
	if (Lives <= 0)
	{
		GameOver();
		return;
	}
	
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
	//remove a life

	//check if lives > zero
		//if true Guess again
		//if false = gameover  and Show Hidden word
	//Prompt to Play again, Press Enter to play again?
	//check user input
	//Playagain or quit
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	//int32 Index = 0;
	//int32 Comparison = Index++;
	 
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

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
	TArray<FString> ValidWords;

		for (int32 Index = 0; Index < WordList.Num(); Index++)
		{
			if (WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8 && IsIsogram(WordList[Index]))
			{
				ValidWords.Emplace(WordList[Index]);
			}
		}

		return ValidWords;
}