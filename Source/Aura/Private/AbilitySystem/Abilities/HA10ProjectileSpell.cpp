// Fill out your copyright notice in the Description page of Project Settings.
//110

#include "AbilitySystem/Abilities/HA10ProjectileSpell.h"

//111-3
#include "Actor/HA10Projectile.h"
#include "Interaction/CombatInterface.h"

//111c 110-2
//#include "Kismet/KismetSystemLibrary.h"
void UHA10ProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}
//114 120 const FVector& ProjectileTargetLocation
void UHA10ProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	//114
	//114m move ActivateAbility() to SpawnProjectile()
	// HasAuthority(&ActivationInfo) to GetAvatarActorFromActorInfo()->HasAuthority()
	//111c
/*UKismetSystemLibrary::PrintString(this, FString("ActivateAbility (C++)"), true, true, FLinearColor::Yellow, 3);*/
//111
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)return;
	//111-3
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		//120
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;//up and down angle
		//111
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);///111-3
		//120
		SpawnTransform.SetRotation(Rotation.Quaternion());

		AHA10Projectile* Projectile = GetWorld()->SpawnActorDeferred<AHA10Projectile>(
			ProjectileClass,
			SpawnTransform, GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//TODO: Givethe Projectile a Gameplay Effect Spec for causing Damage.
		Projectile->FinishSpawning(SpawnTransform);//111-4
	}
}
