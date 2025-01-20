// Fill out your copyright notice in the Description page of Project Settings. 115

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TDUnderMouse.generated.h"

//115-2 117-3 FVector to FGameplayAbilityTargetDataHandle
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UTDUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", 
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTDUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	//115-2
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

	//115-3
private:
	virtual void Activate() override;
	//117
	void SendMouseCursorData();
	//118
	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
