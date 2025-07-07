// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "FL_CharacterHelper.h"




// Sets default values
ACPP_BaseCharacter::ACPP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SC_FirstPersonRotatorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SC_FirstPersonRotatorRootComponent"));
	SC_FirstPersonCameraHorizontalRotator = CreateDefaultSubobject<USceneComponent>(TEXT("SC_FirstPersonCameraHorizontalRotatorComponent"));
	SC_FirstPersonCameraVerticalRotator = CreateDefaultSubobject<USceneComponent>(TEXT("SC_FirstPersonCameraVerticalRotatorComponent"));
	SC_FirstPersonCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SC_FirstPersonCameraRootComponent"));

	//SC_FirstPersonRotatorRoot->SetupAttachment(GetMesh(), HeadBoneName);
	SC_FirstPersonRotatorRoot->SetupAttachment(GetMesh());
	SC_FirstPersonCameraHorizontalRotator->SetupAttachment(SC_FirstPersonRotatorRoot);
	SC_FirstPersonCameraVerticalRotator->SetupAttachment(SC_FirstPersonCameraHorizontalRotator);
	SC_FirstPersonCameraRoot->SetupAttachment(SC_FirstPersonCameraVerticalRotator);


	SC_ThridPersonCameraHorizontalRotator = CreateDefaultSubobject<USceneComponent>(TEXT("SC_ThridPersonCameraHorizontalRotatorComponent"));
	SC_ThridPersonCameraVerticalRotator = CreateDefaultSubobject<USceneComponent>(TEXT("SC_ThridPersonCameraVerticalRotatorComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SC_ThridPersonCameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SC_ThridPersonCameraRootComponent"));

	SC_ThridPersonCameraHorizontalRotator->SetupAttachment(GetMesh());
	SC_ThridPersonCameraVerticalRotator->SetupAttachment(SC_ThridPersonCameraHorizontalRotator);
	SpringArm->SetupAttachment(SC_ThridPersonCameraVerticalRotator);
	SC_ThridPersonCameraRoot->SetupAttachment(SpringArm);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(isThridView? SC_ThridPersonCameraRoot: SC_FirstPersonCameraRoot);
}

void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitVariables();
}

void ACPP_BaseCharacter::ChangeCameraView(bool ThridPerson, bool Force)
{
	if(Force)
	{
		isThridView = ThridPerson;
		Camera->AttachToComponent(isThridView ? SC_ThridPersonCameraRoot : SC_FirstPersonCameraRoot, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		UWorld* World = GetWorld();
		if (!World) return;

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController && PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, timeToChangeView / 2, FLinearColor::Black, false, true);

			FTimerHandle FadeTimerHandle;
			FTimerDelegate FadeDelegate;


			FadeDelegate.BindLambda([PlayerController, ThridPerson, this]()
				{
					this->isThridView = ThridPerson;
					Camera->AttachToComponent(this->isThridView ? this->SC_ThridPersonCameraRoot : this->SC_FirstPersonCameraRoot, FAttachmentTransformRules::KeepRelativeTransform);
					PlayerController->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, this->timeToChangeView/2, FLinearColor::Black, false, true);
				});

			World->GetTimerManager().SetTimer(FadeTimerHandle, FadeDelegate, timeToChangeView / 2, false);
		}
	}
}

void ACPP_BaseCharacter::ChangeThridCameraDistance(float Direction)
{
	if(isThridView)
		SetThridCameraDistance(currentThridPersonDistance+Direction);
}

void ACPP_BaseCharacter::SetThridCameraDistance(float Alpha)
{
	currentThridPersonDistance = FMath::Clamp(Alpha, 0.0f, 1.0f);
	SpringArm->TargetArmLength = FMath::Lerp(ThridPersonMinMax.X, ThridPersonMinMax.Y, currentThridPersonDistance);
}

