// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HUD_InGame.h"
#include "Sound/SoundCue.h"

ATestProjectGameModeBase::ATestProjectGameModeBase() {
	HUDClass = AHUD_InGame::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = A

	static ConstructorHelpers::FObjectFinder<USoundCue>BGM(TEXT("SoundCue'/Game/FantasyOrchestral/cues/ElvenHarmonies.ElvenHarmonies'"));

	if (BGM.Succeeded()) {
		BGMSoundCue = BGM.Object;
		BGMAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMAudioComponent"));
		BGMAudioComponent->SetupAttachment(RootComponent);
	}
}

void ATestProjectGameModeBase::BeginPlay() {
	Super::BeginPlay(); // ������ �ִ� �Լ��� ���

	if (BGMAudioComponent && BGMSoundCue) // ���� �߻�
	{
		BGMAudioComponent->SetSound(BGMSoundCue);
		BGMAudioComponent->Play(0.0f);
	}
}

void ATestProjectGameModeBase::ChangeUI()
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	CurrentWidget->AddToViewport();
}
