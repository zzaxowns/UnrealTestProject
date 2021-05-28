// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingMenuUI.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UEndingMenuUI::NativeConstruct() {

	if (Btn_ExitGame) {
		Btn_ExitGame->OnClicked.AddDynamic(this, &UEndingMenuUI::Btn_ExitGame_Clicked);
	}
}

void UEndingMenuUI::Btn_ExitGame_Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
