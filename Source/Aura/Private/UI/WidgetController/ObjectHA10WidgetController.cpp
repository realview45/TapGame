// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ObjectHA10WidgetController.h"

void UObjectHA10WidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
//34
void UObjectHA10WidgetController::BroadcastInitialValues()
{
}

void UObjectHA10WidgetController::BindCallbacksToDependencies()
{

}
