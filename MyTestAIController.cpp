// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/Engine//Classes/Kismet//GameplayStatics.h"
#include "MyTestPlayer.h"

AMyTestAIController::AMyTestAIController() {
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateAbstractDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMyTestAIController::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AMyTestAIController::BeginPlay()
{
	Super::BeginPlay();
	

	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("All System Set!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No PerceptionComponent"));
	}
}

void AMyTestAIController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
}

void AMyTestAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AMyTestPlayer* Charater = Cast<AMyTestPlayer>(GetPawn());

	if (bIsPlayerDetected == true) {
		AMyTestPlayer* Player = Cast<AMyTestPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MoveToActor(Player, 5.0f);
	}
}

FRotator AMyTestAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) { 
		return FRotator(0.f, 0.f, 0.f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw,0.0f);
}

void AMyTestAIController::OnPawnDetected(const TArray<AActor*> &DetectedPawns)
{
	for (size_t i = 0; i < DetectedPawns.Num(); i++) {
		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);
	}

	bIsPlayerDetected = true;
}
