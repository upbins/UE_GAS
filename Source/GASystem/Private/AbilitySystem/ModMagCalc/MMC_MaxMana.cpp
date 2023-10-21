﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/BaseAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UBaseAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource =  EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	 const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	 const FGameplayTagContainer* TargetsTags = Spec.CapturedSourceTags.GetAggregatedTags();
	 FAggregatorEvaluateParameters EvaluateParameters;
	 EvaluateParameters.SourceTags = SourceTags;
	 EvaluateParameters.TargetTags = TargetsTags;
	 float Intelligence = 0;
	 GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,Intelligence);
	 Intelligence = FMath::Max<float>(Intelligence,0);
	 ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	 const int32 PlayerLevel = CombatInterface->GetObjectLevel();
	 return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
