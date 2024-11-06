// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HA10_Character.h"
//12
#include "GameFramework/CharacterMovementComponent.h"
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
