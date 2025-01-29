// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//21-3
#include "AbilitySystemInterface.h"
//73
#include "Interaction/CombatInterface.h"


#include "MyCharacterBase_HA10.generated.h"
//66
class UGameplayEffect;
//21-3
class UAbilitySystemComponent;
class UAttributeSet;
//98
class UGameplayAbility;

//21-3 inherit IAbilitySystemInterface 73-2 ICombatInterface
UCLASS()
class AURA_API AMyCharacterBase_HA10 : public ACharacter, public IAbilitySystemInterface , public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterBase_HA10();
	//21-3
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	// Called every frame 71c
	//virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//21
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//71publictoprotected
	//07-1
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon2;
	//111-3
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;
	virtual FVector GetCombatSocketLocation() override;

	//54
	virtual void InitAbilityActorInfo();
	//66
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	//void InitializePrimaryAttributes() const; 71-2c

	//71
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//124mm
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//75
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> InitializeAttributes;

	//void InitializeSecondaryAttributes() const; 71-2c
	//71-2 replace InitialPrimaryAttributes() and InitializeSecondaryAttributes()
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect>GameplayEffectClass, float Level) const;
	void InitializeDefaultAttributes() const;

	//98
	void AddCharacterAbilities();

//98
private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray <TSubclassOf<UGameplayAbility>> StartupAbilities;
};
