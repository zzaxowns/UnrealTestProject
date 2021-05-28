// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingMenu_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AEndingMenu_HUD::AEndingMenu_HUD() {
	static ConstructorHelpers::FClassFinder<UUserWidget>ui(TEXT("/Game/_My/HUD/EndingMenu_BP"));

	if (ui.Succeeded()) {
		uiBPClass = ui.Class;
	}
}

void AEndingMenu_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (uiBPClass) {
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);

		if (uiBPClass) {
			uiWidget->AddToViewport();
		}
	}
}
