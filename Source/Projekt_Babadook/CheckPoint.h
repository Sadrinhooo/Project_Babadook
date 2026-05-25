// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API ACheckPoint : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckPoint();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ToSaveInteractPrompt = "PRESS ""E"" TO Save";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override;
	
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};
	
	UFUNCTION(BlueprintImplementableEvent)
	void Save();
};
