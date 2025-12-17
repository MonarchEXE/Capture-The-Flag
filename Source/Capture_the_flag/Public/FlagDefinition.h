// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"

#include "FlagBase.h"

#include "FlagDefinition.generated.h"

/**
 * 
 */
UCLASS()
class CAPTURE_THE_FLAG_API UFlagDefinition : public UItemDefinition
{
	GENERATED_BODY()

	public:
		UFUNCTION()
		virtual UFlagDefinition* CreateItemCopy() const override;

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AFlagBase> FlagAsset;
	
};
