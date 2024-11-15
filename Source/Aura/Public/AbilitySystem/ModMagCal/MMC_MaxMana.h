// Fill out your copyright notice in the Description page of Project Settings.
//74-3
#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_MaxMana();
	//get effectspec and will calculate
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	FGameplayEffectAttributeCaptureDefinition IntDef;
};
