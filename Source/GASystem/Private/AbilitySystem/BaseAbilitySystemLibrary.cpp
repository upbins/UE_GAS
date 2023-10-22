// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/BasePlayerState.h"
#include "UI/HUD/BaseHUD.h"

UOverlayWidgetController* UBaseAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if(ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			ABasePlayerState* PS = PC->GetPlayerState<ABasePlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return  nullptr;
	
}

UAttributeMenuWidgetController* UBaseAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if(ABaseHUD* HUD = Cast<ABaseHUD>(PC->GetHUD()))
		{
			ABasePlayerState* PS = PC->GetPlayerState<ABasePlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return  nullptr;
}
