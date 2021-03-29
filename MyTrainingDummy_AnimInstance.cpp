// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTrainingDummy_AnimInstance.h"
#include "MyTrainingDummy.h"

UMyTrainingDummy_AnimInstance::UMyTrainingDummy_AnimInstance() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATHMONTAGE(
		TEXT("AnimMontage'/Game/_My/MyTrainingDummy_Death_Montage.MyTrainingDummy_Death_Montage'"));
	if (DEATHMONTAGE.Succeeded())
	{
		deathMontage = DEATHMONTAGE.Object;
	}

	isHit = false;

}


void UMyTrainingDummy_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto pawn = dynamic_cast<AMyTrainingDummy*>(TryGetPawnOwner());

	if (!::IsValid(pawn)) { return; }

	isHit = pawn->getIshit();

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

void UMyTrainingDummy_AnimInstance::playDeathMontage()
{
	Montage_Play(deathMontage);
}

