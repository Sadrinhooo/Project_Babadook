// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperNote.h"

// Sets default values
APaperNote::APaperNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APaperNote::BeginPlay()
{
	Super::BeginPlay();
	
	NoteInitLocation = GetActorLocation();
	
}

// Called every frame
void APaperNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


