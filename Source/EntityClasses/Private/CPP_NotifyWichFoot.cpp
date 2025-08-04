// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_NotifyWichFoot.h"



void UCPP_NotifyWichFoot::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (ACPP_BaseCharacter* Character = dynamic_cast<ACPP_BaseCharacter*>(MeshComp->GetOwner()))
	{
		if (UCPP_BaseCharacterABP* CharacterABP = dynamic_cast<UCPP_BaseCharacterABP*>(Character->GetMesh()->GetAnimInstance()))
		{
			CharacterABP->CurrentFoot = Foot;
		}
	}
}