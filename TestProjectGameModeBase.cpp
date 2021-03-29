// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ATestProjectGameModeBase::BeginPlay() {
	Super::BeginPlay(); // 상위에 있는 함수를 사용

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();
}