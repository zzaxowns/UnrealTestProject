// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"MyTestPlayerAnimInstance.h"
#include "EngineMinimal.h"
#include "BasicCharacter.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/AudioComponent.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"

#include "MyTestPlayer.generated.h"


UCLASS()
class TESTPROJECT_API AMyTestPlayer : public ABasicCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyTestPlayer();

	enum State { // 플레이어의 상태를 표시하는 자료형
		idle,
		run,
		dash,
		attack,
		hit
	};


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float playerStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector particlePos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyMaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MyHealth;
		
	//공격 받았을 때 관련 몽타주, 함수 등

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* hit_Mongtage;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool isCombo;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent * Camera; // 카메라 추가

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent * Arm; // 카메라에 달린 봉(셀카봉을 생각하자)

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class USoundCue* AttackSoundCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		class UAudioComponent* AttackAudioComponent;



	UAnimInstance* animInstance;
	//virtual void PostInitilizeComponent();
	UMyTestPlayerAnimInstance* myTestPlayerAnimInst;

	bool usingMoveForward;
	bool usingAttack;
	bool usingDash;

	const char* comboList[3] = { "Attack1" , "Attack2", "Attack3" };
	int comboCount;

public:
	//플레이어 상태
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

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* GetHitFx;

	//float get_Health() const;

	//float get_maxHealth() const;

	//void set_health(float const new_health);

protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//이동 관련 내용 바인딩할 함수
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);
	
	//애니메이션 관련 함수
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
	


private:

	//class UWidgetComponent* Widget_Component;

	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus();

};
