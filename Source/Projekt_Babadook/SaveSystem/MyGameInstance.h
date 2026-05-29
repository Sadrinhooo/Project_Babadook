// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MySaveGame.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer CollectedItems;
	
	UPROPERTY(BlueprintReadWrite)
	bool bShouldLoad = false;
	
	UPROPERTY(BlueprintReadWrite)
	FString GameSlotName = "Slot01";
	
	UPROPERTY(BlueprintReadWrite)
	UMySaveGame* SaveGame;
	
public:
	
	UFUNCTION(BlueprintCallable)
	bool IsItemCollected(FGameplayTag ItemTag) const;

	UFUNCTION(BlueprintCallable)
	void CollectItem(FGameplayTag ItemTag);
	
	
	UFUNCTION(BlueprintCallable)
	void SaveGameData() ;
	
	UFUNCTION(BlueprintCallable)
	void LoadGameData() ;

	virtual void Init() override;
};
