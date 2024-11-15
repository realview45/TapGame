// Fill out your copyright notice in the Description page of Project Settings.
//74-3
#include "AbilitySystem/ModMagCal/MMC_MaxMana.h"

#include "AbilitySystem/HA10AttributeSet.h"
#include "Interaction/CombatInterface.h"
UMMC_MaxMana::UMMC_MaxMana()
{
	//HA10AttributeSet.h's Accessor can use GetIntelligenceAttribute()
	IntDef.AttributeToCapture = UHA10AttributeSet::GetIntelligenceAttribute();
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Int = 0.f;
	GetCapturedAttributeMagnitude(IntDef, Spec, EvaluationParameters, Int);
	Int = FMath::Max<float>(Int, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	//custom calculation maxHealth!
	return 50.f + 2.5f * Int + 15.f * PlayerLevel;
}
