// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_InGame.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AHUD_InGame : public AHUD
{
	GENERATED_BODY()
public: 
	AHUD_InGame();
	void BeginPlay() override;


private:
	TSubclassOf<class UUserWidget> uiBPClass;
	class UUserWidget* uiWidget;
};
