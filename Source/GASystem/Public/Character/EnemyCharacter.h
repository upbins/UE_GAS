// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GASYSTEM_API AEnemyCharacter : public ABaseCharacter,public  IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	UPROPERTY(BlueprintReadOnly);
	bool bHighlighted = false;
	
	/** Enemy Interface */
	virtual  void HighlightActor() override;
	virtual  void UnHighlightActor() override;
	/** End Enemy Interface */
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
	
