// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "Interactable.h"
#include "ShadowPuzzleDefaultState.h"
#include "ShadowPuzzleSolvingState.h"
#include "ShadowPuzzleState.h"
#include "GameFramework/Actor.h"
#include "ShadowPuzzleManager.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API AShadowPuzzleManager : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShadowPuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	TScriptInterface<IShadowPuzzleState> PuzzleState;
	
	
	
	//State object instances
	UPROPERTY()
	UShadowPuzzleDefaultState* DefaultState;
	UPROPERTY()
	UShadowPuzzleSolvingState* SolvingState;
	
	
	
	UPROPERTY(EditAnywhere)
	AActor* PuzzleCameraActor;
	
	UPROPERTY(EditAnywhere)
	APawn* PuzzleItemPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag RequiredKeyItemTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetForwardVector = FVector(0.076f, 0.997f, 0.009f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetUpVector = FVector(0.01f, 0.009f, 1.0f);
	
	UPROPERTY(VisibleAnywhere)
	int32 KeyItemIndex = 0;
	
	UPROPERTY()
	FTimerHandle WaitHandle;
	
	
	//Functions
	virtual void Interact(ACharacter* Interactor) override; //PuzzleStates Interact funktion är det som anropas i CPP filen
	
	virtual const FString& GetInteractPrompt(ACharacter* Interactor) override; //PuzzleStates GetPrompt funktion är det som anropas i CPP filen
	
	void ChangeState(UObject* NewState);
	
	bool PlayerHasKeyItem(int32& OutIndex);
	
	void OnSuccess(float DeltaTime);
};
