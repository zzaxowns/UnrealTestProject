// Fill out your copyright notice in the Description page of Project Settings.


#include "My_MonsterBase.h"

// Sets default values
AMy_MonsterBase::AMy_MonsterBase(int m_Monster_Type, int m_Hp, int m_Offense_Power)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->m_Monster_Type = m_Monster_Type;
	this->m_Hp = m_Hp;
	this->m_Offense_Power = m_Offense_Power;
}

// Called when the game starts or when spawned
void AMy_MonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMy_MonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMy_MonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

