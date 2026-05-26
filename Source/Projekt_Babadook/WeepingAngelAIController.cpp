// Fill out your copyright notice in the Description page of Project Settings.
#include "WeepingAngelAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "FlashlightComponent.h"
#include "EngineUtils.h"
#include "BasePlayerCharacter.h"

AWeepingAngelAIController::AWeepingAngelAIController()
{
	//Behövs för Tick ska faktiskt köras varje frame
	PrimaryActorTick.bCanEverTick = true;
	
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AWeepingAngelAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset == nullptr)
	{
		return;
	}

	if (BehaviorTreeAsset->BlackboardAsset == nullptr)
	{
		return;
	}

	BlackboardComponent->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);

	FreezeKeyID = BlackboardComponent->GetKeyID(TEXT("bFreezeLocked"));
	UE_LOG(LogTemp, Warning, TEXT("FreezeKeyID = %d"), (int32)FreezeKeyID);
	HomeLocation = InPawn->GetActorLocation();
	BlackboardComponent->SetValueAsVector(TEXT("HomeLocation"), HomeLocation);
	BlackboardComponent->SetValueAsBool(TEXT("bGoHome"), false);

	RunBehaviorTree(BehaviorTreeAsset);
}
void AWeepingAngelAIController::GoHomeNow()
{
	if (!BlackboardComponent)
	{
		return;
	}

	CurrentTargetActor = nullptr;
	BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), nullptr);
	BlackboardComponent->SetValueAsBool(TEXT("bHasTarget"), false);
	BlackboardComponent->ClearValue(TEXT("LastKnownTargetLocation"));
	BlackboardComponent->SetValueAsVector(TEXT("HomeLocation"), HomeLocation);
	BlackboardComponent->SetValueAsBool(TEXT("bGoHome"), true);
}
void AWeepingAngelAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (BlackboardComponent && BlackboardComponent->GetValueAsBool(TEXT("bGoHome")))
	{
		CurrentTargetActor = nullptr;
		BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), nullptr);
		BlackboardComponent->SetValueAsBool(TEXT("bHasTarget"), false);
		return;
	}
	
	AActor* OldTarget = CurrentTargetActor;
	// Update which player the angel is currently targeting
	FindCurrentTarget();
	

	if (BlackboardComponent)
	{
		// Store the current target actor in the Blackboard
		BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), CurrentTargetActor);

		// Store whether the angel currently has a valid target
		BlackboardComponent->SetValueAsBool(TEXT("bHasTarget"), CurrentTargetActor != nullptr);

		if (OldTarget && !CurrentTargetActor)
		{
			//ändrade här
			BlackboardComponent->SetValueAsVector(TEXT("LastKnownTargetLocation"),OldTarget->GetActorLocation());
		}
	}

	if (BlackboardComponent && FreezeKeyID != FBlackboard::InvalidKey)
	{
		BlackboardComponent->SetValue<UBlackboardKeyType_Bool>(FreezeKeyID, bIsInLight);

		const bool BBValue = BlackboardComponent->GetValue<UBlackboardKeyType_Bool>(FreezeKeyID);

		UE_LOG(LogTemp, Warning, TEXT("Controller Tick | bIsInLight=%s | bFreezeLocked=%s | KeyID=%d"),
			bIsInLight ? TEXT("true") : TEXT("false"),
			BBValue ? TEXT("true") : TEXT("false"),
			(int32)FreezeKeyID);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller Tick | Invalid FreezeKeyID or BlackboardComponent null"));
	}
}

bool HasFlashlightOn(ABasePlayerCharacter* Player)
{
	if (!Player)
	{
		return false;
	}

	UFlashlightComponent* Flashlight = Player->FindComponentByClass<UFlashlightComponent>();
	if (!Flashlight)
	{
		return false;
	}

	return Flashlight->bLightIsOn;
}

bool AWeepingAngelAIController::CanSeePlayer(ABasePlayerCharacter* Player) const
{
	// Stop if player or AI pawn doesnt exist 
	if (!Player || !GetPawn())
	{
		return false;
	}

	const FVector MyLocation = GetPawn()->GetActorLocation();
	const FVector TargetLocation = Player->GetActorLocation();

	// Direction and distance to Player
	const FVector ToTarget = (TargetLocation - MyLocation);
	const float DistanceSq = ToTarget.SizeSquared();

	// Too far away = cant see 
	if (DistanceSq > VisionRange * VisionRange)
	{
		return false;
	}

	// Look if player is infront of AI 
	const FVector Forward = GetPawn()->GetActorForwardVector();
	const FVector Dir = ToTarget.GetSafeNormal();
	const float Dot = FVector::DotProduct(Forward, Dir);

	// outsife of the vision cone = cant see 
	if (Dot < VisionDotThreshold)
	{
		return false;
	}

	// Line trace to see if anything is blocking the vision 
	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(WeepingAngelVision), false, GetPawn());

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		MyLocation,
		TargetLocation,
		ECC_Visibility,
		Params
	);

	// if nothing hits then its free vision 
	if (!bHit)
	{
		return true;
	}
	
	return Hit.GetActor() == Player;
}

void AWeepingAngelAIController::FindCurrentTarget()
{
	UWorld* World = GetWorld();

	// Stop if world or world is missing
	if (!World || !GetPawn())
	{
		return;
	}

	ABasePlayerCharacter* BestPlayer = nullptr;
	float BestScore = -FLT_MAX;

	// Loop thru all the players
	for (TActorIterator<ABasePlayerCharacter> It(World); It; ++It)
	{
		ABasePlayerCharacter* Player = *It;
		if (!Player)
		{
			continue;
		}

		// Only the player that the enemy can see is Target 
		if (!CanSeePlayer(Player))
		{
			continue;
		}

		const bool bFlashlightOn = HasFlashlightOn(Player);

		// Score = closer player is better 
		const float Distance = FVector::Dist(Player->GetActorLocation(), GetPawn()->GetActorLocation());
		float Score = -Distance;

		// Bonus if player doesnt hae lamp on
		if (!bFlashlightOn)
		{
			Score += 100000.f;
		}

		// Save the best candidate
		if (Score > BestScore)
		{
			BestScore = Score;
			BestPlayer = Player;
		}
	}
	CurrentTargetActor = BestPlayer;
}

