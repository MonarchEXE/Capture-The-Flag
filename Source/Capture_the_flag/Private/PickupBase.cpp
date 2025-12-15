// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "ItemDefinition.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (PickupDataTable && !PickupItemID.IsNone()) {
		const FItemData* ItemDataRow = PickupDataTable->FindRow<FItemData>(PickupItemID, PickupItemID.ToString());

		ReferenceItem = NewObject<UItemDefinition>(this, UItemDefinition::StaticClass());

		ReferenceItem->ID = ItemDataRow->ID;
		ReferenceItem->ItemType = ItemDataRow->ItemType;
		ReferenceItem->ItemText = ItemDataRow->ItemText;
		ReferenceItem->WorldMesh = ItemDataRow->ItemBase->WorldMesh;

		if (ItemDataRow == nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "GEngine: Item data was not found.");
			UE_LOG(LogTemp, Error, TEXT("ItemBase is null in DataTable"));
			return;
		}

		UItemDefinition* TempDefinition = ItemDataRow->ItemBase.Get();
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

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "GEngine: Item Spawned.");
	}
}

void APickupBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "GEngine: Attempting Item Pickup Collision");
	
	// BP_ThirdPersonCharacter is a blueprint class - cannot be casted; casting using base class
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character != nullptr) {
		CollisionSphere->OnComponentBeginOverlap.RemoveAll(this);

		PickupMeshComponent->SetVisibility(false);
		PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (bShouldRespawn) {
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &APickupBase::InitializePickup, RespawnTime, false, 0);
	}
}
