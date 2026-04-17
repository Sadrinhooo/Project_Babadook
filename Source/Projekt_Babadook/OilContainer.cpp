// Fill out your copyright notice in the Description page of Project Settings.


#include "OilContainer.h"

#include "BasePlayerCharacter.h"

// Sets default values
AOilContainer::AOilContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOilContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOilContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOilContainer::Interact(ACharacter* Interactor)
{
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(Interactor);
	Player->LanternOilAmount = Player->MaxLanternOilAmount;
	
}
