// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//21-3
#include "AbilitySystemInterface.h"
#include "MyCharacterBase_HA10.generated.h"
//66
class UGameplayEffect;
//21-3
class UAbilitySystemComponent;
class UAttributeSet;

//21-3 inherit IAbilitySystemInterface 
UCLASS()
class AURA_API AMyCharacterBase_HA10 : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase_HA10();
	//21-3
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//21
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//07-1 ���Ͽ� ������������ Tracking�̰����ϰ� lazy loading�� ������Pointer(UE)�� ���� 
	//Weapon�̶�� ���̷�Ż�޽�������Ʈ����
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon2;

	//54
	virtual void InitAbilityActorInfo();
	//66
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	void InitializePrimaryAttributes() const;


};
