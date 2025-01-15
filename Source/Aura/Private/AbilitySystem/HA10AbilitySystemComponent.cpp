// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/HA10AbilitySystemComponent.h"
//87-5
#include "HA10GameplayTags.h"
//103
#include "AbilitySystem/HA10GameplayAbility.h"
//54
void UHA10AbilitySystemComponent::AbilityActorInfoSet()
{
	//108-4 once this delegate broadcast on the server it will be called in a server and executed on the client
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UHA10AbilitySystemComponent::ClientEffectApplied);
	////87-5 88c
	//const FHA10GameplayTags& GameplayTags = FHA10GameplayTags::Get();
	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	10.f,
	//	FColor::Orange,
	//	FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
	//);
	////88
	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	10.f,
	//	FColor::Orange,
	//	FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_ManaRegeneration.ToString())
	//);

}
//98-2
void UHA10AbilitySystemComponent::AddCharacAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility>AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec  AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		//103
		if (const UHA10GameplayAbility* HA10Ability = Cast<UHA10GameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(HA10Ability->StartupInputTag);
			GiveAbility(AbilitySpec);
		}


		//98-2c GiveAbility(AbilitySpec);
		//103c GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

//103-2
void UHA10AbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	//103-3
	if (!InputTag.IsValid()) return;
	for (auto& AbilitySpec : GetActivatableAbilities())//looping through our activatable abilities
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) 
		{
			AbilitySpecInputPressed(AbilitySpec);//customize ability
			if (!AbilitySpec.IsActive())//activate ability
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}
void UHA10AbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)//will know input is released
{
	if (!InputTag.IsValid())return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())//looping through our activatable abilities
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))//if correct Ability
		{
			AbilitySpecInputReleased(AbilitySpec);//customize ability

		}
	}
}
//108-4 EffectApplied > ClientEffectApplied_Implementation
void UHA10AbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
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
