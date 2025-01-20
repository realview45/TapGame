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
		//118-2
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		//118 there is a delegate broadcast we've set, we can get that Delegate through ASC
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), 
			GetActivationPredictionKey()).AddUObject(this, &UTDUnderMouse::OnTargetDataReplicatedCallBack);
			//we need to know prediction key associated with target data
			//in order to know that info, we need to func with spechandle for the ability associate with specific task
			//this func give the delegate so we can bind callback func
		//118-2														if we don't call this delegate means it hasn't reached server yet
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();//so we will be waiting data to comeback (set waiting flag and tells ability waiting for playerdata 
		}
	}
}z
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
//118 this func would called replicated data has been received in that case we need broadcast 
// it so that our ability task in the gameplayability will have its valid data execution pin excuted
void UTDUnderMouse::OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	//notify ASC knows that data has been recieved(no need to keep it cached anymore)
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
