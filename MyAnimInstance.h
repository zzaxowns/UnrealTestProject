// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROTOTYPE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimInstance();

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
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = MyInstance, meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;

public:
	UAnimMontage *attackMontage;
	UAnimMontage *runMontage;
	UAnimMontage *idleMontage;
	UAnimMontage *dashMontage;

};
