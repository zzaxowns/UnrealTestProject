// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HUD_InGame.h"

ATestProjectGameModeBase::ATestProjectGameModeBase() {
	HUDClass = AHUD_InGame::StaticClass();
	DefaultPawnClass = nullptr;
	//PlayerControllerClass = A
}

void ATestProjectGameModeBase::BeginPlay() {
	Super::BeginPlay(); // ������ �ִ� �Լ��� ���

}

void ATestProjectGameModeBase::ChangeUI()
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	CurrentWidget->AddToViewport();
}
