// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HA10AbilitySystemComponent.generated.h"

//56 Im gonna call this GameplayTagContainer
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

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
	//56
	FEffectAssetTags EffectAssetTags;
	//98-2
	void AddCharacAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	//103-2
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);


//54
protected:
	UFUNCTION(Client, Reliable)//108-4 Client RPC
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);


};
