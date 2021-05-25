// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "My_MonsterBase.generated.h"

UCLASS()
class TESTPROJECT_API AMy_MonsterBase : public ACharacter,public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMy_MonsterBase();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, Category = Behavior)
		UAnimMontage *Attack_Melee;

	enum MonsterState { // 플레이어의 상태를 표시하는 자료형
		idle,
		walk,
		attack,
		death
	};

	float m_HP; //몬스터 HP
	bool canShootRange; // 공격 거리에 들어왔는지 확인 

	MonsterState monsterState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() // 충돌 체크(들어왔을 때)
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() // 나갔을 때
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	USphereComponent *hitSphere;

	void Damaged(); // 데미지 입을 때 호출하는 함수 


	int melee_attack_Implementation() override;

	UAnimMontage* get_montage() const;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;
};
