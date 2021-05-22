// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet//GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework//Character.h"
#include "MyTestPlayer.h"
#include "Engine.h"

AMyTestAIController::AMyTestAIController(FObjectInitializer const& object_initalizer) {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/_My/My_AI/MyTestMonsterBot_BT.MyTestMonsterBot_BT'"));

	if (obj.Succeeded()) {
		btree = obj.Object;
	}
	
	behavior_tree_Comp = object_initalizer.CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initalizer.CreateAbstractDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	setup_perception_system();

}

void AMyTestAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(btree);
	behavior_tree_Comp->StartTree(*btree);
}

void AMyTestAIController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
	if (blackboard) {
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

void AMyTestAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AMyTestAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) { 
		return FRotator(0.f, 0.f, 0.f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw,0.0f);
}

void AMyTestAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus) {
	if (auto const ch = Cast<AMyTestPlayer>(actor)) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!!");
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent*  AMyTestAIController::get_blackboard() const {
	return blackboard;
}

void AMyTestAIController::setup_perception_system() {

	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateAbstractDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sight_config->SightRadius = 500.0f;
	sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;

	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyTestAIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}