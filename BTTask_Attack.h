// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "My_MonsterBase.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_Attack(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	bool montage_has_finished(AMy_MonsterBase* const npcBot);
};
