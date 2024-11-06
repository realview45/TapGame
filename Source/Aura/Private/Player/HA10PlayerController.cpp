// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerController.h"

#include "EnhancedInputSubsystems.h"
//11
#include "EnhancedInputComponent.h"

//14
#include "Interaction/EnemyInterface.h"

AHA10PlayerController::AHA10PlayerController()
{
	bReplicates = true;

}
//14
void AHA10PlayerController::PlayerTick(float DeltaTime)
{
	CursorTrace();
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
//11
void AHA10PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHA10PlayerController::Move);

}

void AHA10PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
//14
void AHA10PlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//B
			ThisActor->HighlightActor();
		}
		else
		{
			//A
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			//C
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				//D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//E
			}
		}
	}
}
