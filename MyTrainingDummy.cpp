// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "MyTestPlayer.h"
#include "MyTrainingDummy.h"

// Sets default values
AMyTrainingDummy::AMyTrainingDummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.0f, 0.f));
	GetMesh()->RelativeLocation.Z = -88.f;
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // 캐릭터가 보는 방향을 바꿈

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DUMMY_MESH(
		TEXT("SkeletalMesh'/Game/DummyTraining/Meshes/SK_Dummy_Training.SK_Dummy_Training'"));
	
	if (DUMMY_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(DUMMY_MESH.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> DUMMY_ANUM(TEXT("AnimBlueprint'/Game/_My/MyTrainingDummyAnimaion_BP.MyTrainingDummyAnimaion_BP_C'"));

	if (DUMMY_ANUM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(DUMMY_ANUM.Class);
	}

	hitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HITSPHERE"));
	hitSphere->InitSphereRadius(75.0f);
	//RootComponent = hitSphere;
	hitSphere->SetCollisionProfileName(TEXT("OverlapAll"));
	hitSphere->SetupAttachment(RootComponent);

	isHit = false;
	lenghOfCanHit = false;
}

// Called when the game starts or when spawned
void AMyTrainingDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTrainingDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//myTrainingDummyAnim = dynamic_cast<UMyTrainingDummy_AnimInstance*>(GetMesh()->GetAnimInstance);
	myTrainingDummyAnim = Cast<UMyTrainingDummy_AnimInstance>(animInstance);

	hitSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyTrainingDummy::OnOverlapBegin);
}

// Called every frame
void AMyTrainingDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyTrainingDummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyTrainingDummy::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp) {

		auto player = Cast<AMyTestPlayer>(OtherActor);
		if (!player) return;

		if (OtherActor->IsA(AMyTestPlayer::StaticClass())&& player->getUsingAttack()) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("collison"));
			lenghOfCanHit = true;
			isHit = true;
		}
	}
}

void AMyTrainingDummy::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp) {

		auto player = Cast<AMyTestPlayer>(OtherActor);
		if (!player) return;

		if (OtherActor->IsA(AMyTestPlayer::StaticClass()) && player->getUsingAttack()) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("collison"));
			lenghOfCanHit = false;
		}
	}
}

void AMyTrainingDummy::ResetHit() 
{
	isHit = false;
}

void AMyTrainingDummy::CheckCanHit()
{

}

bool AMyTrainingDummy::getIshit()
{
	return isHit;
}
