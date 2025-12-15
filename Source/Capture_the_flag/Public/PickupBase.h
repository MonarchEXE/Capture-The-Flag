// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

//#include "BP_ThirdPersonCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

#include "PickupBase.generated.h"

class UItemDefinition;

UCLASS()
class CAPTURE_THE_FLAG_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Table")
	FName PickupItemID;
	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Table")
	TSoftObjectPtr<UDataTable> PickupDataTable;
	UPROPERTY(VisibleAnywhere, Category = "Pickup | Reference Item")
	TObjectPtr<UItemDefinition> ReferenceItem;

	UPROPERTY(VisibleDefaultsOnly, Category = "Pickup | Mesh")
	TObjectPtr<UStaticMeshComponent> PickupMeshComponent;
	UPROPERTY(EditAnywhere, Category = "Pickup | Components")
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "Pickup | Respawn")
	bool bShouldRespawn;
	UPROPERTY(EditAnywhere, Category = "Pickup | Respawn")
	float RespawnTime = 4.0f;

	FTimerHandle RespawnTimerHandle;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
 