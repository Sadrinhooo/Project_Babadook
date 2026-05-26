// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API ALever : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void Pulled();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPulled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReinteractable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractPrompt = "PRESS ""E"" TO UNLOCK";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CantInteractPrompt = "";
	
	//Functions
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};
	
};
