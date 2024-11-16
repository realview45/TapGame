// Fill out your copyright notice in the Description page of Project Settings.
//86
#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

/**HA10GameplayTags
 * Singleton containing native GameplayTags
 */
struct FHA10GameplayTags
{
public:
	static const FHA10GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
protected:

private:
	static FHA10GameplayTags GameplayTags;
};

//86c
//class AURA_API HA10GameplayTags
//{
//public:
//	HA10GameplayTags();
//	~HA10GameplayTags();
//};
