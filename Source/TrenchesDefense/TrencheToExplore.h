// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrencheToExplore.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrencheToExplore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrencheToExplore();

	//actual number of zombies inside the trenche
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ActualNumberInsideTrenche = 0;

	//cost
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int NumberMaxInsideTrenche;

	//if mutli -> tag ally/ennemy

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
