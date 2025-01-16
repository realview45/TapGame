// Fill out your copyright notice in the Description page of Project Settings.
//110

#include "AbilitySystem/Abilities/HA10ProjectileSpell.h"

//110-2
#include "Kismet/KismetSystemLibrary.h"
void UHA10ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Yellow, 3);
}
