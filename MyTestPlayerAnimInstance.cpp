// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestPlayerAnimInstance.h"

UMyTestPlayerAnimInstance::UMyTestPlayerAnimInstance() {
	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/_My/MyTestPlayer_Attack_Montage.MyTestPlayer_Attack_Montage'"));

	if (ATTACK_MONTAGE.Succeeded()) {
		attackMontage = ATTACK_MONTAGE.Object;
	}

	//달리기 애니메이션 추가=====================
	ConstructorHelpers::FObjectFinder<UAnimMontage> RUN_MONTAGE(TEXT("AnimMontage'/Game/_My/MyTestPlayer_Run_Montage.MyTestPlayer_Run_Montage'"));

	if (RUN_MONTAGE.Succeeded()) {
		runMontage = RUN_MONTAGE.Object;
	}

	//달리기 애니메이션 끝.====================

	ConstructorHelpers::FObjectFinder<UAnimMontage> IDLE_MONTAGE(TEXT("AnimMontage'/Game/_My/MyTestPlayer_Idle_Montage.MyTestPlayer_Idle_Montage'"));

	if (IDLE_MONTAGE.Succeeded()) {
		idleMontage = IDLE_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DASH_MONTAGE(TEXT("AnimMontage'/Game/_My/MyTestPlayer_Dash_Montage.MyTestPlayer_Dash_Montage'"));

	if (DASH_MONTAGE.Succeeded()) {
		dashMontage = DASH_MONTAGE.Object;
	}

}

void UMyTestPlayerAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();
}

void UMyTestPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMyTestPlayerAnimInstance::Attack() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Attack Function Active"));
	Montage_Play(attackMontage);
}

void UMyTestPlayerAnimInstance::Run() {
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Attack Function Active"));
	Montage_Play(runMontage);
}

void UMyTestPlayerAnimInstance::Idle() {
	Montage_Play(idleMontage);
}

void UMyTestPlayerAnimInstance::Dash() {
	Montage_Play(dashMontage);
}