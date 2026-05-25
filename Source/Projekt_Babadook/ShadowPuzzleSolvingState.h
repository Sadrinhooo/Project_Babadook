// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowPuzzleState.h"
#include "UObject/Object.h"
#include "ShadowPuzzleSolvingState.generated.h"

class AShadowPuzzleManager;

UCLASS(Blueprintable)
class PROJEKT_BABADOOK_API UShadowPuzzleSolvingState : public UObject, public IShadowPuzzleState
{
	GENERATED_BODY()
	
public:
	
	UShadowPuzzleSolvingState();
	
	UPROPERTY(BlueprintReadOnly)
	AShadowPuzzleManager* Owner;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NoPrompt = "";
	
	
	//Functions
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FVector GetInteractableLocation() override
	{
		return FVector::ZeroVector;
	};
	
	virtual void InitiateState() override;
};
