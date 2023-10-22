// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FBaseAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FBaseAttributeInfo& Info : AttributeInformation)
	{
		if(Info.AttributeTag == AttributeTag)
		{
			return  Info;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]"),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FBaseAttributeInfo();
}
