// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

struct FItemData;
/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddItem(FItemData Item);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowInventoryTutorial();
	
	UPROPERTY(BlueprintReadWrite, Category= "Inventory")
	TArray<FItemData> SharedInventory;

private:
	bool HasAddedItem;
};
