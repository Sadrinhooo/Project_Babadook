// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessionComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPossessionComponent::UPossessionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPossessionComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerFlashlightComponent = GetOwner()->FindComponentByClass<UFlashlightComponent>();
	PickNewDirection();
	DispossessPlayer();
	// ...
}


// Called every frame
void UPossessionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Cast<ACharacter>(GetOwner())->AddMovementInput(CurrentDirection, PossessionStrength);

	// ...
}

void UPossessionComponent::PossessPlayer()
{

	PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	if (PlayerFlashlightComponent) PlayerFlashlightComponent->DeactivateFlashlight();
	SetComponentTickEnabled(true);
	SetActive(true);
	PickNewDirection();
	GetWorld()->GetTimerManager().SetTimer(
		DirectionTimer,
		this,
		&UPossessionComponent::PickNewDirection,
		DirectionChangeInterval,
		true);
	if (PlayerController) PlayerController->ClientStartCameraShake(CameraShakeObject, ScreenShakeIntensity);
	else UE_LOG(LogTemp, Warning, TEXT("PC IS NULL"))
}

void UPossessionComponent::DispossessPlayer()
{
	PlayerFlashlightComponent->ActivateFlashlight();
	SetComponentTickEnabled(false);
	SetActive(false);
	GetWorld()->GetTimerManager().ClearTimer(DirectionTimer);
}



void UPossessionComponent::PickNewDirection()
{
	float XAxis = FMath::FRandRange(-1.f, 1.f);
	float YAxis = FMath::FRandRange(-1.f, 1.f);
	CurrentDirection = FVector(XAxis, YAxis, 0.f);
	CurrentDirection.Normalize();
}

void UPossessionComponent::Mash()
{
	MashCount++;
}

//bomboclat
