// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterDataAsset.h"
#include "LifeComponent.h"
#include "SoldierDataAsset.h"
#include "TrenchesDefenseCharacter.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesDefenseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrenchesDefenseCharacter();

	USkeletalMeshComponent* CharacterMesh;

	//Index of the material to change his color
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category="MaterialCharacterProperties")
	int IndexMaterialToChange;

	//Max emissive color value for the spawning/select system
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "MaterialCharacterProperties")
	float MaxEmissiveColor;

	//Color of the character where's outside the spawning limitation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "MaterialCharacterProperties")
	FLinearColor ColorOutOfLimitation;

	//Color of the character where's inside the spawning limitation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "MaterialCharacterProperties")
	FLinearColor ColorInsideLimitation;

	//Default color of the character
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "MaterialCharacterProperties")
	FLinearColor DefaultColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperties")
	UCharacterDataAsset *CharacterDataAsset;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterProperties")
	ULifeComponent *LifeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierProperties")
	USoldierDataAsset* SoldierDataAsset;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterProperties")
	bool IsDead;

	UPROPERTY(BlueprintReadOnly, Category = "CharacterProperties")
	int MaxLife;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeSoldierColor(FLinearColor color);

	void ChangeSoldierEmissive(float emissive);



};
