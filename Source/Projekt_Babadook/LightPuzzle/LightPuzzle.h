// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projekt_Babadook/Interactable.h"
#include "LightPuzzle.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API ALightPuzzle : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightPuzzle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightPuzzle");
	FString InteractPrompt = "PRESS ""E"" TO ENTER PUZZLE";
	
	UPROPERTY(BlueprintReadWrite, Category = "LightPuzzle");
	float BlendTime = 0.5f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(ACharacter* Interactor) override;
	
	virtual const FString GetInteractPrompt_Implementation(ACharacter* Interactor) override;
	
	void PuzzleEnter(ABasePlayerCharacter* Player, APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable, Category = "LightPuzzle")
	void PuzzleExit(ABasePlayerCharacter* Player, APlayerController* PlayerController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ClearInteractPrompt();
};
	
