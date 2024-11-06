// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HA10_Enemy.h"
//15
#include "Aura/Aura.h"
//21
#include "AbilitySystem/HA10AbilitySystemComponent.h"
#include "AbilitySystem/HA10AttributeSet.h"

AHA10_Enemy::AHA10_Enemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//21
	AbilitySystemComponent = CreateDefaultSubobject<UHA10AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UHA10AttributeSet>("AttributeSet");
}
//13
void AHA10_Enemy::HighlightActor()
{
	bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon2->SetRenderCustomDepth(true);
	Weapon2->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}
void AHA10_Enemy::UnHighlightActor()
{
	bHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	Weapon2->SetRenderCustomDepth(false);

}
