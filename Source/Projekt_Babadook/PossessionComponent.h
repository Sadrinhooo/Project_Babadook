// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlashlightComponent.h"
#include "Components/ActorComponent.h"
#include "PossessionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class PROJEKT_BABADOOK_API UPossessionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPossessionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float PossessionStrength = 600.f;
	
	UPROPERTY(EditAnywhere)
	float DirectionChangeInterval = 0.8f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFlashlightComponent* PlayerFlashlightComponent;
	
	FVector CurrentDirection;
	FTimerHandle DirectionTimer;
	
	//Functions
	
	UFUNCTION(BlueprintCallable)
	void PossessPlayer();
	
	UFUNCTION(BlueprintCallable)
	void DispossessPlayer();
	
	void ActivatePossession();
	
	void DeactivatePossession();
	
	void PickNewDirection();
		
};
