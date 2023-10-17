// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerState.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"

ABasePlayerState::ABasePlayerState()
{
	
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true); //可复制的

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;//服务器发生变更时，更新频率
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return  AbilitySystemComponent;
}
