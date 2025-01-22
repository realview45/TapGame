// Fill out your copyright notice in the Description page of Project Settings.
//109
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA10Projectile.generated.h"

//109-2
class USphereComponent;
class UProjectileMovementComponent;
//122
class UNiagaraSystem;

UCLASS()
class AURA_API AHA10Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHA10Projectile();

	//109-3
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//109-2
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//122-3
	virtual void Destroyed() override;

//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	//122-2
	bool bHit = false;
	//122-4
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	//122
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	UPROPERTY(EditAnywhere)
	//122-4
	TObjectPtr<USoundBase> LoopingSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
