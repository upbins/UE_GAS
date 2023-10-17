// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASYSTEM_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	 UFUNCTION(BlueprintCallable)
	 void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent) //C++不实现,蓝图实现,主要用于C++调用蓝图
	void WidgetControllerSet();
};
