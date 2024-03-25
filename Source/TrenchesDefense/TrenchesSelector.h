// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrencheToExplore.h"
#include "TrenchesSelector.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesSelector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrenchesSelector();

	//You need to initialize trenches in the world yourself due to specific cases.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category="Trenche Selector")
	TArray<ATrencheToExplore*> TrenchesToExploreArray;

	//Score from previous round of the trenches
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ATrencheToExplore*> TrencheToExploreOrderScoreArray;

	//total trenche
	int numberOfTrencheToExplore;

	//total enemies
	int totalEnemies;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//work for 5 trenches
	UFUNCTION(BlueprintCallable)
	void SetTrenchesValues();

	void GiveToTrenche(ATrencheToExplore* trencheGiver, ATrencheToExplore* trencheReceiver, float percentage);

	UFUNCTION(BlueprintCallable)
	ATrencheToExplore *GetTrenche();

};
