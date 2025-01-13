// Fill out your copyright notice in the Description page of Project Settings.
//101
#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
//101-2
#include "HA10InputConfig.h"

#include "HA10InputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UHA10InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

	//101-2
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFunctype, typename HeldFuncType>
	void BindAbilityActions(const UHA10InputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFunctype ReleasedFunc, HeldFuncType HeldFunc);

};

//101-2
template<class UserClass, typename PressedFuncType, typename ReleasedFunctype, typename HeldFuncType>
inline void UHA10InputComponent::BindAbilityActions(const UHA10InputConfig* InputConfig, UserClass* Object, 
	PressedFuncType PressedFunc, ReleasedFunctype ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	for (const FHA10InputAction& Action : InputConfig->AbilityInputActions) {
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
