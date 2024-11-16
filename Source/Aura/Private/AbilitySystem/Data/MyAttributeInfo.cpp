// Fill out your copyright notice in the Description page of Project Settings.
//89

#include "AbilitySystem/Data/MyAttributeInfo.h"

FHA10AttributeInfo UMyAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTagg, bool bLogNotFound) const
{
	for (const FHA10AttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTagg))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), 
			*AttributeTagg.ToString(), *GetNameSafe(this));
	}

	return FHA10AttributeInfo();
}
