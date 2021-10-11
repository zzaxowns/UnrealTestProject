// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCbot.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controller_StartMenu.h"
#include "MyTestplayer.h"

// Sets default values
AMyNPCbot::AMyNPCbot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->InitSphereRadius(250.f);
	RootComponent = CollisionSphere;

	mSkeltalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShopNPC_Obj"));
	mSkeltalMesh->SetupAttachment(RootComponent);

	isTalk = false;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGateway::OnOverlapBegin());

}

void AMyNPCbot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
	Super::FaceRotation(CurrentRotation, DeltaTime);
}

// Called when the game starts or when spawned
void AMyNPCbot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyNPCbot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* myCharLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	myCharLoc->GetActorLocation();

	FaceRotation(, float DeltaTime);
}

// Called to bind functionality to input
void AMyNPCbot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyNPCbot::OnOverlapBegin(UPrimitiveComponent * OverlapperComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFr)
{
}

