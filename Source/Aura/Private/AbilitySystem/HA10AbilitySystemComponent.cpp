// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AbilitySystemComponent.h"
//54
void UHA10AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UHA10AbilitySystemComponent::EffectApplied);
}
void UHA10AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied!"));
}
