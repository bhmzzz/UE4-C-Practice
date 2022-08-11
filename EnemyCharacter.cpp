// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyController.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AIControllerClass = AEnemyController::StaticClass();

	Sight = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sight"));

	BlackboardData = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardData"));

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (Sight)
	{
		Sight->OnSeePawn.AddDynamic(this, &AEnemyCharacter::HaveSeePawn);
	}
	/*if (BlackboardData)
	{
		BlackboardData->SetValueAsVector("TargetLocation", FVector(230.f,840.f,80.f));//设置黑板中对应的键值。
		UE_LOG(LogTemp, Warning, TEXT("1111111"));
	}*/
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::HaveSeePawn(APawn* Pawn)
{
	AMainCharacter* player = Cast<AMainCharacter>(Pawn);
	if (player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Pawn->GetFName().ToString());
		FVector Location = player->GetActorLocation();//获取到玩家的位置
		if (BlackboardData)
		{
			BlackboardData->SetValueAsVector("TargetLocation", Location);//设置黑板中对应的键值。
			BlackboardData->SetValueAsBool("testbool", true);
			bool bresult = BlackboardData->GetValueAsBool("testbool");
			FVector temp = BlackboardData->GetValueAsVector("TargetLocation");
			if (bresult)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("True"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("False"));
			}
			//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("%f %f %f"), temp.X, temp.Y, temp.Z));
			//GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("%f %f %f"), Location.X, Location.Y, Location.Z));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%f %f %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));
		}
	}
}

