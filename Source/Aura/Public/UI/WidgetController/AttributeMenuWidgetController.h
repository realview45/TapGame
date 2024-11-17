// Fill out your copyright notice in the Description page of Project Settings.
//90
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ObjectHA10WidgetController.h"

//93
#include "AbilitySystem/HA10AttributeSet.h"
#include "AbilitySystem/Data/MyAttributeInfo.h"
#include "HA10GameplayTags.h"

#include "AttributeMenuWidgetController.generated.h"

//93 define FAttributeInfoSignature
struct FHA10AttributeInfo;
class UMyAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FHA10AttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UObjectHA10WidgetController
{
	GENERATED_BODY()
	
public:
	//HA10widget controller's function override 
	virtual void BindCallbacksToDependencies() override; //update variables
	virtual void BroadcastInitialValues() override; //initialize variables

	//93
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMyAttributeInfo>AttributeInfo;

};
