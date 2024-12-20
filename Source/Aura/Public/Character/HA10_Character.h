// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase_HA10.h"
#include "HA10_Character.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AHA10_Character : public AMyCharacterBase_HA10
{
	GENERATED_BODY()

//12
public:
	AHA10_Character();
	//24
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	//73-2
	/*CombatInterface*/
	virtual int32 GetPlayerLevel() override;
	/*endCombatInterface*/


//24 54override
private:
	void InitAbilityActorInfo() override;
};
