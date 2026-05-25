// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interactable.h"
#include "MyGameMode.h"
#include "KeyItem.h"
#include "GameFramework/Actor.h"
#include "ItemPedestal.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AItemPedestal : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPedestal();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void PlaceItem();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void PickUpItem();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsItemPlaced = false;

	UPROPERTY(BlueprintReadWrite)
	AMyGameMode* GameMode;
	
	UPROPERTY(VisibleAnywhere)
	int32 KeyIndex = 0; //Used for caching the index of the keyitem in the bombaclat inventory array
	
	//Jag kanske tar en array här sen ifall man behöver flera nycklar ellr whatever dawg
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag RequiredKeyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NoKeyInteractPrompt = "LOCKED!";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlaceInteractPromt = "PRESS ""E"" TO UNLOCK";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PickupInteractPrompt = "UNLOCKED";
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};

	virtual bool PlayerHasKey(int32& OutIndex);

};
