// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Saveables.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer CollectedItems;
	
	UPROPERTY(BlueprintReadWrite)
	FPlayerInfo PlayerInfo;
	
	UPROPERTY(BlueprintReadWrite)
	FPianoInfo PianoInfo;
	
	UPROPERTY(BlueprintReadWrite)
	FLightPuzzleInfo LightPuzzleInfo;
	
	UPROPERTY(BlueprintReadWrite)
	//TArray<FDoorInfo> DoorInfo;
	TMap<int32, FDoorInfo> DoorInfo;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FLeverInfo> LeverInfo;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FShadowPuzzleInfo> ShadowPuzzleInfo;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FBarDoorInfo> BarDoorInfo;
	
	//UPROPERTY(BlueprintReadWrite)
	//TMap<int32, FDoorInfo> SavedDoors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelName;
	
	//UPROPERTY(BlueprintReadWrite)
	//TArray<FVector> Doors;
	//TMap<int32, FDoorInfo> DoorInfo;
};
