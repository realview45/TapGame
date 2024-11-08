// Fill out your copyright notice in the Description page of Project Settings.
//27
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HA10EffectActor.generated.h"

//38
//class USphereComponent;

UCLASS()
class AURA_API AHA10EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHA10EffectActor();

	//38
	//UFUNCTION()
	//virtual void OnOverlap
	//(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	//UFUNCTION()
	//virtual void OutOverlap
	//(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//38
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectclass;

private:
	//overlapvolume sphere
	// //38
	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<USphereComponent> Sphere;
	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UStaticMeshComponent> Mesh;
};
