// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);
	OnHealthChangeSignatureDelegate.Broadcast(BaseAttributeSet->GetHealth());
	OnMaxHealthChangeSignatureDelegate.Broadcast(BaseAttributeSet->GetMaxHealth());
	OnManaChangeSignatureDelegate.Broadcast(BaseAttributeSet->GetMana());
	OnMaxManaChangeSignatureDelegate.Broadcast(BaseAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBaseAttributeSet* BaseAttributeSet = CastChecked<UBaseAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this,&UOverlayWidgetController::OnHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::OnMaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::OnManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::OnMaxManaChanged);
	Cast<UBaseAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagDelegate.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
	{
			for (auto Tag:AssetTags)
			{
				//{"A.1"}.HasTag("A") will return True, {"A"}.HasTag("A.1") will return False
				FGameplayTag MessagePrefixTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				const bool bIsMatchTag = Tag.MatchesTag(MessagePrefixTag);
				if (bIsMatchTag)
				{
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
					OnMessageWidgetRowSignature.Broadcast(*Row);
				}
				
			}
	}
	);
}

void UOverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangeSignatureDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangeSignatureDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChangeSignatureDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChangeSignatureDelegate.Broadcast(Data.NewValue);
}
