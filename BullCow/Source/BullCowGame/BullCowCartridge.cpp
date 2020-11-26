// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	GameSetup();	//setting up game

	PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

	 //If gameover do clearscreen() reset game.
		//else check PlayerGuess 

	PrintLine(Input);

	if (bGameOver)
	{
		ClearScreen();
		GameSetup();
	}
	else
	{
		ProcessGuess(Input);
	}
	//Check if isogram
	//Check right number of characters

	//remove a life
	
	//check if lives > zero
		//if true Guess again
		//if false = gameover  and Show Hidden word
	//Prompt to Play again, Press Enter to play again?
	//check user input
	//Playagain or quit
}

//initiates the game
void UBullCowCartridge::GameSetup()
{
	//Set the Hidden word
	HiddenWord = TEXT("Cakes");
	Lives = HiddenWord.Len();
	bGameOver = false;

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
	}

	else
	{
		PrintLine(TEXT("You have %i trys left."), --Lives);

		if (Lives > 0)
		{
			if (HiddenWord.Len() != Guess.Len())
			{
				PrintLine(TEXT("The hidden word has %i letters."), HiddenWord.Len()); //TODO 
			}
		}
		else
		{
			ClearScreen();
			PrintLine(TEXT("You have no trys left."));
			GameOver();
		}
	}
}