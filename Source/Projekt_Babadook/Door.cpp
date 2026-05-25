// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "KeyItem.h"
#include "MyGameMode.h"
#include "Components/BoxComponent.h"

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
	Door = GetComponentByClass<UStaticMeshComponent>();
	
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







