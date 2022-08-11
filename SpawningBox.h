// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawningBox.generated.h"

UCLASS()
class PRACTICETEMP_API ASpawningBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#if 1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* SpawningBox;
	UFUNCTION(BlueprintPure)
		FVector GetSpawnPoint();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> PawnToSpawn;//可以动态生成类
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawningTargetActor(UClass* SpawnClass, FVector SpawnLocation);

};
