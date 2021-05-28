// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EndingLevelTransferVolum.h"

// Sets default values
AEndingLevelTransferVolum::AEndingLevelTransferVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("EndingVolum"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPwan"));
}

// Called when the game starts or when spawned
void AEndingLevelTransferVolum::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndingLevelTransferVolum::NotifyActorBeginOverlap(AActor * OtherActor)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn == nullptr) { return; }

	if (Pawn != nullptr)
	{
		UGameplayStatics::OpenLevel(this, "EndingMenu_Level");
	}
}

// Called every frame
void AEndingLevelTransferVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

