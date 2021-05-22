// Fill out your copyright notice in the Description page of Project Settings.


#include "My_MonsterBase.h"
#include "MyTestPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMy_MonsterBase::AMy_MonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HITSPHERE"));
	hitSphere->InitSphereRadius(50.0f);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	m_HP = 3;
	canShootRange = false; // 슈팅 레인지에 들어왔는지 아닌지 확인하는 변수 
	monsterState = idle;

	

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

	if (OtherActor != nullptr && (OtherActor != this) && OtherComp) {

		auto player = Cast<AMyTestPlayer>(OtherActor);
		if (!player) return;

		if (OtherActor->IsA(AMyTestPlayer::StaticClass())) {
			UE_LOG(LogTemp, Warning, TEXT("Attack Player"));
		}
	}

}

void AMy_MonsterBase::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp) {

		auto player = Cast<AMyTestPlayer>(OtherActor);
		if (!player) return;

		if (OtherActor->IsA(AMyTestPlayer::StaticClass()) && player->getUsingAttack()) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("collison"));
			canShootRange = false;
		}
	}
}

void AMy_MonsterBase::Damaged()
{
	this->m_HP--; //1씩 감소
}
