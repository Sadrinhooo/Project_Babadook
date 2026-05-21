// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ShadowPuzzleState.h"
#include "UObject/Object.h"
#include "ShadowPuzzleDefaultState.generated.h"

class AShadowPuzzleManager;

UCLASS(Blueprintable)
class PROJEKT_BABADOOK_API UShadowPuzzleDefaultState : public UObject, public IShadowPuzzleState
{
	GENERATED_BODY()
	
public:
	
	UShadowPuzzleDefaultState();
	
	UPROPERTY()
	AShadowPuzzleManager* Owner;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NoItemInteractPrompt = "SOMETHING IS MISSING!";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString HasItemInteractPrompt = "PRESS ""E"" TO INSERT";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MoveItemInteractPrompt = "PRESS ""E"" TO INTERACT";
	
	
	//Functions
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual void InitiateState() override;
	
};
