// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacterBase_HA10.h"
//66
#include "AbilitySystemComponent.h"

// Sets default values
AMyCharacterBase_HA10::AMyCharacterBase_HA10()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//07-2 CreateDefaultSubobject�� Fname(��Ʈ��)�� �޾Ƽ� "Weapon"�� �Է� (FString�� �̸� WideCharacter�� �Ͻ������� ��ȯ������ Fname�� �׳� �̻��·� ����)
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//07-3 Character Class���� ��ӵ� GetMesh()���, WeaponHandSocket�̸��� ���Ͽ� ���̱�, �ݸ�������
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//my08-1 Weapon�� ������ 2�� �޼�
	Weapon2 = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon2");
	Weapon2->SetupAttachment(GetMesh(), FName("WeaponHandSocket2"));
	Weapon2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
//21-3
UAbilitySystemComponent* AMyCharacterBase_HA10::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AMyCharacterBase_HA10::BeginPlay()
{
	Super::BeginPlay();

}
//71c
//// Called every frame
//void AMyCharacterBase_HA10::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void AMyCharacterBase_HA10::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
//54
void AMyCharacterBase_HA10::InitAbilityActorInfo()
{
}
//66 71-2c
//void AMyCharacterBase_HA10::InitializePrimaryAttributes() const
//{
//	check(IsValid(GetAbilitySystemComponent()));
//	check(DefaultPrimaryAttributes);
//	//get contexthandle
//	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
//	//get effectspec
//	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, ContextHandle);
//	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
//}
//71 71-2c
//void AMyCharacterBase_HA10::InitializeSecondaryAttributes() const
//{
//	check(IsValid(GetAbilitySystemComponent()));
//	check(DefaultSecondaryAttributes);
//	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
//	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultSecondaryAttributes, 1.f, ContextHandle);
//	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
//}
//71-2
void AMyCharacterBase_HA10::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	//74-2 substract const and AddSourceObject()
	//const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
void AMyCharacterBase_HA10::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}

