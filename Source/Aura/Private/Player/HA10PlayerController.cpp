// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerController.h"

#include "EnhancedInputSubsystems.h"
//11 102c
//#include "EnhancedInputComponent.h"
//102
#include "Input/HA10InputComponent.h"
//14
#include "Interaction/EnemyInterface.h"

AHA10PlayerController::AHA10PlayerController()
{
	bReplicates = true;

}
//14
void AHA10PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime); 
	CursorTrace();
}

void AHA10PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(HA10Context);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//33-4
	//check(Subsystem);
	if (Subsystem)
	{
		Subsystem->AddMappingContext(HA10Context, 0);
	}
	//Subsystem->AddMappingContext(HA10Context, 0);

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

	//102
	UHA10InputComponent* HA10InputComponent = CastChecked<UHA10InputComponent>(InputComponent);
	//102c
	//UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	HA10InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHA10PlayerController::Move);
	//102
	HA10InputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);


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
//102
void AHA10PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//103-2c GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}
void AHA10PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//103-2c GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}
void AHA10PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//103-2c GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}
//103-2
UHA10AbilitySystemComponent* AHA10PlayerController::GetASC()
{
	if (HA10ASC == nullptr)
	{
		HA10ASC = Cast<UHA10AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return HA10ASC;
}
