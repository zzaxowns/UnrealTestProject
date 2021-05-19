// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"MyTestPlayerAnimInstance.h"
#include "EngineMinimal.h"
#include "BasicCharacter.h"
#include "MyTestPlayer.generated.h"


UCLASS()
class TESTPROJECT_API AMyTestPlayer : public ABasicCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTestPlayer();

	enum State { // �÷��̾��� ���¸� ǥ���ϴ� �ڷ���
		idle,
		run,
		dash,
		attack
	};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float playerHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float playerStamina;

	bool isCombo;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent * Camera; // ī�޶� �߰�

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent * Arm; // ī�޶� �޸� ��(��ī���� ��������)

	UAnimInstance* animInstance;
	//virtual void PostInitilizeComponent();
	UMyTestPlayerAnimInstance* myTestPlayerAnimInst;

	bool usingMoveForward;
	bool usingAttack;
	bool usingDash;

	const char* comboList[3] = { "Attack1" , "Attack2", "Attack3" };
	int comboCount;

public:
	//�÷��̾� ����
	State playerState;
	float recoverStaminaDelay;

	UFUNCTION()
	void RecoverST(float DeltaTime);

	UFUNCTION()
	void Damaged();

	UFUNCTION()
	void setUsingAttack(bool usingAttack);

	UFUNCTION()
	bool getUsingAttack();

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
	UParticleSystem* HitFx;


	void ShowFX();
protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//�̵� ���� ���� ���ε��� �Լ�
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);
	
	//�ִϸ��̼� ���� �Լ�
	UFUNCTION()
	void DoIdle();

	UFUNCTION()
	void DoAttack();

	UFUNCTION()
	void DoRun();

	UFUNCTION()
	void DoDash();

	UFUNCTION()
	void playerAnimation();
	
};
