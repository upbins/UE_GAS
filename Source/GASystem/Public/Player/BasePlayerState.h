// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/)
/**
 * 
 */
UCLASS()
class GASYSTEM_API ABasePlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ABasePlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return  AttributeSet;}
	FORCEINLINE int32 GetObjectLevel() const { return Level; }
	FOnLevelChanged OnLevelChangedDelegate;
protected:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;//GAS能力组件

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet; //GAS属性
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
