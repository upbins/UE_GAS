// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class GASYSTEM_API ABasePlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ABasePlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return  AttributeSet;}
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;//GAS能力组件

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet; //GAS属性
};
