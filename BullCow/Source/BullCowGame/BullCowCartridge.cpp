// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
	GameSetup();	//setting up game

	PrintLine(TEXT("The hidden word is %s."), *HiddenWord); //Debug line

	//Welcome player
    PrintLine(TEXT("Welcome to Bull Cows!"));
	PrintLine(TEXT("Guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("What is your guess? Press enter to continue..."));

	//Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

	PrintLine(Input);

	if (HiddenWord == Input)
	{
		ClearScreen();
		PrintLine(TEXT("You've guessed the isogram!!!"));
	}
	
	else
	{
		if (HiddenWord.Len() != Input.Len())
		{
			PrintLine(TEXT("The hidden word has %i letters."), HiddenWord.Len()); //TODO 
		}

		PrintLine(TEXT("Sorry, try again..."));
		Lives--;

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

	//Setup lives
	Lives = 3;
}