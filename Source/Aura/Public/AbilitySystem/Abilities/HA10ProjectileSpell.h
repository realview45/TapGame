// Fill out your copyright notice in the Description page of Project Settings.
//110
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/HA10GameplayAbility.h"
#include "HA10ProjectileSpell.generated.h"
//111
class AHA10Projectile;
//122-2my
class UNiagaraSystem;
//124
class UGameplayEffect;
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
	//114 120 const FVector& ProjectileTargetLocation
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	//111
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AHA10Projectile> ProjectileClass;
	//122-2my
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ProjectileEffectClass;

	//124
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

};
