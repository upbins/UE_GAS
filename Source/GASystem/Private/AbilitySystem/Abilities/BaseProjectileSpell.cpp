// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BaseProjectileSpell.h"

#include "Actor/BaseProjectile.h"
#include "Interaction/CombatInterface.h"

void UBaseProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer)
	{
		return;
	}
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set the projectile rotation
		ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give then projectile a gameplay effect spec for causing damage;
		
		Projectile->FinishSpawning(SpawnTransform);
		
	}

	
}
