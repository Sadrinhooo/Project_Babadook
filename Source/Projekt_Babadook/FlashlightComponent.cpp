// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashlightComponent.h"
#include "BasePlayerCharacter.h"

// Sets default values for this component's properties
UFlashlightComponent::UFlashlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();
	ActivateFlashlight();
	// ...
	
}


// Called every frame
void UFlashlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PerformConeDetection();
	// ...
}

void UFlashlightComponent::ActivateFlashlight()
{
	bPlayerIsPossessed = false;
	SetComponentTickEnabled(true);
	SetActive(true);
}

void UFlashlightComponent::DeactivateFlashlight()
{
	ForceOff();
	bPlayerIsPossessed = true;
	SetComponentTickEnabled(false);
	SetActive(false);
}

void UFlashlightComponent::SwitchFlashlight()
{
	if (bPlayerIsPossessed) return;
	
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(GetOwner());
	if (!Player) return;
	
	if (!bLightIsOn && Player->LanternOilAmount <= 0.f) return;

	bLightIsOn = !bLightIsOn;
	//LightComponent->SetVisibility(bLightIsOn);
}

void UFlashlightComponent::ForceOff()
{
	bLightIsOn = false;
	//LightComponent->SetVisibility(false);
}


//Gazelle Ändrade härifrån 
void UFlashlightComponent::PerformConeDetection()
{
	// position and direction from the lamp
	const FVector Origin = GetComponentLocation();
	const FVector Forward = GetForwardVector();

	TArray<FOverlapResult> Overlaps;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(ConeRange);
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Origin, FQuat::Identity,
		ECC_GameTraceChannel1, Sphere);

	// Reset all controllers from last frame
	for (AWeepingAngelAIController* Controller : ActorsInCone)
	{
		if (!Controller) continue;
		
		Controller->bIsInLight = false;
	}
	ActorsInCone.Empty();

	//Go thru all overlaps and put bIsInLight = true for the enemies in cone
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.GetActor();
		if (!HitActor || HitActor == GetOwner())
		{
				continue;
		}

		//Vector from lamp to target
		const FVector ToTarget = (HitActor->GetActorLocation() - Origin).GetSafeNormal();
		
		const float Dot = FVector::DotProduct(Forward, ToTarget);
		
		//Only if the lamp is on and inside the cone
		if (Dot >= ConeThreshold && bLightIsOn)
		{
			APawn* Pawn = Cast<APawn>(HitActor);
			if (!Pawn) continue;
			
			AWeepingAngelAIController* Controller = Cast<AWeepingAngelAIController>(Pawn->GetController());
			if (!Controller) continue;
			
			UE_LOG(LogTemp, Warning, TEXT("Flashlight sees: %s"), *Controller->GetName());
			Controller->bIsInLight = true;
			ActorsInCone.Add(Controller);
		}
		
	}

	/*
	 DrawDebugSphere(GetWorld(), Origin, ConeRange, 32,
		FColor::Green, false, -1.f, 0, 2.f);
	*/
}

