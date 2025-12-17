// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "ItemDefinition.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// UProperty definitions pre-runtime
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	check(PickupMeshComponent != nullptr);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	check(CollisionSphere != nullptr);

	CollisionSphere->SetupAttachment(PickupMeshComponent);
	CollisionSphere->SetSphereRadius(32.f);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup();
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::InitializePickup() {

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("GEngine: %s - Spawning Item."), *GetActorLabel()));
	
	if (PickupDataTable && !PickupItemID.IsNone()) {
		const FItemData* ItemDataRow = PickupDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());

		if (ItemDataRow == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GEngine: %s - Item ID was not found."), *GetActorLabel()));
			UE_LOG(LogTemp, Error, TEXT("APickupBase::InitializePickup(): Item lookup in Data table returns nullptr."));
			return;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("GEngine: %s - Item ID found."), *GetActorLabel()));

		UItemDefinition* TempDefinition = ItemDataRow->ItemBase.Get();

		ReferenceItem = TempDefinition->CreateItemCopy();

		if (TempDefinition->WorldMesh.IsValid()) {
			PickupMeshComponent->SetStaticMesh(TempDefinition->WorldMesh.Get());
		}
		else {
			UStaticMesh* WorldMesh = TempDefinition->WorldMesh.LoadSynchronous();
			PickupMeshComponent->SetStaticMesh(WorldMesh);
		}
		PickupMeshComponent->SetVisibility(true);

		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnSphereBeginOverlap);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("GEngine: %s - Item spawned."), *GetActorLabel()));
	}
	// debug msgs for missing properties for Item Data
	else {
		if (PickupItemID.IsNone()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GEngine: %s - \"Pickup Item ID\" is empty."), *GetActorLabel()));
		}
		if (!(PickupDataTable)) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GEngine: %s - \"Pickup Data table\" is empty."), *GetActorLabel()));
		}
	}
	
}

void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "GEngine: Attempting Item Pickup Collision");
	
	// BP_ThirdPersonCharacter is a blueprint class - cannot be casted; casting using base class
	ACTF_PlayerChar* Character = Cast<ACTF_PlayerChar>(OtherActor);

	if (Character != nullptr) {
		Character->GiveItem(ReferenceItem);
		
		CollisionSphere->OnComponentBeginOverlap.RemoveAll(this);

		PickupMeshComponent->SetVisibility(false);
		PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// sets timer to delay when item respawns
	if (bShouldRespawn) {
		// InitializePickup fine to call again - just makes Static Mesh visible and enables Collision detection.
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBase::InitializePickup, RespawnTime, false, RespawnTime);
	}
}
