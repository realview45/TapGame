// Fill out your copyright notice in the Description page of Project Settings.
//110
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/HA10GameplayAbility.h"
#include "HA10ProjectileSpell.generated.h"
//111
class AHA10Projectile;
/**
 * 
 */
UCLASS()
class AURA_API UHA10ProjectileSpell : public UHA10GameplayAbility
{
	GENERATED_BODY()

//110-2
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//111
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHA10Projectile>ProjectileClass;
};
