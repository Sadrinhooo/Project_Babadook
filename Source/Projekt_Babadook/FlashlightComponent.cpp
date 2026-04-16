// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashlightComponent.h"

// Sets default values for this component's properties
UFlashlightComponent::UFlashlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	FlashlightMesh->SetupAttachment(this);
	
	LightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	LightComponent->SetupAttachment(FlashlightMesh);

	// ...
}


// Called when the game starts
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFlashlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	PerformConeDetection();
	// ...
}

void UFlashlightComponent::SwitchFlashlight()
{
	LightComponent->SetVisibility(!LightComponent->IsVisible());
}

void UFlashlightComponent::PerformConeDetection()
{
	FVector Origin = GetComponentLocation();
	FVector Forward = GetForwardVector();
	
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(ConeRange);
	
	bool bHit = GetWorld()->OverlapMultiByChannel(Overlaps, Origin, FQuat::Identity
		, ECC_GameTraceChannel1, Sphere);
	
	if (!bHit) return;
	
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.GetActor();
		if (!HitActor || HitActor == GetOwner()) continue;

		FVector ToTarget = (HitActor->GetActorLocation() - Origin).GetSafeNormal();
		float Dot = FVector::DotProduct(Forward, ToTarget);

		if (Dot >= ConeThreshold)
		{
			// Monster is in light
		}
	}
	
	DrawDebugSphere(GetWorld(), Origin, ConeRange, 32, 
		FColor::Green, false, -1.f, 0, 2.f);
	
}

