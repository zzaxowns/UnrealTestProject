// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "MyTestNpc.generated.h"

UCLASS()
class TESTPROJECT_API AMyTestNpc : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTestNpc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


	bool isHit; //충돌 확인 변수

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//충돌 시작하는 때
	UFUNCTION() 
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//충돌 범위에서 탈출했을 때
	UFUNCTION() 
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//충돌 확인할 수 있는 구체
	USphereComponent *hitSphere;

	bool getIshit();//현재 체크인지 확인하는 함수 - isHit 변수값을 반환
	void ResetHit();// 충돌된거 해제하는 함수

};
