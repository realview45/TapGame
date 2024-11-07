// Fill out your copyright notice in the Description page of Project Settings.
//27
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA10EffectActor.generated.h"

class USphereComponent;

UCLASS()
class AURA_API AHA10EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHA10EffectActor();

	UFUNCTION()
	virtual void OnOverlap
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//overlapvolume sphere
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
};
