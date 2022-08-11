// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardData.h"

AEnemyController::AEnemyController()
{
	MyTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("MyTreeComponent"));
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/AI/AIBTree"));//�ҵ��༭���е���Ϊ����Դ��
	if (BehaviorTreeAssert.Succeeded())
	{
		MyTree = BehaviorTreeAssert.Object;
	}
}

void AEnemyController::OnPossess(APawn* possesPawn)
{
	PossTarget = Cast<AEnemyCharacter>(possesPawn);
	if (PossTarget)
	{
		Super::OnPossess(possesPawn);
		if (PossTarget->BlackboardData)
		{
			PossTarget->BlackboardData->InitializeBlackboard(*MyTree->BlackboardAsset);//��ʼ���ڰ�
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NULL"));
		}
	}
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	if (MyTreeComponent)
	{
		if (MyTree)
		{
			RunBehaviorTree(MyTree);
			//MyTreeComponent->StartTree(*MyTree,EBTExecutionMode::Looped);//������Ϊ��
			UE_LOG(LogTemp, Warning, TEXT("RunTree"));
		}
	}
}
