// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyTrainingDummy_AnimInstance.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "MyTrainingDummy.generated.h"

UCLASS()
class TESTPROJECT_API AMyTrainingDummy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTrainingDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UAnimInstance* animInstance;
	UMyTrainingDummy_AnimInstance* myTrainingDummyAnim;

	bool isHit;
	bool lenghOfCanHit;
	//UFUNCTION(BlueprintCallable)
	//void ResetHit();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	USphereComponent *hitSphere;
	bool getIshit();//현재 체크인지 확인하는 함수 - isHit 변수값을 반환
	void ResetHit();// 충돌된거 해제하는 함수
	void CheckCanHit(); //현재 체크될 수 있는지(예비로 만듬)
};
