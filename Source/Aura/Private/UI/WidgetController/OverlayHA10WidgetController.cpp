// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayHA10WidgetController.h"
//34
#include "AbilitySystem/HA10AttributeSet.h"
void UOverlayHA10WidgetController::BroadcastInitialValues()
{
	//OnHealthChanged.Broadcast(100.f);
	const UHA10AttributeSet* HA10AttributeSet = CastChecked<UHA10AttributeSet>(AttributeSet);
	//Delegate initialize using Accessor macro
	OnHealthChanged.Broadcast(HA10AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(HA10AttributeSet->GetMaxHealth());

}
//35
void UOverlayHA10WidgetController::BindCallbacksToDependencies()
{
	const UHA10AttributeSet* HA10AttributeSet = CastChecked<UHA10AttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayHA10WidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		HA10AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayHA10WidgetController::MaxHealthChanged);
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
