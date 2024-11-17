// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AttributeSet.h"

//25-2
#include "Net/UnrealNetwork.h"
//47
#include "GameplayEffectExtension.h"
//47-2
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
//95
#include "HA10GameplayTags.h"

UHA10AttributeSet::UHA10AttributeSet()
{
	//75c
	////26 in accessors macro func InitHealth
	//InitHealth(50.f);
	//InitMaxHealth(100.f);
	//InitMana(100.f);
	//InitMaxMana(200.f);
	//95
	const FHA10GameplayTags& GameplayTags = FHA10GameplayTags::Get();
	//95-2
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);

	//95-2c
	//FAttributeSignature StrengthDelegate;
	//StrengthDelegate.BindStatic(GetStrengthAttribute);//bind static func
	//TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, StrengthDelegate);
	//FAttributeSignature IntelligenceDelegate;
	//IntelligenceDelegate.BindStatic(GetIntelligenceAttribute);//bind static func
	//TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, IntelligenceDelegate);
	//95-2c how to use funcpointer
	//FunctionPointer = GetIntelligenceAttribute;
	//FGameplayAttribute Attribute = FunctionPointer();
	//95-3c randomfunction ex
	//RandomFunctionPointer = RandomFunction; float F = RandomFunctionPointer(0, 0.f, 0);
}
//25-2
void UHA10AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//65
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	//70
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHA10AttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

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
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Magenta, FString::Printf(TEXT("Health: %f"), NewValue));
		//UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewValue);
	}
	if (Attribute == GetMaxHealthAttribute())
	{
		//UE_LOG(LogTemp, Warning, TEXT("MaxHealth: %f"), NewValue);
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, FString::Printf(TEXT("Mana: %f"), NewValue));
		//UE_LOG(LogTemp, Warning, TEXT("Mana: %f"), NewValue);
	}
	if (Attribute == GetMaxManaAttribute())
	{
		//UE_LOG(LogTemp, Warning, TEXT("MaxMana: %f"), NewValue);
	}
}
//47
void UHA10AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//47-3
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	//64 clamp one more time
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::ClampAngle(GetHealth(), 0.f, GetMaxHealth()));
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, FString::Printf(TEXT("Health: %f"), GetHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::ClampAngle(GetMana(), 0.f, GetMaxMana()));
		GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Blue, FString::Printf(TEXT("Mana: %f"), GetMana()));
	}

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
//65
void UHA10AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Strength, OldStrength);
}
void UHA10AttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Intelligence, OldIntelligence);
}
void UHA10AttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Resilience, OldResilience);
}
void UHA10AttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Vigor, OldVigor);
}
//70
void UHA10AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, Armor, OldArmor);
}
void UHA10AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, ArmorPenetration, OldArmorPenetration);
}
void UHA10AttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, BlockChance, OldBlockChance);
}
void UHA10AttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, CriticalHitChance, OldCriticalHitChance);
}
void UHA10AttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
void UHA10AttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
void UHA10AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, HealthRegeneration, OldHealthRegeneration);
}
void UHA10AttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHA10AttributeSet, ManaRegeneration, OldManaRegeneration);
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
