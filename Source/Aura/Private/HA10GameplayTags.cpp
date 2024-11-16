// Fill out your copyright notice in the Description page of Project Settings.


#include "HA10GameplayTags.h"
#include "GameplayTagsManager.h"

FHA10GameplayTags FHA10GameplayTags::GameplayTags;

void FHA10GameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
}