// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAnimInstance.h"
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "TestPlayer.generated.h"

//���� ���ǿ��� ���� ���� ���� �߰�
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

	enum State { // �÷��̾��� ���¸� ǥ���ϴ� �ڷ���
		idle,
		run,
		dash,
		attack
	};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent * Camera; // ī�޶� �߰�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * Arm; // ī�޶� �޸� ��(��ī���� ��������)

	bool usingMoveForward;
	bool usingAttack;
	bool usingDash;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UAnimInstance* animInstance;
	virtual void PostInitilizeComponent();
	UMyAnimInstance* myAnimInst;

	const char* comboList[3] = { "Attack1" , "Attack2", "Attack3" };
	int comboCount;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	State playerState;

	//�̵� ���� ���� ���ε��� �Լ�
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void DoIdle();

	//�ִϸ��̼� ���� �Լ�
	UFUNCTION()
		void DoAttack();

	UFUNCTION()
		void DoRun();

	UFUNCTION()
		void DoDash();

	UFUNCTION()
		void playerAnimation();

	//UFUNCTION(BlueprintCallable)
	//void EndAttacking();
};
