// Fill out your copyright notice in the Description page of Project Settings.


#include "My_MonsterBase.h"
#include "MyTestPlayer.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMy_MonsterBase::AMy_MonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttckCollsionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollsionSphere"));
	AttckCollsionSphere->InitSphereRadius(10.f);
	AttckCollsionSphere->AttachTo(GetMesh(), "AttackPoint");
	GetCharacterMovement()->bOrientRotationToMovement = true;

	m_HP = 3;
	canShootRange = false; // 슈팅 레인지에 들어왔는지 아닌지 확인하는 변수 
	monsterState = idle;
}

void AMy_MonsterBase::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AMyTestPlayer::StaticClass()) && PlayAnimMontage(montage) > 0.2f ) {
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		
	}
}

float AMy_MonsterBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
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

void AMy_MonsterBase::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp) {

		auto player = Cast<AMyTestPlayer>(OtherActor);
		if (!player) return;

		if (OtherActor->IsA(AMyTestPlayer::StaticClass()) && player->getUsingAttack()) {
			//m_HP--;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Monster hit"));
		}
	}

}

int AMy_MonsterBase::melee_attack_Implementation()
{
	if (montage) {
		PlayAnimMontage(montage);
	}

	return 0;
}

UAnimMontage * AMy_MonsterBase::get_montage() const
{
	return montage;
}

