// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HA10_Character.h"
//12
#include "GameFramework/CharacterMovementComponent.h"

//24
#include "AbilitySystemComponent.h"
#include "Player/HA10PlayerState.h"

//33-4
#include "Player/HA10PlayerController.h"
#include "UI/HUD/HA10HUD.h"

AHA10_Character::AHA10_Character()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
//24
void AHA10_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init ability actor info for the server
	InitAbilityActorInfo();
}
void AHA10_Character::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability actor info for the client
	InitAbilityActorInfo();
}

void AHA10_Character::InitAbilityActorInfo()
{
	AHA10PlayerState* HA10PlayerState = GetPlayerState<AHA10PlayerState>();
	check(HA10PlayerState);
	HA10PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(HA10PlayerState, this);
	AbilitySystemComponent = HA10PlayerState->GetAbilitySystemComponent();
	AttributeSet = HA10PlayerState->GetAttributeSet();

	//33-4
	if (AHA10PlayerController* HA10PlayerController = Cast<AHA10PlayerController>(GetController()))
	{
		if (AHA10HUD* HA10HUD = Cast<AHA10HUD>(HA10PlayerController->GetHUD()))
		{
			HA10HUD->InitOverlay(HA10PlayerController, HA10PlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}


