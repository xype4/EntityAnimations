// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CPP_BaseCharacterABP.h"
#include "CPP_BaseCharacter.h"

#include "CPP_NotifyWichFoot.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class ENTITYCLASSES_API UCPP_NotifyWichFoot : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	ECharacterFoot_Enum Foot;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};