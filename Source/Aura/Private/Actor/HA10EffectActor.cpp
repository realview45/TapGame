// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/HA10EffectActor.h"

#include "Components/SphereComponent.h"
//27-3
#include "AbilitySystemInterface.h"
#include "AbilitySystem/HA10AttributeSet.h"
// Sets default values
AHA10EffectActor::AHA10EffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AHA10EffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Shouldn't do this!! const_cast
	//27-3
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//pure virtual function
		const UHA10AttributeSet* HA10AttributeSet = Cast<UHA10AttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UHA10AttributeSet::StaticClass()));
		UHA10AttributeSet* MutableHA10AttributeSet = const_cast<UHA10AttributeSet*>(HA10AttributeSet);
		MutableHA10AttributeSet->SetHealth(HA10AttributeSet->GetHealth() + 25.f);
		//36
		MutableHA10AttributeSet->SetMana(HA10AttributeSet->GetMana() + 25.f);
		Destroy();
	}
}

void AHA10EffectActor::OutOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void AHA10EffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AHA10EffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AHA10EffectActor::OutOverlap);

}


