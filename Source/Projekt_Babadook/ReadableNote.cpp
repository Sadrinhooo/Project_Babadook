// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadableNote.h"

// Sets default values
AReadableNote::AReadableNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReadableNote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReadableNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReadableNote::Interact(ACharacter* Interactor)
{
	if (!bIsReading)
	{
		Pressed();
	}
	
}

const FString& AReadableNote::GetInteractPrompt(ACharacter* Interactor)
{
	if (!bIsReading)
	{
		return InteractPrompt;
	}
	else
	{
		return CantInteractPrompt;
	}
}
