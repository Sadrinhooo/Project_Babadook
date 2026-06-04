// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "KeyItem.h"
#include "MyGameMode.h"
#include "Components/BoxComponent.h"
#include "SaveSystem/MyGameInstance.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
#if WITH_EDITOR
	if (!PersistentGuid.IsValid())
	{
		PersistentGuid = FGuid::NewGuid();
	}
#endif
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	Door = GetComponentByClass<UStaticMeshComponent>();
	
	if (GameInstance && GameInstance->bShouldLoad)
	{
		if (FDoorInfo* d = GameInstance->SaveGame->SavedDoors.Find(PersistentGuid))
		{
			bIsUnlocked = d->bIsUnlocked;
			Door->SetRelativeRotation(d->DoorRotation);
		}
		
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bShouldInterpDoor)
	{
		FRotator NewRotation =
			FMath::RInterpTo(
				Door->GetRelativeRotation(),
				TargetRotation,
				DeltaTime,
				3.f
			);

		Door->SetRelativeRotation(NewRotation);
	}
}

void ADoor::SendOutSave_Implementation()
{
	ISaveInterface::SendOutSave_Implementation();
	
	if (GameInstance)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, bIsUnlocked ? "True" : "False");
		GameInstance->SaveGame->SavedDoors.Add(PersistentGuid, FDoorInfo{bIsUnlocked, Door->GetRelativeRotation()});
	}
	
	GameInstance->SaveGameData();
}

void ADoor::Interact(ACharacter* Interactor)
{
	if (!bIsUnlocked)
	{
		if (PlayerHasKey(KeyIndex))
		{
			GameMode->SharedInventory[KeyIndex].NumberOfUses++;
			if (GameMode->SharedInventory[KeyIndex].NumberOfUses >= GameMode->SharedInventory[KeyIndex].MaxNumberOfUses) GameMode->SharedInventory.RemoveAt(KeyIndex);
			bIsUnlocked = true;
			OpenDoor(Interactor->GetActorLocation());
			ADoor::PlaySFX();
		}
		
	}
	
}

const FString& ADoor::GetInteractPrompt(ACharacter* Interactor)
{
	if (PlayerHasKey(KeyIndex))
	{
		return UnlockedInteractPrompt;
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

void ADoor::OpenForMonster(const FVector& OpenerLocation)
{
	
	//Gör inget för nu vi ska göra om hela dörr beteendet
	
	/*if (bIsUnlocked)
	{
		const FRotator CurrentRotation = Door->GetRelativeRotation();

		const float Offset = 50.f * GetOpenerDirectionToDoor(OpenerLocation);

		TargetRotation = FRotator(
			CurrentRotation.Pitch,
			CurrentRotation.Yaw + Offset,
			CurrentRotation.Roll
		);

		bShouldInterpDoor = true;
	}*/
	
}

void ADoor::OpenDoor(const FVector& PlayerLocation)
{
	const FRotator CurrentRotation = Door->GetRelativeRotation();

	const float Offset = 90.f * GetOpenerDirectionToDoor(PlayerLocation);

	TargetRotation = FRotator(
		CurrentRotation.Pitch,
		CurrentRotation.Yaw + Offset,
		CurrentRotation.Roll
	);

	bShouldInterpDoor = true;
	
	UBoxComponent* Collider = FindComponentByClass<UBoxComponent>();
	if (Collider)
	{
		Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	}
}

void ADoor::OpenOnLightPuzzle(const FVector& PlayerLocation)
{
	OpenDoor(PlayerLocation);
}

float ADoor::GetOpenerDirectionToDoor(const FVector& OpenerLocation)
{
	const FVector ToPlayer = (OpenerLocation - GetActorLocation()).GetSafeNormal();
	const float Side = FVector::DotProduct(GetActorForwardVector(), ToPlayer);
	const float Direction = Side > 0.f ? 1.f : -1.f;
	return Direction;
}

UTexture2D* ADoor::GetWidget()
{
	if (PlayerHasKey(KeyIndex))
	{
		return nullptr;
	} else
	{
		return Widget;
	}
}







