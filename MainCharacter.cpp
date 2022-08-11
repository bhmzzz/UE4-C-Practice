// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	InitPlayer();//初始化玩家
	
}

void AMainCharacter::InitPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 80.0f);
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetMesh());
	CameraArm->TargetArmLength = 300.0f;
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 3;

	camera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("camera1"));
	camera1->SetupAttachment(CameraArm, USpringArmComponent::SocketName);//USpringArmComponent::SocketName处于弹簧臂末端的位置。
	camera1->bUsePawnControlRotation = false; //关闭摄像机的跟随旋转


	//保证控制器不会随着视角反转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
	GetCharacterMovement()->JumpZVelocity = 600.0f;//设置跳跃的速度
	GetCharacterMovement()->AirControl = 0.2f;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	USkeletalMeshComponent* PlayerMesh = GetMesh();
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(PlayerMesh,FName("WeaponBack"));

	bIsEquip = false;
	bIsAttacking = false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	MontageNeedToJump = "";
	PlayerStateTemp = Cast<AMainPlayerState>(GetPlayerState());
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AMainCharacter::CombatNotifyBegin);
	animInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &AMainCharacter::CombatNotifyEnd);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AttackCheck();

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Forward", this, &AMainCharacter::Move_Forward);
	PlayerInputComponent->BindAxis("Move_Right", this, &AMainCharacter::Move_Right);
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::PlayerTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::PlayerLookUp);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &AMainCharacter::PlayerJumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::PlayerJumpEnd);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::PlayerAttack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::SetRUN);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::SetWALK);


}

void AMainCharacter::PlayerTurn(float value)
{
	AddControllerYawInput(value);
}

void AMainCharacter::PlayerLookUp(float value)
{
	AddControllerPitchInput(value);
}

void AMainCharacter::PlayerJumpStart()
{
	Jump();
}

void AMainCharacter::PlayerJumpEnd()
{
	StopJumping();
}

void AMainCharacter::PlayerAttack()
{
	if (bIsEquip)
	{
		SetFIGHT();
		InitSocketLocation();
		ClearTargetEnemy();
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (!bIsAttacking && AnimInstance && !(AnimInstance->Montage_IsPlaying(PlayerAttackAnim)))
		{
			bIsAttacking = true;
			AnimInstance->Montage_Play(PlayerAttackAnim);
			MontageEndedDelegate.BindUObject(this, &AMainCharacter::AttackEnded);
			AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate);
		}
		else if (bIsAttacking && AnimInstance)
		{
			MontageNeedToJump = AnimInstance->Montage_GetCurrentSection();
			if (MontageNeedToJump == "Attack1S")
			{
				AnimInstance->Montage_SetNextSection(MontageNeedToJump, FName("Attack2S"));
			}
			else if (MontageNeedToJump == "Attack1E")
			{
				AnimInstance->Montage_SetNextSection(MontageNeedToJump, FName("End"));
			}
			else if (MontageNeedToJump == "Attack2S")
			{
				AnimInstance->Montage_SetNextSection(MontageNeedToJump, FName("Attack3S"));
			}
			else if (MontageNeedToJump == "Attack2E")
			{
				AnimInstance->Montage_SetNextSection(MontageNeedToJump, FName("End"));
			}
		}
	}
	else
	{
		EquipWeapon();
	}
}

void AMainCharacter::EquipWeapon()
{
	bIsEquip = true;
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	UWorld* world = GetWorld();
	DisableInput(UGameplayStatics::GetPlayerController(world,0));
	animInstance->Montage_Play(PlayerEquipAnim);
	MontageEndedDelegate.BindUObject(this, &AMainCharacter::EquipEnded);
	animInstance->Montage_SetEndDelegate(MontageEndedDelegate);
}

void AMainCharacter::AttackEnded(UAnimMontage* Montage, bool bValue)
{
	GEngine->AddOnScreenDebugMessage(2,5.f,FColor::Green,FString::Printf(TEXT("Value: %s"),"AttackEnded"));
	bIsAttacking = false;
}

void AMainCharacter::EquipEnded(UAnimMontage* montage, bool bInterrupted)
{
	UWorld* world = GetWorld();
	EnableInput(UGameplayStatics::GetPlayerController(world,0));
}

void AMainCharacter::AttackCheck()
{
	if (bIsAttacking)
	{
		UWorld* world = GetWorld();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("TEST: %s"),"ATTACK!"));
		TargetTypes.AddUnique(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
		TArray<AActor*> ActorToIngore;
		ActorToIngore.AddUnique(this);
		TArray<FHitResult> OutHits;
		for (int i = 0; i < socketLocation.Num(); ++i)
		{
			if (UKismetSystemLibrary::LineTraceMultiForObjects(world, socketLocation[i], WeaponMesh->GetSocketLocation(WeaponMesh->GetAllSocketNames()[i]), TargetTypes, false, ActorToIngore, EDrawDebugTrace::ForDuration, OutHits, true))
			{
				AddTargetEnemy(OutHits);
			}
		}
		InitSocketLocation();
	}
}

//初始化武器插槽位置。
void AMainCharacter::InitSocketLocation()
{
	socketLocation.Empty();
	socketsName = WeaponMesh->GetAllSocketNames();
	for (auto Iter = socketsName.begin(); Iter != socketsName.end(); ++Iter)
	{
		socketLocation.AddUnique(WeaponMesh->GetSocketLocation(*Iter));
	}
}

void AMainCharacter::AddTargetEnemy(TArray<FHitResult> OutHits)
{
	if (OutHits.Num() != 0)
	{
		for (auto result : OutHits)
		{
			TargetEnemy.AddUnique(Cast<AEnemyCharacter>(result.GetActor()));
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Green,FString::Printf(TEXT("%s"),*result.Actor->GetName()));
		}
	}
}

void AMainCharacter::ClearTargetEnemy()
{
	TargetEnemy.Empty();
}

UStaticMeshComponent* AMainCharacter::GetWeapon()
{
	return WeaponMesh;
}

void AMainCharacter::SetNULL()
{
	if(PlayerStateTemp)
	PlayerStateTemp->SetNULL();
}

void AMainCharacter::SetWALK()
{
	if (PlayerStateTemp)
	GetCharacterMovement()->MaxWalkSpeed = 300;
	PlayerStateTemp->SetWALK();
}

void AMainCharacter::SetRUN()
{
	if (PlayerStateTemp)
	GetCharacterMovement()->MaxWalkSpeed = 500;
	PlayerStateTemp->SetRUN();
}

void AMainCharacter::SetFIGHT()
{
	if (PlayerStateTemp)
	PlayerStateTemp->SetFIGHT();
}

void AMainCharacter::CombatNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "Combat1" || NotifyName == "Combat2" || NotifyName == "Combat3")
	GetWorldTimerManager().SetTimer(handler,this, &AMainCharacter::AttackCheck,GetWorld()->GetDeltaSeconds(),true);
}

void AMainCharacter::CombatNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "Combat1" || NotifyName == "Combat2" || NotifyName == "Combat3")
	GetWorldTimerManager().ClearTimer(handler);
}



void AMainCharacter::Move_Forward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator ConRotator = Controller->GetControlRotation();
		const FRotator YawRotation(0, ConRotator.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}

}

void AMainCharacter::Move_Right(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator ConRotator = Controller->GetControlRotation();
		const FRotator YawRotation(0, ConRotator.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}


