// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase_HA10.h"
//13
#include "Interaction/EnemyInterface.h"

#include "HA10_Enemy.generated.h"



/**
 * 
 */
//13 public IEnemyInterface inherit
UCLASS()
class AURA_API AHA10_Enemy : public AMyCharacterBase_HA10, public IEnemyInterface
{
	GENERATED_BODY()

	//13
public:
	//15
	AHA10_Enemy();

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	//14-2
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

};
