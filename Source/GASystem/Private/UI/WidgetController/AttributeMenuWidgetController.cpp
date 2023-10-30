// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "BaseGamePlayTags.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Kismet/GameplayStatics.h"
//DECLARE_CYCLE_STAT(TEXT("Char BroadcastInitialValues"), STAT_CharBroadcastInitialValues, STATGROUP_Game);

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UBaseAttributeSet* AS = CastChecked<UBaseAttributeSet>(AttributeSet);
	for (auto& Element : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Element.Value()).AddLambda(
			[this,Element](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Element.Key, Element.Value());
			});
		
	}
}


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//SCOPE_CYCLE_COUNTER(STAT_CharBroadcastInitialValues);
	// UE_LOG(LogTemp,Error,TEXT("%s"),"Start");
	auto Start = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
	UBaseAttributeSet* AS = CastChecked<UBaseAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Element : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Element.Key, Element.Value());
	}
	// int  count = 1;
	// for (int i = 0; i < 1000; ++i)
	// {
	// 	//UE_LOG(LogTemp,Error,TEXT("%d"),count);
	// 	count = count + 1;
	// }
	// auto offsetTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds() - Start;
	// UE_LOG(LogTemp,Error,TEXT("%f,%f"),offsetTime,Start);
}


void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FBaseAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	OnAttributeInfoDelegate.Broadcast(Info);
}
