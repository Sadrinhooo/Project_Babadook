// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"
#include "WeepingAngelAIController.h"
#include "FlashlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_BABADOOK_API UFlashlightComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlashlightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* FlashlightMesh;
	
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* LightComponent;
	
	UPROPERTY(EditAnywhere)
	bool bLightIsOn = true;
	
	UPROPERTY(EditAnywhere)
	float ConeRange = 1000.f;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "-1", ClampMax = "1"))
	float ConeThreshold = 0.25f;
	
	UPROPERTY()
	TSet<AWeepingAngelAIController*> ActorsInCone;
	
	//Functions
	
	void Activate(bool bReset) override;
	
	void Deactivate(bool bReset);
	
	UFUNCTION(BlueprintCallable)
	void SwitchFlashlight();
	
	UFUNCTION(BlueprintCallable)
	void PerformConeDetection();
	
	UFUNCTION(BlueprintCallable)
	void ForceOff();
		
};
