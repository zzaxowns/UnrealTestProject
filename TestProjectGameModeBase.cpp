// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ATestProjectGameModeBase::BeginPlay() {
	Super::BeginPlay(); // ������ �ִ� �Լ��� ���

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();
}