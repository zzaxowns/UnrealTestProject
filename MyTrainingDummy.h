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
	bool getIshit();//���� üũ���� Ȯ���ϴ� �Լ� - isHit �������� ��ȯ
	void ResetHit();// �浹�Ȱ� �����ϴ� �Լ�
	void CheckCanHit(); //���� üũ�� �� �ִ���(����� ����)
};
