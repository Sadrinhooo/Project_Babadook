// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "MyGameMode.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "KeyItem.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AKeyItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite)
	AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	
	//Functions
	
	virtual void Interact(ACharacter* Interactor) override;
};
