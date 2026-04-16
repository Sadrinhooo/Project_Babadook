// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerEnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AStalkerEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	int numOFPLAYER = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("%d"), numOFPLAYER)
	Player1 = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

void AStalkerEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (LineOfSightTo(Player1))
	{
		SetFocus(Player1);
		MoveToActor(Player1, 200);
	}else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
	
}
