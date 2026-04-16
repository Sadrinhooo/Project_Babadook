// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StalkerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFootstep, FVector, FootstepLocation);

UCLASS()
class PROJEKT_BABADOOK_API AStalkerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnFootstep OnFootstep;
	
	void OnFootstepEvent() const;

};
