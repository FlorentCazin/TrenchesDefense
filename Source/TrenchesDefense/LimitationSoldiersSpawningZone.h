// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "LimitationSoldiersSpawningZone.generated.h"

UCLASS()
class TRENCHESDEFENSE_API ALimitationSoldiersSpawningZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALimitationSoldiersSpawningZone();

	//limitation
	UPROPERTY(BlueprintReadOnly)
	UBoxComponent* BoxLimitation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
