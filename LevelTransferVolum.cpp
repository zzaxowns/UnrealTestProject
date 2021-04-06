// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolum.h"

// Sets default values
ALevelTransferVolum::ALevelTransferVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransferVolum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVolum::NotifyActorBeginOverlap(AActor * OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn == nullptr) { return; }

	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, "HuntingGround");
	}
}

