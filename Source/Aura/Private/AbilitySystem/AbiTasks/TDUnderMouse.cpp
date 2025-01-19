// Fill out your copyright notice in the Description page of Project Settings. 115


#include "AbilitySystem/AbiTasks/TDUnderMouse.h"
//117-2
#include "AbilitySystemComponent.h"

UTDUnderMouse* UTDUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTDUnderMouse* MyObj = NewAbilityTask<UTDUnderMouse>(OwningAbility);
	return MyObj;
}

//115-3
void UTDUnderMouse::Activate()
{
	//117-2
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//TODO: We are on the server, so listen for target data.
	}


}
//117
void UTDUnderMouse::SendMouseCursorData()
{
	//117-3
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	//117-2 Activate() to SendMouseCursorData() to cation);
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	//117-2c ValidData.Broadcast(CursorHit.Location);
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);
	FGameplayTag ApplicationTag;
	AbilitySystemComponent->ServerSetReplicatedTargetData(//Sending Target Data
		GetAbilitySpecHandle(), 
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(), 
		AbilitySystemComponent->ScopedPredictionKey);//ScopedPredictionKey is variable updated 

	//117-3 if Ability not still Active, this will be prevent broadcast
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);//modify Delegate type Vector to DataHandle
	}
}
