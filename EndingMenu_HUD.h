// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndingMenu_HUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AEndingMenu_HUD : public AHUD
{
	GENERATED_BODY()
public:
	AEndingMenu_HUD();
	void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
