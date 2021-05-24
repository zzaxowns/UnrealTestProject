// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "StartMenu_HUD.h"
#include "Sound/SoundCue.h"

AStartMenu_GameMode::AStartMenu_GameMode() {
	HUDClass = AStartMenu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = 

	static ConstructorHelpers::FObjectFinder<USoundCue>BGM(TEXT("SoundCue'/Game/FantasyOrchestral/cues/FantasyAdventure.FantasyAdventure'"));

	if (BGM.Succeeded()) {
		BGMSoundCue = BGM.Object;
		BGMAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMAudioComponent"));
		BGMAudioComponent->SetupAttachment(RootComponent);
	}
}

void AStartMenu_GameMode::BeginPlay() {
	if (BGMAudioComponent && BGMSoundCue) // 사운드 발생
	{
		BGMAudioComponent->SetSound(BGMSoundCue);
		BGMAudioComponent->Play(0.0f);
	}


}