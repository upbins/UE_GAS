// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "BaseProjectileSpell.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class GASYSTEM_API UBaseProjectileSpell : public UBaseGameplayAbility
{
	GENERATED_BODY()
private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<ABaseProjectile> ProjectileClass;
};