FVector2D ACPP_BaseCharacter::CalculateMovementDirection(FVector2D Value, float MoveMultiply)
{
	MoveVector = Value.GetSafeNormal() * FMath::Clamp(MoveMultiply, 0.0f, 1.0f);
	return MoveVector;
}

void ACPP_BaseCharacter::RotateCamera(FVector2D HorizontalClamp, FVector2D VerticalClamp, FVector2D MouseInput, float DisovewflowClampSpeed, APlayerController* PlayerController)
{
	USceneComponent* VerticalRotator = isThridView ? SC_ThridPersonCameraVerticalRotator : SC_FirstPersonCameraVerticalRotator;

	float VerticalCurrentPitch = VerticalRotator->GetRelativeRotation().Pitch;

	if (VerticalCurrentPitch > VerticalClamp.Y || VerticalCurrentPitch < VerticalClamp.X)
	{
		VerticalCurrentPitch = (FMath::Abs(VerticalCurrentPitch) - DisovewflowClampSpeed) * FMath::Sign(VerticalCurrentPitch);
	}
	else
	{
		VerticalCurrentPitch += MouseInput.Y;
		VerticalCurrentPitch = FMath::Clamp(VerticalCurrentPitch, VerticalClamp.X, VerticalClamp.Y);
	}
	


	SC_ThridPersonCameraVerticalRotator->SetRelativeRotation(FRotator(VerticalCurrentPitch, SC_ThridPersonCameraVerticalRotator->GetRelativeRotation().Yaw, SC_ThridPersonCameraVerticalRotator->GetRelativeRotation().Roll));
	SC_FirstPersonCameraVerticalRotator->SetRelativeRotation(FRotator(VerticalCurrentPitch, SC_FirstPersonCameraVerticalRotator->GetRelativeRotation().Yaw, SC_FirstPersonCameraVerticalRotator->GetRelativeRotation().Roll));


	USceneComponent* HorizontalRotator = isThridView ? SC_ThridPersonCameraHorizontalRotator : SC_FirstPersonCameraHorizontalRotator;

	float HorizontalCurrentYaw = HorizontalRotator->GetRelativeRotation().Yaw;
	float HorizontalCurrentYawClamped = 0.0f;
	float YawOverflow = 0.0f;

	if (HorizontalCurrentYaw > HorizontalClamp.Y || HorizontalCurrentYaw < HorizontalClamp.X)
	{ 
		HorizontalCurrentYawClamped = HorizontalCurrentYaw;
		YawOverflow += MouseInput.X;
	}
	else
	{
		HorizontalCurrentYaw += MouseInput.X;
		HorizontalCurrentYawClamped = FMath::Clamp(HorizontalCurrentYaw, HorizontalClamp.X, HorizontalClamp.Y);

		SC_ThridPersonCameraHorizontalRotator->SetRelativeRotation(FRotator(SC_ThridPersonCameraHorizontalRotator->GetRelativeRotation().Pitch, HorizontalCurrentYawClamped, SC_ThridPersonCameraHorizontalRotator->GetRelativeRotation().Roll));
		SC_FirstPersonCameraHorizontalRotator->SetRelativeRotation(FRotator(SC_FirstPersonCameraHorizontalRotator->GetRelativeRotation().Pitch, HorizontalCurrentYawClamped, SC_FirstPersonCameraHorizontalRotator->GetRelativeRotation().Roll));

		YawOverflow = (FMath::Abs(HorizontalCurrentYawClamped) - FMath::Abs(HorizontalCurrentYaw)) * FMath::Sign(HorizontalCurrentYaw) * -1;
	}

	if(FMath::Abs(YawOverflow)>0.001f)

		PlayerController->SetControlRotation(FRotator(PlayerController->GetControlRotation().Pitch, PlayerController->GetControlRotation().Yaw + YawOverflow, PlayerController->GetControlRotation().Roll));
}

