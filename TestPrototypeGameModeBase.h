// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestPrototypeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROTOTYPE_API ATestPrototypeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATestPrototypeGameModeBase();
};
