// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GASYSTEM_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual  void PossessedBy(AController* NewController) override;
	virtual  void OnRep_PlayerState() override;
	/** Combat Interface */
		virtual int32 GetObjectLevel_Implementation() override;
	/** end Combat Interface */
private:
	virtual void InitAbilityActorInfo() override;
};
