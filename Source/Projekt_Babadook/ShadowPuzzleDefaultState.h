// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ShadowPuzzleState.h"
#include "UObject/Object.h"
#include "ShadowPuzzleDefaultState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJEKT_BABADOOK_API UShadowPuzzleDefaultState : public UObject, public IShadowPuzzleState
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NoItemInteractPrompt = "SOMETHING IS MISSING!";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WithItemInteractPrompt = "PRESS ""E"" TO UNLOCK";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UnlockedInteractPrompt = "UNLOCKED";
	
	//Functions
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	
};
