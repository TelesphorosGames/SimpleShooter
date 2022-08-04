// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTASK_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTASK_ClearBlackboardValue::UBTTASK_ClearBlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}


EBTNodeResult::Type UBTTASK_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;

}
