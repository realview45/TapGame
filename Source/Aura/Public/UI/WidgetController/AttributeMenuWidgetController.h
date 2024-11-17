// Fill out your copyright notice in the Description page of Project Settings.
//90
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ObjectHA10WidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

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
};
