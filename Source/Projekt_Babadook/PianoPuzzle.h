// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "PianoPuzzle.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API APianoPuzzle : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	
	virtual void Interact(ACharacter* Interactor) override;
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetActorLocation();
	};

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	FString InteractPrompt = "PRESS ""E"" TO REFILL";
};
