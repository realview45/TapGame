// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HA10HUD.h"

//33-2
#include "UI/Widgets/HA10UserWidget.h"
#include "UI/WidgetController/OverlayHA10WidgetController.h"
UOverlayHA10WidgetController* AHA10HUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayHA10WidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//35
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

//33-3
void AHA10HUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	//check and print formatic string crash log if check fails
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_HA10HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_HA10HUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UHA10UserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayHA10WidgetController* OverlayHAWidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(OverlayHAWidgetController);
	//34 
	OverlayHAWidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
//void AHA10HUD::BeginPlay()
//{
//	Super::BeginPlay();
//
//	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
//	Widget->AddToViewport();
//}
