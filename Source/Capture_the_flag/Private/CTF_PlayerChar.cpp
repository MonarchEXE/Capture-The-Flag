// Fill out your copyright notice in the Description page of Project Settings.


#include "CTF_PlayerChar.h"

// Sets default values
ACTF_PlayerChar::ACTF_PlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	playerCam->SetupAttachment(RootComponent);

	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	playerMesh->SetupAttachment(RootComponent);

	playerHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player Hitbox"));
	playerHitbox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACTF_PlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTF_PlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTF_PlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

