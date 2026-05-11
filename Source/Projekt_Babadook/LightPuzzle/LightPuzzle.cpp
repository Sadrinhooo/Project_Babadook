// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPuzzle.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projekt_Babadook/BasePlayerCharacter.h"


// Sets default values
ALightPuzzle::ALightPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALightPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightPuzzle::Interact_Implementation(ACharacter* Interactor)
{
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(Interactor);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Player, 0);
	
	PuzzleEnter(Player, PlayerController);
	
}

const FString ALightPuzzle::GetInteractPrompt_Implementation(ACharacter* Interactor)
{
	return InteractPrompt;
}

void ALightPuzzle::PuzzleEnter(ABasePlayerCharacter* Player, APlayerController* PlayerController)
{
	if (Player == nullptr || PlayerController == nullptr)
	{
		return;
	}
	
	PlayerController->SetViewTargetWithBlend(this, BlendTime);
	Player->GetCharacterMovement()->DisableMovement();
	PlayerController->SetIgnoreLookInput(true);
	EnableInput(PlayerController);
	
	
}

void ALightPuzzle::PuzzleExit(ABasePlayerCharacter* Player, APlayerController* PlayerController)
{
	if (Player == nullptr || PlayerController == nullptr)
	{
		return;
	}
	
	PlayerController->SetViewTargetWithBlend(Player, BlendTime);
	PlayerController->DisableInput(PlayerController);
	PlayerController->ResetIgnoreLookInput();
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
}

