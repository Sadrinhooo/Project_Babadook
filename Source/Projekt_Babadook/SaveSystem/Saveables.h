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

USTRUCT(BlueprintType)
struct FBarDoorInfo
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bVisibility;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DoorRotation;
};


USTRUCT(BlueprintType)
struct FLeverInfo
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPulled;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator LeverRotation;
};


USTRUCT(BlueprintType)
struct FPianoInfo
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NoteIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform DoorTransform;
};