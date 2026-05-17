// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowPuzzleManager.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	AMyPlayerController();
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
    void PossessPuzzlePawn(AShadowPuzzleManager* PuzzleManager);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UnpossessPuzzlePawn();
};
