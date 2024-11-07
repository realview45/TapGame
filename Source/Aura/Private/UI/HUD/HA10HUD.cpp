// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/HA10HUD.h"

#include "UI/Widgets/HA10UserWidget.h"

void AHA10HUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
