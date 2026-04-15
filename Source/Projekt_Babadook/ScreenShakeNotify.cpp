// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenShakeNotify.h"

#include "StalkerCharacter.h"


void UScreenShakeNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
const FAnimNotifyEventReference& EventReference)
{
	AActor* OwnerActor = (MeshComp->GetOwner());
	if (const AStalkerCharacter* Stalker = Cast<AStalkerCharacter>(OwnerActor))
	{
		Stalker->OnFootstepEvent();
	}
	
	Super::Notify(MeshComp, Animation, EventReference);
}
