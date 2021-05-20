// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyTestAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;

class UBlackboardComponent;

UCLASS(config = Game)
class TESTPROJECT_API AMyTestAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyTestAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightRadius = 500.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightAge = 5.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AILoseSightRadius = AISightRadius + 50.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AIFieldOfView = 90.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	bool bIsPlayerDetected = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;

private:
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;
};
