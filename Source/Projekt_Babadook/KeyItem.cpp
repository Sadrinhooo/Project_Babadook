// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "MyGameMode.h"

#include "Misc/MapErrors.h"

// Sets default values
AKeyItem::AKeyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKeyItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyItem::Interact(ACharacter* Interactor)
{
	GameMode->SharedInventory.Add(ItemData);
	//Nåt mer om det behövs
	Destroy();
}

