// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/HA10UserWidget.h"
//Setter of widgetController
void UHA10UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

