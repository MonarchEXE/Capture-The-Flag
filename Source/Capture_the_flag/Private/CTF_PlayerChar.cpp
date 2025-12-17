// Fill out your copyright notice in the Description page of Project Settings.


#include "CTF_PlayerChar.h"

// Sets default values
ACTF_PlayerChar::ACTF_PlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	check(InventoryComponent != nullptr);
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

bool ACTF_PlayerChar::IsEquipmentAlreadyOwned(UEquipmentDefinition* EquipmentDefinition) {
	for (UEquipmentDefinition* InventoryItem : InventoryComponent->EquipmentInventory) {
		if (EquipmentDefinition->ID.ToString() == InventoryItem->ID.ToString()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Player: Item is already in inventory.");
			return true;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Player: Item not in inventory.");
	return false;
}

void ACTF_PlayerChar::AttachTool(UEquipmentDefinition* EquipmentDefinition) {
	if (!IsEquipmentAlreadyOwned(EquipmentDefinition)) {
		AEquipmentBase* ToolToEquip = GetWorld()->SpawnActor<AEquipmentBase>(EquipmentDefinition->ToolAsset, this->GetActorTransform());
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

		ToolToEquip->AttachToActor(this, AttachmentRules);

		ToolToEquip->OwningCharacter = this;

		InventoryComponent->EquipmentInventory.Add(EquipmentDefinition);
		
		EquippedItem = ToolToEquip;
		
		// Get the player controller for this character
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(ToolToEquip->MappingContext, 1);
			}
		}

		ToolToEquip->BindInputAction(UseAction);
	}

}

void ACTF_PlayerChar::GiveItem(UItemDefinition* ItemDefinition) {
	switch (ItemDefinition->ItemType) {
	case EItemType::Tool: {
		UEquipmentDefinition* ToolDefinition = Cast<UEquipmentDefinition>(ItemDefinition);
		if (ToolDefinition != nullptr) {
			//AttachTool(ToolDefinition);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("GEngine: %s - Successfully cast \"%s\" instance to tool."), *GetActorLabel(), *ItemDefinition->ID.ToString()));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("GEngine: %s - Failed to cast \"%s\" instance to tool."), *GetActorLabel(), *ItemDefinition->ID.ToString()));
		}
		
		break;
	}
	case EItemType::Consumable: {
		break;
	}
	case EItemType::Flag: {
		break;
	}
	default: {
		break;
	}
	}
}