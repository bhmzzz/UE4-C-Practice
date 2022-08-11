// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawningBox::ASpawningBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawningBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
}

// Called when the game starts or when spawned
void ASpawningBox::BeginPlay()
{
	Super::BeginPlay();
	SpawningTargetActor(PawnToSpawn, GetSpawnPoint());
}

FVector ASpawningBox::GetSpawnPoint()
{
	FVector Extent = SpawningBox->GetScaledBoxExtent();//缩放后的长宽高
	FVector Origin = SpawningBox->GetComponentLocation();
	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	return Point;
}

// Called every frame
void ASpawningBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawningBox::SpawningTargetActor(UClass* SpawnClass, FVector SpawnLocation)
{
	if (SpawnClass)
	{
		GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLocation, FRotator(0.0f));
	}
}

