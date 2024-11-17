// Fill out your copyright notice in the Description page of Project Settings.
//91
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "HA10AbilitySystemBPLibrary.generated.h"


class UOverlayHA10WidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UHA10AbilitySystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static UOverlayHA10WidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);


};



