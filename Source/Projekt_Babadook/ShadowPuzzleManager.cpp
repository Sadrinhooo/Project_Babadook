// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowPuzzleManager.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "KeyItem.h"
#include "MyPlayerController.h"
#include "MyPlayerController.h"
#include "ShadowPuzzleDefaultState.h"
#include "Components/BoxComponent.h"


// Sets default values
AShadowPuzzleManager::AShadowPuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShadowPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	MyPC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	DefaultState = NewObject<UShadowPuzzleDefaultState>(this);
	SolvingState = NewObject<UShadowPuzzleSolvingState>(this);
	ChangeState(DefaultState);
	PuzzleState->InitiateState();
}

// Called every frame
void AShadowPuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ((FVector::DotProduct(PuzzleItemPawn->GetActorForwardVector(), TargetForwardVector)) > 0.95f &&
		FVector::DotProduct(PuzzleItemPawn->GetActorUpVector(), TargetUpVector) > 0.95f)
	{
		
		OnSuccess(DeltaTime);
	}
	
	if (bSuccessTriggered)
	{
		FQuat TargetQuat = TargetRotation.Quaternion();
		FQuat CurrentQuat = PuzzleItemPawn->GetActorQuat();
		FQuat NewQuat = FQuat::Slerp(CurrentQuat, TargetQuat, DeltaTime * 3);
		NewQuat.Normalize();
		PuzzleItemPawn->SetActorRotation(NewQuat);
	}
	
	for (FItemData& Item : GameMode->SharedInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *Item.ItemName);
	}
}

void AShadowPuzzleManager::Interact(ACharacter* Interactor)
{
	PuzzleState->Interact(Interactor);
}

const FString& AShadowPuzzleManager::GetInteractPrompt(ACharacter* Interactor)
{
	return PuzzleState->GetInteractPrompt(Interactor);
}

UTexture2D* AShadowPuzzleManager::GetWidget()
{
	if (PlayerHasKeyItem(KeyItemIndex))
	{
		return nullptr;
	}else
	{
		return PromptImage;
	}
}

void AShadowPuzzleManager::ChangeState(UObject* NewState)
{
	PuzzleState = NewState;
}

bool AShadowPuzzleManager::PlayerHasKeyItem(int32& OutIndex)
{
	for (int i = 0; i < Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this))->SharedInventory.Num(); i++)
	{
		if (Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this))->SharedInventory[i].ItemTag == RequiredKeyItemTag)
		{
			OutIndex = i;
			return true;
		}
	}

	return false;
}

void AShadowPuzzleManager::ExitPuzzle()
{
	if (MyPC)
	{
		MyPC->UnpossessPuzzlePawn(); // This should repossess the player pawn
		MyPC->bAutoManageActiveCameraTarget = true;
		ChangeState(DefaultState);
		HideWidget();
		if (!bSuccessTriggered)
		{
			SetInteractable(true);
		}
	}
}

void AShadowPuzzleManager::OnSuccess(float DeltaTime)
{
	// Guard so this only runs once
	if (bSuccessTriggered) return;
	bSuccessTriggered = true;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PC->GetPawn();
	Success();

	PlayerPawn->DisableInput(PC);

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, [this]()
	{

		ExitPuzzle();

		// Get the pawn AFTER unpossess, since possession may have changed
		APawn* PlayerPawn = MyPC->GetPawn();
		if (PlayerPawn)
		{
			PlayerPawn->EnableInput(MyPC); // Called on the PAWN, not 'this'
		}
		PrimaryActorTick.bCanEverTick = false;
	}, 4.0f, false);

	SetInteractable(false);
}

void AShadowPuzzleManager::SetInteractable(bool Interactable)
{
	UBoxComponent* Collider = FindComponentByClass<UBoxComponent>();
	if (Collider)
	{
		if (Interactable)
		{
			Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
		}
		else
		{
			Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
		}
	}
}

