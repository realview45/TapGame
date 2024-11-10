// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HA10AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHA10AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	//54
public:
	void AbilityActorInfoSet();
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);


};
