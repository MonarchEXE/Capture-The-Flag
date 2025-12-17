// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "EquipmentBase.h"
#include "EquipmentDefinition.h"
#include "InventoryComponent.h"

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

	UFUNCTION()
	void GiveItem(UItemDefinition* ItemDefinition);
	
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	TObjectPtr<UInventoryComponent> InventoryComponent;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	bool IsEquipmentAlreadyOwned(UEquipmentDefinition* EquipmentDefinition);

	UFUNCTION() 
	void AttachTool(UEquipmentDefinition* EquipmentDefinition);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tools)
	TObjectPtr<AEquipmentBase> EquippedItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction>UseAction;

private:	
	
};
