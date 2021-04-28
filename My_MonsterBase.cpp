// Fill out your copyright notice in the Description page of Project Settings.


#include "My_MonsterBase.h"

// Sets default values
AMy_MonsterBase::AMy_MonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HITSPHERE"));
	hitSphere->InitSphereRadius(75.0f);

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

void AMy_MonsterBase::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

void AMy_MonsterBase::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}