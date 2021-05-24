// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/AudioComponent.h"
#include "TestProjectGameModeBase.generated.h"
/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState :uint8 {
	GameStart,
	GamePlay,
	GamePause,
	GameOver,
};

UCLASS()
class TESTPROJECT_API ATestProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	ATestProjectGameModeBase();

	virtual void BeginPlay() override;

	/*UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG Game")
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidget;*/

	UPROPERTY(EditAnywhere, Category = "UMG Game")
		EGameState gameStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget>HUDWidgetClass;

	UUserWidget* CurrentWidget;


	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* BGMSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* BGMAudioComponent;

public:
	void ChangeUI();
};
