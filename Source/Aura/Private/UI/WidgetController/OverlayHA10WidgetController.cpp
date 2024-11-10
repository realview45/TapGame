// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayHA10WidgetController.h"
//34
#include "AbilitySystem/HA10AttributeSet.h"
//56
#include "AbilitySystem/HA10AbilitySystemComponent.h"

void UOverlayHA10WidgetController::BroadcastInitialValues()
{
	//OnHealthChanged.Broadcast(100.f);
	const UHA10AttributeSet* HA10AttributeSet = CastChecked<UHA10AttributeSet>(AttributeSet);
	//Delegate initialize using Accessor macro
	OnHealthChanged.Broadcast(HA10AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(HA10AttributeSet->GetMaxHealth());

	//36
	OnManaChanged.Broadcast(HA10AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(HA10AttributeSet->GetMaxMana());

}
//35
void UOverlayHA10WidgetController::BindCallbacksToDependencies()
{
	const UHA10AttributeSet* HA10AttributeSet = CastChecked<UHA10AttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayHA10WidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayHA10WidgetController::MaxHealthChanged);

	//36
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayHA10WidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayHA10WidgetController::MaxManaChanged);
	//56
	Cast<UHA10AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) 
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				//Tag.GetTageName() returns FName, Tag.ToString() returns FString put * to convert a wide character array(ArrayofTchar)
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);

				//58 specify the type(T) beacause this is the template function
				FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
			}
		}
	);
}
//35-2
void UOverlayHA10WidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayHA10WidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
//36
void UOverlayHA10WidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}
void UOverlayHA10WidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
