// Fill out your copyright notice in the Description page of Project Settings.
//87

#include "HA10AssetManager.h"
#include "HA10GameplayTags.h"
//118-3
//#include "AbilitySystemGlobals.h"

UHA10AssetManager& UHA10AssetManager::Get()
{
	check(GEngine);

	UHA10AssetManager* HA10AssetManager = Cast<UHA10AssetManager>(GEngine->AssetManager);
	return *HA10AssetManager;
}

void UHA10AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FHA10GameplayTags::InitializeNativeGameplayTags();
	//118-3 Initialize somethings including TargetData
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
