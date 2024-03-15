// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseCharacter.h"

// Sets default values
ATrenchesDefenseCharacter::ATrenchesDefenseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
	IndexMaterialToChange = 0;
	MaxEmissiveColor = 1.f;
	AlreadySpawned = false;
	IsDead = false;
}

// Called when the game starts or when spawned
void ATrenchesDefenseCharacter::BeginPlay()
{
	Super::BeginPlay();
	LifeComponent->LifeInitialization = MaxLife;
	LifeComponent->RegenerateLife();
	CharacterMesh = GetMesh();
}

// Called every frame
void ATrenchesDefenseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrenchesDefenseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
}

void ATrenchesDefenseCharacter::ChangeSoldierColor(FLinearColor color) {
	if (CharacterMesh) {
		//Fisrt material of the mesh
		UMaterialInterface* MaterialToChange = CharacterMesh->GetMaterial(IndexMaterialToChange);
		if (MaterialToChange) {
			//Material is dynamic
			UMaterialInstanceDynamic* MyDynamicMaterialInstance = Cast<UMaterialInstanceDynamic>(MaterialToChange);
			if (!MyDynamicMaterialInstance)
			{
				MyDynamicMaterialInstance = CharacterMesh->CreateAndSetMaterialInstanceDynamic(IndexMaterialToChange);
			}
			if (MyDynamicMaterialInstance)
			{
				MyDynamicMaterialInstance->SetVectorParameterValue("SoldierBodyColor", color);
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Material is not dynamic!"));
			}
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Material to change does not exist! Wrong Index or verify that the material is correctly defined inside the mesh!"));
		}
	}
	else {
		UE_LOG(LogTemp,Log,TEXT("CharacterMesh is not defined!"))
	}
}

void ATrenchesDefenseCharacter::ChangeSoldierEmissive(float emissive) {
	if (CharacterMesh) {
		//Fisrt material of the mesh
		UMaterialInterface* MaterialToChange = CharacterMesh->GetMaterial(IndexMaterialToChange);
		if (MaterialToChange) {
			//Material is dynamic
			UMaterialInstanceDynamic* MyDynamicMaterialInstance = Cast<UMaterialInstanceDynamic>(MaterialToChange);
			//if not dynamic, make it dynamic
			if (!MyDynamicMaterialInstance)
			{
				MyDynamicMaterialInstance = CharacterMesh->CreateAndSetMaterialInstanceDynamic(IndexMaterialToChange);
			}
			if (MyDynamicMaterialInstance)
			{
				MyDynamicMaterialInstance->SetScalarParameterValue("SoldierEmissiveColor", emissive);
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Material is not dynamic!"));
			}
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Material to change does not exist! Wrong Index or verify that the material is correctly defined inside the mesh!"));
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("CharacterMesh is not defined!"))
	}
}

