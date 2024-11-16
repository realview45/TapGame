// Fill out your copyright notice in the Description page of Project Settings.
//87
#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
struct FHA10GameplayTags
{
public:
	static const FHA10GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	//88
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	//88
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;

protected:

private:
	static FHA10GameplayTags GameplayTags;
};