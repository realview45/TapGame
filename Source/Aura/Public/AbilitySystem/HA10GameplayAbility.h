// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HA10GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHA10GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	//103
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

};
