// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interactable.h"
#include "KeyItem.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void PlaySFX();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlocked = false;

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
	FString WithKeyInteractPrompt = "PRESS ""E"" TO UNLOCK";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UnlockedInteractPrompt = "UNLOCKED";
	
	UPROPERTY(EditAnywhere)
	bool bShouldInterpDoor = false;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;
	
	UPROPERTY()
	FRotator TargetRotation;
	
	//Functions
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};

	virtual bool PlayerHasKey(int32& OutIndex);

	UFUNCTION(BlueprintCallable, Blueprintable)
	void OpenForMonster(const FVector& OpenerLocation);
	
	void OpenDoor(const FVector& PlayerLocation);
	
	float GetOpenerDirectionToDoor(const FVector& OpenerLocation);
	
};
