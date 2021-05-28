// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingMenu_GameMode.h"
#include "EndingMenu_HUD.h"
AEndingMenu_GameMode::AEndingMenu_GameMode() {
	HUDClass = AEndingMenu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
}

void AEndingMenu_GameMode::BeginPlay()
{
}
