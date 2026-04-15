// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerCharacter.h"

void AStalkerCharacter::OnFootstepEvent() const
{
	FVector	FootstepLocation = GetActorLocation();
	OnFootstep.Broadcast(FootstepLocation);
}