void ACPP_BaseCharacter::EqualizationControllerToCamera(float MinEqualizingAngle, float EqualizingSpeedMultiply, float DeltaSeconds, float SmoothSpeedMultiply, APlayerController* PlayerController)
{
	USceneComponent* HorizontalRotator = isThridView ? SC_ThridPersonCameraHorizontalRotator : SC_FirstPersonCameraHorizontalRotator;

	if(MoveState == ECharacterMove_Enum::Move)
	{
		equalizindEnded = false;

		if(!FMath::IsNearlyEqual(HorizontalRotator->GetRelativeRotation().Yaw, 0.0f, MinEqualizingAngle))
		{
			rotationSmooth = FMath::Clamp(rotationSmooth + (DeltaSeconds * SmoothSpeedMultiply),0.0f,1.0f);	//Увеличение множителя для сглаживания

			float rotationAngleClampAbs = MoveVector.Length() * EqualizingSpeedMultiply * rotationSmooth;	//Вычисление максимального воззможного доворота на кадре
			float rotationAngle = FMath::Clamp(HorizontalRotator->GetRelativeRotation().Yaw, -rotationAngleClampAbs, rotationAngleClampAbs);	// Вычисление реального доворота на кадре

			PlayerController->SetControlRotation(FRotator(PlayerController->GetControlRotation().Pitch, PlayerController->GetControlRotation().Yaw + rotationAngle, PlayerController->GetControlRotation().Roll));

			float cameraRotaionAngle = HorizontalRotator->GetRelativeRotation().Yaw + (-oldRotationAngle);

			SC_ThridPersonCameraHorizontalRotator->SetRelativeRotation(FRotator(SC_ThridPersonCameraHorizontalRotator->GetRelativeRotation().Pitch, cameraRotaionAngle, SC_ThridPersonCameraHorizontalRotator->GetRelativeRotation().Roll));
			SC_FirstPersonCameraHorizontalRotator->SetRelativeRotation(FRotator(SC_FirstPersonCameraHorizontalRotator->GetRelativeRotation().Pitch, cameraRotaionAngle, SC_FirstPersonCameraHorizontalRotator->GetRelativeRotation().Roll));

			oldRotationAngle = rotationAngle;
		}
		else
		{
			equalizindNeedEnd = true;
		}
	}
	else
	{
		equalizindNeedEnd = true;
	}
	
	if(equalizindEnded == false && equalizindNeedEnd == true)
	{
		equalizindEnded = true;
		equalizindNeedEnd = false;

		rotationSmooth = 0;

		float cameraRotaionAngle = HorizontalRotator->GetRelativeRotation().Yaw + (-oldRotationAngle);
		HorizontalRotator->SetRelativeRotation(FRotator(HorizontalRotator->GetRelativeRotation().Pitch, cameraRotaionAngle, HorizontalRotator->GetRelativeRotation().Roll));

		oldRotationAngle = 0;
	}
}
FVector ACPP_BaseCharacter::CalculateHeadRotation(FVector2D HeadVerticalClamp)
{

	SC_FirstPersonRotatorRoot->SetWorldLocation(GetMesh()->GetSocketLocation(HeadBoneName));


	FTransform meshTransform = GetMesh()->GetComponentTransform();

	USceneComponent* HeadLocationComponent = SC_FirstPersonCameraRoot;

	FRotator UnclampedRotation = UKismetMathLibrary::MakeRotationFromAxes(SC_FirstPersonCameraRoot->GetForwardVector(), SC_FirstPersonCameraRoot->GetRightVector(), SC_FirstPersonCameraRoot->GetUpVector());
	FRotator ClampedRotation = FRotator(FMath::Clamp(UnclampedRotation.Pitch, HeadVerticalClamp.X, HeadVerticalClamp.Y), UnclampedRotation.Yaw, UnclampedRotation.Roll);

	FVector lookWorldPoint = (ClampedRotation.Vector()* 100) + HeadLocationComponent->GetComponentLocation();

	return meshTransform.InverseTransformPosition(lookWorldPoint);
}

void ACPP_BaseCharacter::InitVariables()
{

}


void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

