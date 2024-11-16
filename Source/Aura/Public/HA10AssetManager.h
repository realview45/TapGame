// Fill out your copyright notice in the Description page of Project Settings.
//87
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HA10AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHA10AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UHA10AssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
	
};
