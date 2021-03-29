// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API ATestProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG Game")
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidget;
};
