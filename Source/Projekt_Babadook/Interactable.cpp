// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

bool IInteractable::IsLocked()
{
	return false;
}

const FVector IInteractable::GetInteractableLocation()
{
	return FVector::ZeroVector; // all classes get this unless they override
}