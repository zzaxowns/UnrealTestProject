// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrainingDummy_AnimInstance.h"
#include "MyTrainingDummy.h"

UMyTrainingDummy_AnimInstance::UMyTrainingDummy_AnimInstance() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HITMONTAGE(
		TEXT("AnimMontage'/Game/_My/MyTrainingDummy_HIt_Montage.MyTrainingDummy_Hit_Montage'"));

	if (HITMONTAGE.Succeeded())
	{
		hitMontage = HITMONTAGE.Object;
	}

	isHit = false;

}


void UMyTrainingDummy_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto pawn = dynamic_cast<AMyTrainingDummy*>(TryGetPawnOwner());

	if (!::IsValid(pawn)) { return; }

	isHit = pawn->getIshit();
	playhitMontage();
}

void UMyTrainingDummy_AnimInstance::AnimNotify_ResetHit()
{
	auto pawn = dynamic_cast<AMyTrainingDummy*>(TryGetPawnOwner());

	if (!::IsValid(pawn)) { return; }

	pawn->ResetHit();
}

void UMyTrainingDummy_AnimInstance::NativeBeginPlay()
{

}

void UMyTrainingDummy_AnimInstance::playhitMontage()
{
	Montage_Play(hitMontage);
}

