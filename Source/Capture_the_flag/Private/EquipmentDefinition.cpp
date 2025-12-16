// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentDefinition.h"

UEquipmentDefinition* UEquipmentDefinition::CreateItemCopy() const {

	UEquipmentDefinition* EquipmentCopy = NewObject<UEquipmentDefinition>(StaticClass());

	EquipmentCopy->ID = this->ID;
	EquipmentCopy->ItemText = this->ItemText;
	EquipmentCopy->ItemType = this->ItemType;
	EquipmentCopy->WorldMesh = this->WorldMesh;

	return EquipmentCopy;
}