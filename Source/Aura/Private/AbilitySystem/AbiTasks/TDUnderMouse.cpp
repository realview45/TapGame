// Fill out your copyright notice in the Description page of Project Settings. 115


#include "AbilitySystem/AbiTasks/TDUnderMouse.h"


UTDUnderMouse* UTDUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTDUnderMouse* MyObj = NewAbilityTask<UTDUnderMouse>(OwningAbility);
	return MyObj;
}