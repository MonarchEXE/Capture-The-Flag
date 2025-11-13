// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CTF_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURE_THE_FLAG_API ACTF_PlayerController : public APlayerController
{
	GENERATED_BODY()

	protected:
		void BeginPlay();

	private:
		virtual ~ACTF_PlayerController() = default;
		void MovementInput();
	
};
