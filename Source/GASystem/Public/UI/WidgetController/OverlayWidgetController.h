// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature,float,NewMaxMana);
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class GASYSTEM_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
private:
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnHealthChangeSignature OnHealthChangeSignatureDelegate;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxHealthChangeSignature OnMaxHealthChangeSignatureDelegate;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnManaChangeSignature OnManaChangeSignatureDelegate;
	UPROPERTY(BlueprintAssignable,Category = "GAS|Attributes")
	FOnMaxManaChangeSignature OnMaxManaChangeSignatureDelegate;
protected:
	void OnHealthChanged(const FOnAttributeChangeData& Data) const;
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void OnManaChanged(const FOnAttributeChangeData& Data) const;
	void OnMaxManaChanged(const FOnAttributeChangeData& Data) const;
};
