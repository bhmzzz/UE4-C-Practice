// Fill out your copyright notice in the Description page of Project Settings.


#include "MYBTT_MoveTo.h"
#include "MainCharacter.h"
#include "EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyCharacter.h"

UMYBTT_MoveTo::UMYBTT_MoveTo()
{
	NodeName = "MyMoveTo";
}

EBTNodeResult::Type UMYBTT_MoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyController* AIC = Cast<AEnemyController>(OwnerComp.GetAIOwner());//�����Ϊ�������Ŀ�������
	if (AIC)
	{
		FVector TagetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TargetLocation"));//��úڰ��е����ݡ�
		AEnemyCharacter* AI = Cast<AEnemyCharacter>(AIC->GetPawn());
		if (AI)
		{
			AIC->MoveToLocation(TagetLocation);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}