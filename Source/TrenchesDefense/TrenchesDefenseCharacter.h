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

	//return true if success
	UFUNCTION(BlueprintCallable)
	virtual bool Attack(TArray<ATrenchesDefenseCharacter*> targets);

	//return true if success
	UFUNCTION(BlueprintCallable)
	bool GoTo(FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void Die();

};
