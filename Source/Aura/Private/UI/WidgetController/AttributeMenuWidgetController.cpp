// Fill out your copyright notice in the Description page of Project Settings.
//90

#include "UI/WidgetController/AttributeMenuWidgetController.h"
//93
#include "AbilitySystem/HA10AttributeSet.h"
#include "AbilitySystem/Data/MyAttributeInfo.h"
//#include "HA10GameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//no need to super because it's empty
	//96 this return delegate
	UHA10AttributeSet* AS = CastChecked<UHA10AttributeSet>(AttributeSet);
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetStrengthAttribute())
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				//96-2
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
				//96-2c
				//FHA10AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
				//Info.AttributeValue = Pair.Value().GetNumericValue(AS);
				//AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetStrengthAttribute()).AddLambda(
	//	[]
	//	{

	//	}
	//);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//93 95StrengthInfo
	UHA10AttributeSet* AS = CastChecked<UHA10AttributeSet>(AttributeSet);
	check(AttributeInfo);
	//95c
	//FHA10AttributeInfo StrengthInfo = AttributeInfo->FindAttributeInfoForTag(FHA10GameplayTags::Get().Attributes_Primary_Strength);
	//StrengthInfo.AttributeValue = AS->GetStrength();
	//AttributeInfoDelegate.Broadcast(StrengthInfo);
	//FHA10AttributeInfo IntelligenceInfo = AttributeInfo->FindAttributeInfoForTag(FHA10GameplayTags::Get().Attributes_Primary_Intelligence);
	//IntelligenceInfo.AttributeValue = AS->GetIntelligence();
	//AttributeInfoDelegate.Broadcast(IntelligenceInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		//96-2
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
		//96-2c
		//FHA10AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		////95-2c Value = delegate to funcpointer 95-2
		////Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AS);
		//Info.AttributeValue = Pair.Value().GetNumericValue(AS);

		//AttributeInfoDelegate.Broadcast(Info);
	}
}
//96-2
void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FHA10AttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	//95-2c Value = delegate to funcpointer 95-2
	//Info.AttributeValue = Pair.Value.Execute().GetNumericValue(AS);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
