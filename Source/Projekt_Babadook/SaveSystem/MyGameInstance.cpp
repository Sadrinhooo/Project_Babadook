// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

bool UMyGameInstance::IsItemCollected(FGameplayTag ItemTag) const
{
	return CollectedItems.HasTag(ItemTag);
}

void UMyGameInstance::CollectItem(FGameplayTag ItemTag)
{
	CollectedItems.AddTag(ItemTag);
}
