// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projekt_Babadook/KeyItem.h"
#include "Saveables.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LanternOilAmount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlayerPos;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemData> Inventory;
};

USTRUCT(BlueprintType)
struct FDoorInfo
{
	GENERATED_BODY()
	
public:
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FGuid Guid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlocked;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator DoorRotation;
};
