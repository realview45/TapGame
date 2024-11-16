// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
struct FHA10GameplayTags
{
public:
	static const FHA10GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Secondary_Armor;

protected:

private:
	static FHA10GameplayTags GameplayTags;
};