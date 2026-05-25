// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ScreenShakeComponent.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "FlashlightComponent.h"
#include "BasePlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPressedCancel, FString, PressedKey);


UCLASS()
class PROJEKT_BABADOOK_API ABasePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPressedCancel OnPressedCancel;
	
	UPROPERTY(EditDefaultsOnly, Category="ScreenShake")
	TSubclassOf<UScreenShakeComponent> ScreenShakeCompRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LanternOil")
	float MaxLanternOilAmount = 400;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LanternOil")
	float LanternOilAmount = 0;
	
	UPROPERTY(EditAnywhere, Category="LanternOil")
	float LanternOilDecreaseRate;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractRange = 100;
	
	IInteractable* InteractObjectInSight;  //Den här borde cacha den objektet som är nu/sist inom interaction range
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* InteractableObjectOverlay;
	
	//Functions
	
	UFUNCTION(BlueprintCallable)
	void LookForInteractable();
	
	UFUNCTION(BlueprintCallable)
	void Interact();
	
	UFUNCTION(BlueprintCallable)
	void DecreaseLanternOil(float DeltaTime) ;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowInteractPrompt(const FString& Prompt, const FVector InteractableLocation, const UTexture2D* Widget);

	UFUNCTION(BlueprintImplementableEvent)
	void ClearInteractPrompt();

};
