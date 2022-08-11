// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACheckActor::ACheckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = MyRoot;
	Mesh->SetupAttachment(MyRoot);
	A = 1;
	B = 1;
	RunningTime = 0;
}

// Called when the game starts or when spawned
void ACheckActor::BeginPlay()
{
	Super::BeginPlay();

	/*
	float InitX = FMath::FRand() * 500;
	float InitY = FMath::FRandRange(100, 500);
	float InitZ = 0;
	SetActorLocation(FVector(InitX, InitY, InitZ));
	*/
}

// Called every frame
void ACheckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this)
	{
		RunningTime += DeltaTime;
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = A * FMath::Sin(B * RunningTime);
		SetActorLocation(NewLocation);
	}
}

