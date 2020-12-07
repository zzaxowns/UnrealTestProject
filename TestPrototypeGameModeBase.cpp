// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPrototypeGameModeBase.h"
#include "TestPlayer.h"

ATestPrototypeGameModeBase::ATestPrototypeGameModeBase() {
	DefaultPawnClass = ATestPlayer::StaticClass();
}

void ATestPrototypeGameModeBase::BeginPlay() {

}