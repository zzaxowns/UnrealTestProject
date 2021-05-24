// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/AudioComponent.h"
#include "StartMenu_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AStartMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AStartMenu_GameMode();
protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* BGMSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* BGMAudioComponent;
};
