// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "ShadowPuzzleState.h"
#include "GameFramework/Actor.h"
#include "ShadowPuzzleManager.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AShadowPuzzleManager : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadowPuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UShadowPuzzleState* PuzzleState;
	
	virtual void Interact(ACharacter* Interactor) override; //PuzzleStates Interact funktion är det som anropas i CPP filen
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override; //PuzzleStates GetPrompt funktion är det som anropas i CPP filen
	
	FString SIGMA = "LOCKED!";

};
