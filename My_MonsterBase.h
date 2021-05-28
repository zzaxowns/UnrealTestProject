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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		class USphereComponent* AttckCollsionSphere;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, Category = Behavior)
		UAnimMontage *Attack_Melee;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyCharacterName;*/

	enum MonsterState { // �÷��̾��� ���¸� ǥ���ϴ� �ڷ���
		idle,
		walk,
		attack,
		death
	};

	float m_HP; //���� HP
	bool canShootRange; // ���� �Ÿ��� ���Դ��� Ȯ�� 

	MonsterState monsterState;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	int melee_attack_Implementation() override;

	UAnimMontage* get_montage() const;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* hitmontage;
};
