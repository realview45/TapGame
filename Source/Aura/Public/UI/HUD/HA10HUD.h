// Fill out your copyright notice in the Description page of Project Settings.
//32
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HA10HUD.generated.h"


class UHA10UserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AHA10HUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UHA10UserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHA10UserWidget> OverlayWidgetClass;

};
