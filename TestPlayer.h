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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent * Camera; // ī�޶� �߰�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent * Arm; // ī�޶� �޸� ��(��ī���� ��������)
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

	//�̵� ���� ���� ���ε��� �Լ�
	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void GoToIdle();

	//�ִϸ��̼� ���� �Լ�
	UFUNCTION()
		void DoAttack();

	UFUNCTION()
		void DoRun();

	UFUNCTION()
		void DoDash();
};
