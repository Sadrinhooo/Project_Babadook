// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPuzzleManager.h"

// Sets default values
AShadowPuzzleManager::AShadowPuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShadowPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShadowPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShadowPuzzleManager::Interact(ACharacter* Interactor)
{
}

const FString& AShadowPuzzleManager::GetInteractPrompt(ACharacter* Interactor)
{
	return SIGMA;
}

