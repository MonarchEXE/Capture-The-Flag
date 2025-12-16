// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "EquipmentBase.h"
#include "EquipmentDefinition.generated.h"

/**
 * 
 */

class AEquippableToolBase;
class UInputMappingContext;

UCLASS()
class CAPTURE_THE_FLAG_API UEquipmentDefinition : public UItemDefinition
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEquipmentBase> ToolAsset;

		UFUNCTION()
		virtual UEquipmentDefinition* CreateItemCopy() const override;
	
};
