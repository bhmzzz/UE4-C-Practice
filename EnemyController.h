// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */

UCLASS()
class PRACTICETEMP_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyController();
	void OnPossess(APawn* possesPawn) override;
protected:
	void BeginPlay() override;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* MyTreeComponent;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* MyTree;

	UPROPERTY()
		class AEnemyCharacter* PossTarget;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() { return MyTreeComponent; }
};
