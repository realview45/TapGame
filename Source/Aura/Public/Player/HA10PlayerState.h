// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
//21-4
#include "AbilitySystemInterface.h"

#include "HA10PlayerState.generated.h"


//21-4
class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
//21-4
class AURA_API AHA10PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHA10PlayerState();
	//21-4
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
//21-2
protected:
	//65 VisibleAnywhere
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
