// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "ReadableNote.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AReadableNote : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReadableNote();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void Pressed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReading = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractPrompt = "";
	
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
