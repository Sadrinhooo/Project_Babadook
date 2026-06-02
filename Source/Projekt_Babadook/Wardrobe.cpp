// Fill out your copyright notice in the Description page of Project Settings.


#include "Wardrobe.h"

// Sets default values
AWardrobe::AWardrobe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWardrobe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWardrobe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWardrobe::Interact(ACharacter* Interactor)
{
	if (!PlayerSkeletalMesh) return;
	//this->OnInteract();
	if (CosmeticMaterials.Num() > 0)
	{
		PlayerSkeletalMesh->SetMaterial(3, CosmeticMaterials[CurrentMaterialIndex]);
		CurrentMaterialIndex = (CurrentMaterialIndex + 1) % CosmeticMaterials.Num();
	}
	InteractAnim();
}

