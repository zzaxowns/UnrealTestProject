// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyTrainingDummy_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMyTrainingDummy_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UMyTrainingDummy_AnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool isHit;

	UFUNCTION()
	void AnimNotify_ResetHit();

public:

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UAnimMontage *hitMontage;

	void playhitMontage();
};
