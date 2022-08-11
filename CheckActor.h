// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckActor.generated.h"

UCLASS()
class PRACTICETEMP_API ACheckActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* MyRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Floater Variables")
		float A;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
		float B;

private:
		float RunningTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
