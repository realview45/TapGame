// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HA10PlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class AURA_API AHA10PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHA10PlayerController();
protected:
	virtual void BeginPlay() override;

private:
	//10 My
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	//UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> HA10Context;
};
