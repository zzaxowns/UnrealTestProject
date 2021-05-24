// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuUI.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UStartMenuUI::NativeConstruct() {
	if (Btn_StartGame) {
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartMenuUI::Btn_StartGame_Clicked);
	}

	if (Btn_ExitGame) {
		Btn_ExitGame->OnClicked.AddDynamic(this, &UStartMenuUI::Btn_ExitGame_Clicked);
	}
}

void UStartMenuUI::Btn_StartGame_Clicked(){
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/LEVEL/MyTestMap_01");
}


void UStartMenuUI::Btn_ExitGame_Clicked(){
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
