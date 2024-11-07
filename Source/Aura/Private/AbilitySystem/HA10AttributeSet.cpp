// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AttributeSet.h"

//25-2
#include "Net/UnrealNetwork.h"

UHA10AttributeSet::UHA10AttributeSet()
{
	//26 in accessors macro func InitHealth
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(200.f);
	InitMaxMana(200.f);
}
//25-2
void UHA10AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Health, COND_None, REPNOTIFY_Always);
	//25-3
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
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

void UHA10AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Mana, OldMana);
}

void UHA10AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, MaxMana, OldMaxMana);
}
