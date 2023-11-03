// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "BaseGamePlayTags.h"
UBaseAssetManager& UBaseAssetManager::Get()
{
	check(GEngine)
	UBaseAssetManager* BaseAssetManager = Cast<UBaseAssetManager>(GEngine->AssetManager);
	return *BaseAssetManager;
}

void UBaseAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FBaseGameplayTags::InitializeNativeGameplayTags();
	//This is required to use TargetData
	UAbilitySystemGlobals::Get().InitGlobalData();
}
