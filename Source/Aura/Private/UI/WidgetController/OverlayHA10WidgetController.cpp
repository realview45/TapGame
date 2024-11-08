// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayHA10WidgetController.h"
//34
#include "AbilitySystem/HA10AttributeSet.h"
void UOverlayHA10WidgetController::BroadcastInitialValues()
{
	//OnHealthChanged.Broadcast(100.f);
	const UHA10AttributeSet* HA10AttributeSet = CastChecked<UHA10AttributeSet>(AttributeSet);
	//Delegate initialize
	OnHealthChanged.Broadcast(HA10AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(HA10AttributeSet->GetMaxHealth());
}
