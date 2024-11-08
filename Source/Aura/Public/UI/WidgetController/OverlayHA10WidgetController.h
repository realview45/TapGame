// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ObjectHA10WidgetController.h"
#include "OverlayHA10WidgetController.generated.h"

//34
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
//34-2
UCLASS(BlueprintType, Blueprintable)


class AURA_API UOverlayHA10WidgetController : public UObjectHA10WidgetController
{
	GENERATED_BODY()

//34
public:
	virtual void BroadcastInitialValues() override;
	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnMaxHealthChanged;
};
