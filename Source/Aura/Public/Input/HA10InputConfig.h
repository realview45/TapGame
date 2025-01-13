// Fill out your copyright notice in the Description page of Project Settings.
//100
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//100-2
#include "GameplayTagContainer.h"

#include "HA10InputConfig.generated.h"

//100-2
USTRUCT(BlueprintType)
struct FHA10InputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class AURA_API UHA10InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
	//100-2
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FHA10InputAction> AbilityInputActions;

};
