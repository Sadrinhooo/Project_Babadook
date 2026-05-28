// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItem.h"
#include "MyGameInstance.h"
#include "MyGameMode.h"

// Sets default values
AKeyItem::AKeyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKeyItem::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	
	if (GameInstance)
	{
		if (GameInstance->IsItemCollected(ItemData.ItemTag))
		{
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);
		}
	}
}

// Called every frame
void AKeyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKeyItem::Interact(ACharacter* Interactor)
{
	if (GameMode)
	{
		GameMode->AddItem(ItemData);
	}
	
	if (GameInstance)
	{
		GameInstance->CollectItem(ItemData.ItemTag);
	}
	
	PickupSFX();
	StaticMesh->SetVisibility(false);
	//Destroy();
}

const FString& AKeyItem::GetInteractPrompt(ACharacter* Interactor)
{
	return InteractPrompt;
}

