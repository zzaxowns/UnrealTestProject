// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "My_MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMy_MonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMy_MonsterAnimInstance();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;



};
