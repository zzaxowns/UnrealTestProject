// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyTestAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;

class UBlackboardComponent;

UCLASS()
class TESTPROJECT_API AMyTestAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyTestAIController(FObjectInitializer const& object_initalizer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	class UBlackboardComponent* get_blackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
	class UAISenseConfig_Sight* sight_config;

	void setup_perception_system();
};
