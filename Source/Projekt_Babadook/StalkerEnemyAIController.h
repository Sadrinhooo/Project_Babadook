// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include "StalkerEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_BABADOOK_API AStalkerEnemyAIController : public AEnemyAIController
{
	GENERATED_BODY()
	
public:
	
	APawn* Player1;
	APawn* Player2;
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
