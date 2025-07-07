// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CPP_BaseCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterMove_Enum : uint8
{
	Stay		UMETA(DisplayName = "Stay"),
	Move		UMETA(DisplayName = "Move"),
	Swim		UMETA(DisplayName = "Swim"),
	Jump		UMETA(DisplayName = "Jump"),
	Fall		UMETA(DisplayName = "Fall")
};

UCLASS()
class ENTITYCLASSES_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_BaseCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Protected", meta = (ToolTip = "Инициализация переменных"))
	void InitVariables();
	

public:	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_ThridPersonCameraHorizontalRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_ThridPersonCameraVerticalRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_ThridPersonCameraRoot;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_FirstPersonRotatorRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_FirstPersonCameraHorizontalRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_FirstPersonCameraVerticalRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SC_FirstPersonCameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ToolTip = "Кость к которой аттачатся камеры"))
	FName HeadBoneName = TEXT("head");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ToolTip = "Текущий вид камеры"))
	bool isThridView = false;		

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "10.0", ToolTip = "Время перехода из FPV в TPV и наоборот"))
	float timeToChangeView = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "Текущее расстояние до камеры в ThridPersonView"))
	float currentThridPersonDistance = 0.5f;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "10000", ToolTip = "Границы расстояния до камеры в ThridPersonView"))
	FVector2D  ThridPersonMinMax = FVector2D(100.0f, 350.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Other", meta = (ToolTip = "Текущий нормализованный вектор перемещения"))
	FVector2D MoveVector = FVector2D(0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, Category = "Other", meta = (ToolTip = "Текущее состояние перемещения"))
	ECharacterMove_Enum MoveState;


	UFUNCTION(BlueprintCallable, Category = "Public", meta= (ToolTip = "Изменить вид камеры"))
	void ChangeCameraView(bool ThridPerson, bool Force);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Регулировать сторону, в которую сместится камера от 3 лица"))
	void ChangeThridCameraDistance(float Direction);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение смещения камеры от 3 лица"))
	void SetThridCameraDistance(float Alpha);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение альфы перемещения"))
	FVector2D CalculateMovementDirection(FVector2D Value, float MoveMultiply);


	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Поворот сценкомпонентов камеры. Кламп по горизонтале для поворота головы скелета"))
	void RotateCamera(FVector2D HorizontalClamp, FVector2D VerticalClamp, FVector2D MouseInput, float DisovewflowClampSpeed = 1.0f, APlayerController* PlayerController = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Выравнивание контроллера относительно павна"))
	void EqualizationControllerToCamera(float MinEqualizingAngle = 5.0f, float EqualizingSpeedMultiply = 3.0f, float DeltaSeconds = 0.0f, float SmoothSpeedMultiply = 2.0f, APlayerController* PlayerController = nullptr);
	// множитель доворота персонажа к камере, увеличивающийся по мере доворота
	float rotationSmooth = 0.0f;
	// угол доворота на предыдущем кадре
	float oldRotationAngle = 0.0f;
	//Доворот завершён
	bool equalizindEnded = true;
	bool equalizindNeedEnd = true;

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Поворот головы скелета в сторону взгляда"))
	FVector CalculateHeadRotation(FVector2D HeadVerticalClamp);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
