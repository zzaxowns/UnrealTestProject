// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAnimationNotiftState.h"
#include "MyTestPlayer.h"
#include "Engine.h"

void UMyTestAnimationNotiftState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, __FUNCTION__);
}

void UMyTestAnimationNotiftState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, __FUNCTION__);
}
