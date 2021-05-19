// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAnimationNotiftState.h"
#include "MyTestPlayer.h"
#include "Engine.h"

void UMyTestAnimationNotiftState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, __FUNCTION__);
	AMyTestPlayer *player = Cast<AMyTestPlayer>(MeshComp->GetOwner());

	if (player != NULL) {//플레이어가 있으면 
		player->setUsingAttack(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, __FUNCTION__);
	}
}

void UMyTestAnimationNotiftState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{

	AMyTestPlayer *player = Cast<AMyTestPlayer>(MeshComp->GetOwner());

	if (player != NULL) {//플레이어가 있으면 
		player->setUsingAttack(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, __FUNCTION__);
	}
}
