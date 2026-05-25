// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayTags.h"
#include "KeyItem.generated.h"

class AMyGameMode;

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int MaxNumberOfUses = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int NumberOfUses = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsPickedUp = false;
	
};

UCLASS()
class PROJEKT_BABADOOK_API AKeyItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's propertiess
	AKeyItem();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event on interact")
	void PickupSFX();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	FString InteractPrompt = "PRESS ""E"" TO PICKUP";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(BlueprintReadWrite)
	AMyGameMode* GameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;
	
	
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
