// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Wardrobe.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AWardrobe : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWardrobe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable)
    	TArray<UMaterial*> CosmeticMaterials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString InteractPrompt = "Appearance Updated";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* PlayerSkeletalMesh;
	
	UPROPERTY()
	int32 CurrentMaterialIndex = 0;
	
	//Functions
	
	UFUNCTION(BlueprintImplementableEvent)
	void InteractAnim();
	
	virtual void Interact(ACharacter* Interactor) override;
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override
	{
		return InteractPrompt;
	}
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	FVector GetInteractPromptLocation();
	
	virtual const FVector GetInteractableLocation() override
	{
		return this->GetInteractPromptLocation();
	};
	

};
