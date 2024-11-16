// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AbilitySystemComponent.h"
//87-5
#include "HA10GameplayTags.h"
//54
void UHA10AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UHA10AbilitySystemComponent::EffectApplied);
	//87-5
	const FHA10GameplayTags& GameplayTags = FHA10GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
	);

}
void UHA10AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, 
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, FString("Effect Applied!"));
	//55
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//56
	EffectAssetTags.Broadcast(TagContainer);
	//AbilitySystemComponent hasn't DebugMessage
	//for (const FGameplayTag& Tag : TagContainer)
	//{
	//	//TODO:Broadcast the tah to the the WidgetController
	//	//Tag.GetTageName() returns FName, Tag.ToString() returns FString put * to convert a wide character array(ArrayofTchar)
	//	const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
	//	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	//}
}
