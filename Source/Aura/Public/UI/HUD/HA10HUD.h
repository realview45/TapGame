// Fill out your copyright notice in the Description page of Project Settings.
//32
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HA10HUD.generated.h"

class UHA10UserWidget;

//33-2
class UOverlayHA10WidgetController;
struct FWidgetControllerParams;

//33-3
class UAttributeSet;
class UAbilitySystemComponent;

//92
class UAttributeMenuWidgetController;

/**
 * 
 */
UCLASS()
class AURA_API AHA10HUD : public AHUD
{
	GENERATED_BODY()
public:
	//33-2
	UOverlayHA10WidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	//92
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	//33-3
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

//protected:
	//virtual void BeginPlay() override;

private:
	//92 public to private
	UPROPERTY()
	TObjectPtr<UHA10UserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHA10UserWidget> OverlayWidgetClass;

	//33-2
	UPROPERTY()
	TObjectPtr<UOverlayHA10WidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayHA10WidgetController> OverlayWidgetControllerClass;

	//92
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

};
