// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacterBase_HA10.h"

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

// Called every frame
void AMyCharacterBase_HA10::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterBase_HA10::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

