// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerState.h"
//21-2
#include "AbilitySystem/HA10AbilitySystemComponent.h"
#include "AbilitySystem/HA10AttributeSet.h"
//73
#include "Net/UnrealNetwork.h"

AHA10PlayerState::AHA10PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UHA10AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//22
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UHA10AttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}
//73
void AHA10PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHA10PlayerState, Level);
}
//21-4
UAbilitySystemComponent* AHA10PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
//73
void AHA10PlayerState::OnRep_Level(int32 OldLevel)
{
}
