// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance() {
	bIsAttack = false;

	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animation_BP/AttackMontage.AttackMontage'"));
	
	if (ATTACK_MONTAGE.Succeeded()) {
		attackMontage = ATTACK_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> RUN_MONTAGE(TEXT("AnimMontage'/Game/Animation_BP/RunMontage.RunMontage'"));

	if (RUN_MONTAGE.Succeeded()) {
		runMontage = RUN_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> IDLE_MONTAGE(TEXT("AnimMontage'/Game/Animation_BP/IdleMontage.IdleMontage'"));

	if (IDLE_MONTAGE.Succeeded()) {
		idleMontage = IDLE_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DASH_MONTAGE(TEXT("AnimMontage'/Game/Animation_BP/DashMontage.DashMontage'"));

	if (DASH_MONTAGE.Succeeded()) {
		dashMontage = DASH_MONTAGE.Object;
	}
}

void UMyAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMyAnimInstance::Attack() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Attack Function Active"));
	//ToDo: Play Attack Montage
	Montage_Play(attackMontage);
}

void UMyAnimInstance::Run() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Attack Function Active"));
	//ToDo: Play Attack Montage
	Montage_Play(runMontage);
}

void UMyAnimInstance::Idle() {
	Montage_Play(idleMontage);
}

void UMyAnimInstance::Dash() {
	Montage_Play(dashMontage);
}