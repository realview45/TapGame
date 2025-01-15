// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HA10PlayerController.h"

#include "EnhancedInputSubsystems.h"
//11 102c
//#include "EnhancedInputComponent.h"
//102
#include "Input/HA10InputComponent.h"
//14
#include "Interaction/EnemyInterface.h"
//105-2
#include "HA10GameplayTags.h"
#include "Components/SplineComponent.h"
//106
#include "NavigationSystem.h"
#include "NavigationPath.h"

AHA10PlayerController::AHA10PlayerController()
{
	bReplicates = true;

	//105
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}
//14
void AHA10PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime); 
	CursorTrace();

	//107
	AutoRun();
}
//107
void AHA10PlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	//107 spline near pawn
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
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
	//108c FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	//108-2
	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
	//108-2c
	//if (LastActor == nullptr)
	//{
	//	if (ThisActor != nullptr)
	//	{
	//		//B
	//		ThisActor->HighlightActor();
	//	}
	//	else
	//	{
	//		//A
	//	}
	//}
	//else
	//{
	//	if (ThisActor == nullptr)
	//	{
	//		//C
	//		LastActor->UnHighlightActor();
	//	}
	//	else
	//	{
	//		if (LastActor != ThisActor)
	//		{
	//			//D
	//			LastActor->UnHighlightActor();
	//			ThisActor->HighlightActor();
	//		}
	//		else
	//		{
	//			//E
	//		}
	//	}
	//}
}
//102
void AHA10PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//103-2c 
	/*GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());*/
	//105-2
	if (InputTag.MatchesTagExact(FHA10GameplayTags::Get().InputTag_LMB)) {
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}
void AHA10PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//103-2c 
	/*GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());*/
	if (GetASC() == nullptr) return;
	//106c GetASC()->AbilityInputTagReleased(InputTag);
	//106
	if (!InputTag.MatchesTagExact(FHA10GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if (bTargeting)
	{
		if (GetASC())GetASC()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					//108-3c DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];//107 initialize path's last point
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}
void AHA10PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	//103-2c 
	//GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());
	//105-2
	if (!InputTag.MatchesTagExact(FHA10GameplayTags::Get().InputTag_LMB)) {//not left mouse button
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);//activate ability(let abilitySC to know held)
		return;//inform once for performance
	}
	if (bTargeting)//left mouse button and hover actor(enemy)
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		//108c FHitResult Hit;
		//if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		//108
		if (CursorHit.bBlockingHit)CachedDestination = CursorHit.ImpactPoint;//108 Hit to CursorHit

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
	//105-2c
	//if (GetASC() == nullptr) return;
	//GetASC()->AbilityInputTagHeld(InputTag);
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

