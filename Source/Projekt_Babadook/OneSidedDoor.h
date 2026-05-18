// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "OneSidedDoor.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API AOneSidedDoor : public ADoor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WrongSideInteractPrompt = "LOCKED FROM THE OTHER SIDE!";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RightSideInteractPrompt = "PRESS ""E"" TO UNLOCK";
	

	//Functions
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
};


