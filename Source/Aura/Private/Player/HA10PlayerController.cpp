// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerController.h"

#include "EnhancedInputSubsystems.h"

AHA10PlayerController::AHA10PlayerController()
{
	bReplicates = true;

}

void AHA10PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(HA10Context);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(HA10Context, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);


}
