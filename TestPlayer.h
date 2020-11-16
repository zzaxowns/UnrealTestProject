// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAnimInstance.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "TestPlayer.generated.h"

//영어 강의에서 나온 내용 관련 추가
//#include"Components/InputComponent.h"
//#include"GameFramework/Controller.h"
//#include"GameFramework//CharacterMovementComponent.h"
//#include "Camera/CameraComponent.h"
//#include"GameFramework/SpringArmComponent.h"

UCLASS()
class TESTPROTOTYPE_API ATestPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent * Camera; // 카메라 추가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * Arm; // 카메라에 달린 봉(셀카봉을 생각하자)
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UAnimInstance* animInstance;
	virtual void PostInitilizeComponent();
	UMyAnimInstance* myAnimInst;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//이동 관련 내용 바인딩할 함수
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void GoToIdle();

	//애니메이션 관련 함수
	UFUNCTION()
		void DoAttack();

	UFUNCTION()
		void DoRun();

	UFUNCTION()
		void DoDash();
};
