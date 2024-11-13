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
	//73
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//21-4
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	//73-3 because level is private(73), we need to set getter() in public section Forceinline = fast runtime
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	

//21-2
protected:
	//65 VisibleAnywhere
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

//73
private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
