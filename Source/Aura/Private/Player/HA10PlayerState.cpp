// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerState.h"
//21-2
#include "AbilitySystem/HA10AbilitySystemComponent.h"
#include "AbilitySystem/HA10AttributeSet.h"
AHA10PlayerState::AHA10PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UHA10AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UHA10AttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}
//21-4
UAbilitySystemComponent* AHA10PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
