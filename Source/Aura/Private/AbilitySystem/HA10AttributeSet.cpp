// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AttributeSet.h"
//25
#include "AbilitySystemComponent.h"
//25-2
#include "Net/UnrealNetwork.h"

UHA10AttributeSet::UHA10AttributeSet()
{

}
//25-2
void UHA10AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Health, COND_None, REPNOTIFY_Always);
	//25-3
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHA10AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Health, OldHealth);
}
//25-3
void UHA10AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, MaxHealth, OldMaxHealth);
}
