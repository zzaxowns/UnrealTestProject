// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyTestPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMyTestPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UMyTestPlayerAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void Run();

	UFUNCTION(BlueprintCallable)
	void Idle();

	UFUNCTION(BlueprintCallable)
	void Dash();

private:
	/*UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;*/

public:
	UAnimMontage *attackMontage;
	UAnimMontage *runMontage;
	UAnimMontage *idleMontage;
	UAnimMontage *dashMontage;
		 
};
