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
		AMainCharacter* player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());//获取玩家
		if (player)
		{
			FVector PlayerLocation = player->GetActorLocation();

			float Dis = (PlayerLocation - AILocation).Size();
			if (Dis < fDis)
			{
				return false; //足够近不用移动了。
			}
			else
			{
				return true;//不够近，继续移动。
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
