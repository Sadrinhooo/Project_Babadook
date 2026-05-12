// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoPuzzle.h"


void APianoPuzzle::Interact(ACharacter* Interactor)
{
	OnInteract();
}

const FString& APianoPuzzle::GetInteractPrompt(ACharacter* Interactor)
{
	return InteractPrompt;
}
