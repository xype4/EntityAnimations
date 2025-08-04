#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPP_BaseCharacterABP.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterMove_Enum : uint8
{
	Stay		UMETA(DisplayName = "Stay"),
	Move		UMETA(DisplayName = "Move"),
	Swim		UMETA(DisplayName = "Swim"),
	Jump		UMETA(DisplayName = "Jump"),
	Fall		UMETA(DisplayName = "Fall")
};

UENUM(BlueprintType)
enum class ECharacterFoot_Enum : uint8
{
	Right		UMETA(DisplayName = "Right"),
	Left		UMETA(DisplayName = "Left")
};

UCLASS(Blueprintable)
class ENTITYCLASSES_API UCPP_BaseCharacterABP : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Look", meta = (ToolTip = "Смотреть ли на LookAtLocation"))
	bool IsEnableLookAt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Look", meta = (ToolTip = "Точка, на которую направлен взгляд"))
	FVector LookAtLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move", meta = (ToolTip = "Текущий вектор движения"))
	FVector2D MoveVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move", meta = (ToolTip = "Состояние движения"))
	ECharacterMove_Enum MoveState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move|Fall", meta = (ToolTip = "Время последнего падения"))
	float FallTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move|Fall", meta = (ToolTip = "Время для проигрывания анимации тяжелого приземления"))
	float FallTimeToHardLanding = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move|Fall", meta = (ToolTip = "Время для проигрывания анимации неописуемо тяжёного приземления"))
	float FallTimeToPizdezLanding = 1.75f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config|Move", meta = (ToolTip = "Нога впереди"))
	ECharacterFoot_Enum CurrentFoot;
};
