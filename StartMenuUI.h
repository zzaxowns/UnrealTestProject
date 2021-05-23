// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartGame = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ExitGame = nullptr;

private:
	UFUNCTION()
		void Btn_StartGame_Clicked();

	UFUNCTION()
		void Btn_ExitGame_Clicked();
};
