// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	void GameSetup();
	void GameOver();
	//void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;

	TArray<FString> Words; //This is for reading the words from the text file

	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;

	// Your declarations go below!
private:

	FString HiddenWord;
	TArray<FString> Isograms;
	
	int32 Lives;

	bool bGameOver;
	
};
