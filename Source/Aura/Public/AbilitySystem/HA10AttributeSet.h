// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "HA10AttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHA10AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

//25
public:
	UHA10AttributeSet();
	//25-2
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
};
