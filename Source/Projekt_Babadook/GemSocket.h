// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interactable.h"
#include "KeyItem.h"
#include "GameFramework/Actor.h"
#include "GemSocket.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AGemSocket : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGemSocket();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void ItemPlaced();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsItemPlaced = false;

	UPROPERTY(BlueprintReadWrite)
	AMyGameMode* GameMode;
	
	UPROPERTY(VisibleAnywhere)
	int32 ItemIndex = 0; //Used for caching the index of the keyitem in the bombaclat inventory array
	
	//Jag kanske tar en array här sen ifall man behöver flera nycklar ellr whatever dawg
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag RequiredItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NoKeyInteractPrompt = "LOCKS LIKE SOMETHING COULD FIT IN HERE";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WithKeyInteractPrompt = "PRESS ""E"" TO PLACE GEMSTONE";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UnlockedInteractPrompt = "";
	
	//Functions	
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;

	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};

	bool PlayerHasItem(int32& OutIndex);
	
};