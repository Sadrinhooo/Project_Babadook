// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "PaperNote.generated.h"

UCLASS()
class PROJEKT_BABADOOK_API APaperNote : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaperNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector NoteInitLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* NoteTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> NoteWidgetClass;
	
	UPROPERTY()
	FString InteractPrompt = "";
	
	//Functions
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();
	
	virtual void Interact(ACharacter* Interactor) override
	{
		this->OnInteract();
	}
	
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
