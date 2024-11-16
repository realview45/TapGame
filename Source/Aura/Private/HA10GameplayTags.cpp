// Fill out your copyright notice in the Description page of Project Settings.
//86

#include "HA10GameplayTags.h"
#include "GameplayTagsManager.h"

FHA10GameplayTags FHA10GameplayTags::GameplayTags;

void FHA10GameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
}

//86c
////Constructer
//HA10GameplayTags::HA10GameplayTags()
//{
//}
////DeConstructer
//HA10GameplayTags::~HA10GameplayTags()
//{
//}


