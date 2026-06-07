// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"

#include "Interactable.h"
#include "MyGameMode.h"
#include "SaveSystem/SaveInterface.h"
#include "ScreenShakeComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Camera = FindComponentByClass<UCameraComponent>();
	
	//Yasna
	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(this));
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	
	if (ScreenShakeCompRef)
	{
		UScreenShakeComponent* Comp = NewObject<UScreenShakeComponent>(this, ScreenShakeCompRef);
		if (IsValid(Comp))
		Comp->RegisterComponent();
		
	}
	
	//Yasna - Load
	if (GameInstance && GameInstance->bShouldLoad)
	{
		LanternOilAmount = GameInstance->SaveGame->PlayerInfo.LanternOilAmount;
		SetActorTransform(GameInstance->SaveGame->PlayerInfo.PlayerPos);
		
		if(GameMode)
		{
			GameMode->SharedInventory = GameInstance->SaveGame->PlayerInfo.Inventory;
		}
	}
	
}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookForInteractable();
	DecreaseLanternOil(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePlayerCharacter::LookForInteractable()
{
	if (!CanInteract) return;
	if (!Camera) return;
	
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * InteractRange);
	
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_GameTraceChannel2  
	);

	if (bHit && Hit.GetActor()->Implements<UInteractable>())
	{
		InteractObjectInSight = Cast<IInteractable>(Hit.GetActor());
	}else
	{
		if (AActor* Actor = Cast<AActor>(InteractObjectInSight))
		{
			if (UMeshComponent* MeshComp = Actor->GetComponentByClass<UMeshComponent>())
			{
				//MeshComp->SetOverlayMaterial(nullptr);
				MeshComp->SetRenderCustomDepth(false);
			}
		}
		InteractObjectInSight = nullptr;
	}

	if (InteractObjectInSight)
	{
		//Fixa den här få at den kommer upp på UI och anpassad för controller oxå
		FString Prompt = InteractObjectInSight->GetInteractPrompt(this);
		FVector Location = InteractObjectInSight->GetInteractableLocation();
		if (AActor* Actor = Cast<AActor>(InteractObjectInSight))
		{
			if (UMeshComponent* MeshComp = Actor->GetComponentByClass<UMeshComponent>())
			{
				//MeshComp->SetOverlayMaterial(InteractableObjectOverlay);
				MeshComp->SetRenderCustomDepth(true);
				MeshComp->CustomDepthStencilValue = 1;
			}
		}
		ShowInteractPrompt(Prompt, Location, InteractObjectInSight->GetWidget());
	}else
	{
		ClearInteractPrompt();
	}
}

void ABasePlayerCharacter::Interact()
{
	if (InteractObjectInSight)
	{
		InteractObjectInSight->Interact(this);
	};
}

void ABasePlayerCharacter::DecreaseLanternOil(float DeltaTime)
{
	UFlashlightComponent* Flashlight = FindComponentByClass<UFlashlightComponent>();
	if (!Flashlight) return;
	
	if (Flashlight->bLightIsOn)
		LanternOilAmount = FMath::Max(0, LanternOilAmount - (LanternOilDecreaseRate * DeltaTime));
	
	if (LanternOilAmount <= 0)
	{
		Flashlight->bLightIsOn = false;
		Flashlight->ForceOff();
	}
}

//Yasna - Save
void ABasePlayerCharacter::SendOutSave_Implementation()
{
	ISaveInterface::SendOutSave_Implementation();
	
	if (GameInstance)
	{
		GameInstance->SaveGame->PlayerInfo.LanternOilAmount = LanternOilAmount;
		GameInstance->SaveGame->PlayerInfo.PlayerPos = GetActorTransform();
		
		if (GameMode)
		{
			GameInstance->SaveGame->PlayerInfo.Inventory = GameMode->SharedInventory;
		}
		
		GameInstance->SaveGameData();
	}
	
}

