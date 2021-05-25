// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerAttackRange.h"
#include "My_MonsterBase.h"
#include "MyTestAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBTService_IsPlayerAttackRange::UBTService_IsPlayerAttackRange() {
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}

void UBTService_IsPlayerAttackRange::OnBecomeRelevant(UBehaviorTreeComponent & owner_comp, uint8 * node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);
	
	AMyTestAIController* const cont = Cast<AMyTestAIController>(owner_comp.GetAIOwner());
	AMy_MonsterBase* const npcBot = Cast<AMy_MonsterBase>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, npcBot->GetDistanceTo(player) <= Attack_range);
}
