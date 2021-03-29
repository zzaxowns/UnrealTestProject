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


	bool isHit; //�浹 Ȯ�� ����

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//�浹 �����ϴ� ��
	UFUNCTION() 
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//�浹 �������� Ż������ ��
	UFUNCTION() 
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//�浹 Ȯ���� �� �ִ� ��ü
	USphereComponent *hitSphere;

	bool getIshit();//���� üũ���� Ȯ���ϴ� �Լ� - isHit �������� ��ȯ
	void ResetHit();// �浹�Ȱ� �����ϴ� �Լ�

};
