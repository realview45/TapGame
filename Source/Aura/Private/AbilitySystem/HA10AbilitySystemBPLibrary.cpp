// Fill out your copyright notice in the Description page of Project Settings.
//91

#include "AbilitySystem/HA10AbilitySystemBPLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/HA10PlayerState.h"
#include "UI/HUD/HA10HUD.h"
#include "UI/WidgetController/ObjectHA10WidgetController.h"




UOverlayHA10WidgetController* UHA10AbilitySystemBPLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHA10HUD* HA10HUD = Cast<AHA10HUD>(PC->GetHUD()))
		{
			AHA10PlayerState* PS = PC->GetPlayerState<AHA10PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return HA10HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

