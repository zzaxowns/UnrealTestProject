// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "My_MonsterBase.generated.h"

UCLASS()
class TESTPROJECT_API AMy_MonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMy_MonsterBase(int m_Monster_Type, int m_Hp, int m_Offense_Power);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int m_Monster_Type;
	int m_Hp;
	int m_Offense_Power;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
