// Fill out your copyright notice in the Description page of Project Settings.
//91
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "HA10AbilitySystemBPLibrary.generated.h"


class UOverlayHA10WidgetController;
//92-2
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UHA10AbilitySystemBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="HA10AbilitySystemLibraryWidgetController")
	static UOverlayHA10WidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	//92-2
	UFUNCTION(BlueprintPure, Category = "HA10AbilitySystemLibraryWidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};



