#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CPP_BaseCharacterABP.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CPP_BaseCharacter.generated.h"

UCLASS()
class ENTITYCLASSES_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_BaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ToolTip = "Кость к которой аттачатся камеры"))
	FName HeadBoneName = TEXT("head");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "2.5", ToolTip = "Время перехода из FPV в TPV и наоборот"))
	float timeToChangeView = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "0.25", ToolTip = "Шаг по альфе при вызове функции ChangeThridCameraDistance"))
	float thridViewRegulateStep = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "1.0", ToolTip = "Текущее расстояние до камеры в ThridPersonView"))
	float currentThridPersonDistance = 0.5f;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "10000", ToolTip = "Границы расстояния до камеры в ThridPersonView"))
	FVector2D  ThridPersonMinMax = FVector2D(100.0f, 350.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "5.0", ToolTip = "Скорость доворота тела относительно головы"))
	float normalizingSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "90", ToolTip = "Абсолютное отклонение по горизонтале головы при скорости от 0 до 1"))
	FVector2D  HorizontalAbsClamp = FVector2D(15.0f, 50.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "100", ToolTip = "Абсолютное отклонение по вертикале головы при скорости от 0 до 1"))
	FVector2D  VerticalAbsClamp = FVector2D(75.0f, 75.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "5.0", ToolTip = "Чувствительность мыши"))
	float mouseSensetive = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "150.0", ToolTip = "Высота шага в полёте"))
	float fallStepHeight = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0.0", ClampMax = "150.0", ToolTip = "Высота шага на земле"))
	float onGroundStepHeight = 4.0f;



	UPROPERTY(BlueprintReadOnly, Category = "Other", meta = (ToolTip = "Сейчас вид от 3 лица"))
	bool isThridView = false;

	UPROPERTY(BlueprintReadOnly, Category = "Other", meta = (ToolTip = "Текущий нормализованный вектор перемещения"))
	FVector2D MoveVector = FVector2D(0.0f, 0.0f);

	UPROPERTY(BlueprintReadOnly, Category = "Other", meta = (ToolTip = "Текущий вектор перемещения мыши"))
	FVector2D MouseVector = FVector2D(0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, Category = "Other", meta = (ToolTip = "Текущее состояние перемещения"))
	ECharacterMove_Enum MoveState;

	UPROPERTY(BlueprintReadWrite, Category = "Other", meta = (ToolTip = "Базовый анимблупринт"))
	UCPP_BaseCharacterABP* AnimBlueprintBase;

	UPROPERTY(BlueprintReadWrite, Category = "Other", meta = (ToolTip = "Базовый плеерконтроллер"))
	APlayerController* PlayerControllerBase;


public:

	UFUNCTION(BlueprintCallable, Category = "Public", meta= (ToolTip = "Изменить вид камеры (1-3 лицо)"))
	void ChangeCameraView(bool ThridPerson, bool Force);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Регулировать сторону, в которую сместится камера от 3 лица"))
	void ChangeThridCameraDistance(float Direction);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение смещения камеры от 3 лица"))
	void SetThridCameraDistance(float Alpha);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение движения мыши"))
	void MouseInput(FVector2D Value);

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение движения мыши"))
	void JumpInput();

	UFUNCTION(BlueprintCallable, Category = "Public", meta = (ToolTip = "Установить значение альфы перемещения"))
	void MovementInput(FVector2D Value, float MoveMultiply);

protected:
	// множитель доворота персонажа к камере, увеличивающийся по мере доворота
	float rotationSmooth = 0.0f;

	// угол доворота на предыдущем кадре
	float oldRotationAngle = 0.0f;

	//Доворот завершён
	bool equalizindEnded = true;
	bool equalizindNeedEnd = true;

	//Время в падении
	float fallTime = 0.0f;

	


	/*
	Поворот камеры

	@params HorizontalClamp - Границы по горизонтале
	VerticalClamp - Границы по вертикале
	MouseInput - Инпут мыши
	DisovewflowClampSpeed - Скорость перехода к максимальному клампу, если текущее значение оказывается больше клампа
	*/
	void RotateCamera(FVector2D HorizontalClamp, FVector2D VerticalClamp, FVector2D MouseInput, float DisovewflowClampSpeed = 1.0f);


	/*
	Выравнивание тела относительно головы при старте движения

	@params MinEqualizingAngle - Минимальный угол при котором будет происходить выравнивание
	EqualizingSpeedMultiply - Множитель к скорости поворота
	SmoothSpeedMultiply - Множитель к скорости набора максимальной скорости доворота
	*/

	void EqualizationControllerToCamera(float MinEqualizingAngle = 5.0f, float EqualizingSpeedMultiply = 3.0f, float DeltaSeconds = 0.0f, float SmoothSpeedMultiply = 2.0f);


	/*
	Поворот головы
	@params HeadVerticalClamp - Границы в которых поворот осуществляется головой. Вычисляет targetLocation и передаёт в ABP
	*/
	void CalculateHeadRotation(FVector2D HeadVerticalClamp);

};
