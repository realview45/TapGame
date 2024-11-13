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
	/*Enemy Interface*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/*endEnemyInterface*/
	//73-2
	/*CombatInterface*/
	virtual int32 GetPlayerLevel() override;
	/*endCombatInterface*/
	//14-2
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	//23
	virtual void BeginPlay() override;
	//54
	virtual void InitAbilityActorInfo() override;

	//73-2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;


};
