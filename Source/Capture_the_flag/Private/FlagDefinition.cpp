// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagDefinition.h"

UFlagDefinition* UFlagDefinition::CreateItemCopy() const {
	
	UFlagDefinition* FlagCopy = NewObject<UFlagDefinition>(StaticClass());

	FlagCopy->ID = this->ID;
	FlagCopy->ItemText = this->ItemText;
	FlagCopy->ItemType = this->ItemType;
	FlagCopy->WorldMesh = this->WorldMesh;
	FlagCopy->FlagAsset = this->FlagAsset;

	return FlagCopy; 

}