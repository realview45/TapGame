// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AttributeSet.h"

//25-2
#include "Net/UnrealNetwork.h"
//47
#include "GameplayEffectExtension.h"
//47-2
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"

UHA10AttributeSet::UHA10AttributeSet()
{
	//26 in accessors macro func InitHealth
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(100.f);
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
//46
void UHA10AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth: %f"), NewValue);
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);
	}
	if (Attribute == GetMaxManaAttribute())
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxMana: %f"), NewValue);
	}
}
//47
void UHA10AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//47-3
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	//WhatAttributesHasbeenChanged
	//if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Health from GetHealth(): %f"), GetHealth());
	//	UE_LOG(LogTemp, Warning, TEXT("Magnitude: %f"), Data.EvaluatedData.Magnitude);
	//}
	////47-2 Source = causer of the effect, Target = target of the effect(owner of thisAttributeSet)
	//const FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	//const UAbilitySystemComponent* SourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	//if (IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid() && SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	//{
	//	AActor* SourceAvatarActor = SourceASC->AbilityActorInfo->AvatarActor.Get();
	//	const AController* SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
	//	//if AAI has nullptr sourcecontroller, initialize pawn's controller
	//	if (SourceController == nullptr && SourceAvatarActor != nullptr)
	//	{
	//		if (const APawn* Pawn = Cast<APawn>(SourceAvatarActor))
	//		{
	//			SourceController = Pawn->GetController();
	//		}
	//	}
	//	if (SourceController)
	//	{
	//									//possessedpawn, cast avataractor to a character
	//		ACharacter* SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
	//	}
	//}
	//if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	//{
	//	AActor* TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	//	AController* TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	//	ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatarActor);
	//	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetAvatarActor);
	//}

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
//47-3
void UHA10AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties Props) const
{
	//47-2 Source = causer of the effect, Target = target of the effect(owner of thisAttributeSet)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		//if AAI has nullptr sourcecontroller, initialize pawn's controller
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
										//possessedpawn, cast avataractor to a character
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
