// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WeepingAngelAIController.generated.h"

class ABasePlayerCharacter;

UCLASS()
class PROJEKT_BABADOOK_API AWeepingAngelAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWeepingAngelAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
	FBlackboard::FKey FreezeKeyID = FBlackboard::InvalidKey;

	void FindCurrentTarget();
	bool CanSeePlayer(ABasePlayerCharacter* Player) const; 

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	bool bIsInLight = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision") 
	AActor* CurrentTargetActor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision")
	float VisionRange = 3000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision")
	float VisionDotThreshold = 0.5f; 

};