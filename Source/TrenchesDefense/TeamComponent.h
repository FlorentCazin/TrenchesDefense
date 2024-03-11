// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectifToReach.h"
#include "TeamComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TRENCHESDEFENSE_API UTeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeamComponent();

	//Team name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TeamProperties")
	FString name;

	//Objectif to reach (necessary for multiplayer)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeamProperties")
	FVector ObjectifToReach;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
