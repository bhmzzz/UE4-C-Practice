// Fill out your copyright notice in the Description page of Project Settings.


#include "MYBTD_CheckDistance.h"
#include "EnemyController.h"
#include "EnemyCharacter.h"
#include "MainCharacter.h"

bool UMYBTD_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AEnemyController* AIC = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		FVector AILocation = Cast<AEnemyCharacter>(AIC->GetPawn())->GetActorLocation();
		AMainCharacter* player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());//��ȡ���
		if (player)
		{
			FVector PlayerLocation = player->GetActorLocation();

			float Dis = (PlayerLocation - AILocation).Size();
			if (Dis < fDis)
			{
				return false; //�㹻�������ƶ��ˡ�
			}
			else
			{
				return true;//�������������ƶ���
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
}
