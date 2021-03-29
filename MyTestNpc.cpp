// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestNpc.h"
#include "MyTestPlayer.h"

// Sets default values
AMyTestNpc::AMyTestNpc()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HITSPHERE"));
	hitSphere->InitSphereRadius(200.0f);
	//RootComponent = hitSphere;
	hitSphere->SetCollisionProfileName(TEXT("OverlapAll"));
	hitSphere->SetupAttachment(RootComponent);

	isHit = false;

}

// Called when the game starts or when spawned
void AMyTestNpc::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyTestNpc::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//hitSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyTrainingDummy::OnOverlapBegin);
}

// Called every frame
void AMyTestNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyTestNpc::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyTestNpc::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{//¡¢√À¿ª Ω√¿€ «ﬂ¿ª∂ß

}

void AMyTestNpc::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{//¡¢√À¿Ã ≥°≥µ¿ª ∂ß

}

bool AMyTestNpc::getIshit()
{
	return isHit;
}

void AMyTestNpc::ResetHit()
{
	isHit = false;
}

