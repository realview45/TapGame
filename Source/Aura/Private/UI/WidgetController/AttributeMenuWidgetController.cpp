// Fill out your copyright notice in the Description page of Project Settings.
//90

#include "UI/WidgetController/AttributeMenuWidgetController.h"
//93
#include "AbilitySystem/HA10AttributeSet.h"
#include "AbilitySystem/Data/MyAttributeInfo.h"
#include "HA10GameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//no need to super because it's empty
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//93
	UHA10AttributeSet* AS = CastChecked<UHA10AttributeSet>(AttributeSet);
	check(AttributeInfo);
	FHA10AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FHA10GameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
