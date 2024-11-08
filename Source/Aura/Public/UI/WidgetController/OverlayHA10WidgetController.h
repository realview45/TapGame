// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ObjectHA10WidgetController.h"
//35
#include "AbilitySystemComponent.h"

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

	//35
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category= "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnMaxHealthChanged;

	//35-2
protected:
	//FOnAttributeChangeData delegate already exists in AbilitySystemComponent.h
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

};
