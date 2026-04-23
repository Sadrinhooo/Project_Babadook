// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Door.h"

#include "KeyItem.h"
#include "MyGameMode.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::Interact(ACharacter* Interactor)
{
	if (!bIsUnlocked)
	{
		if (PlayerHasKey(KeyIndex))
		{
			GameMode->SharedInventory.RemoveAt(KeyIndex);
			bIsUnlocked = true;
		}
	}
	
	GetComponentByClass<UMeshComponent>()->SetSimulatePhysics(bIsUnlocked);
}

const FString& ADoor::GetInteractPrompt(ACharacter* Interactor)
{
	if (bIsUnlocked) return UnlockedInteractPrompt;
		
	if (PlayerHasKey(KeyIndex))
	{
		return WithKeyInteractPrompt;
	} else
	{
		return NoKeyInteractPrompt;
	}
}

bool ADoor::PlayerHasKey(int32& OutIndex)
{
	for (int i = 0; i < GameMode->SharedInventory.Num(); i++)
	{
		if (GameMode->SharedInventory[i].ItemTag == RequiredKeyTag)
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}





