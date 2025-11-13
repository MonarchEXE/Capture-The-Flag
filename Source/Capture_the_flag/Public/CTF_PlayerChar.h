// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "CTF_PlayerChar.generated.h"

UCLASS()
class CAPTURE_THE_FLAG_API ACTF_PlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACTF_PlayerChar();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* playerCam;
	UPROPERTY(EditDefaultsonly)
	UStaticMeshComponent* playerMesh;
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* playerHitbox;

	void MoveXAxis(float axisValue);
	void MoveYAxis(float axisValue);
	//void Jump();
	
};
