// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;
	
	//Jag tar en array här för nu ifall man behöver flera nycklar ellr whatever dawg
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> RequiredKeyTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LockedInteractPrompt = "LOCKED!";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UnlockedInteractPrompt = "PRESS ""E"" TO UNLOCK";
	
	
	
	//Functions
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
};
