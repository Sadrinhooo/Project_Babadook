// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightPuzzle")
	FString InteractPrompt = "PRESS ""E"" TO ENTER PUZZLE";
	
	UPROPERTY(BlueprintReadWrite, Category = "LightPuzzle")
	float BlendTime = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightPuzzle")
	bool bCanEnterPuzzle = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LightPuzzle")
	bool bInPuzzle = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};
	
	void PuzzleEnter(ABasePlayerCharacter* Player, APlayerController* PlayerController);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartPuzzle();
	
	UFUNCTION(BlueprintCallable, Category = "LightPuzzle")
	void PuzzleExit(ABasePlayerCharacter* Player, APlayerController* PlayerController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ClearInteractPrompt();
};
	
