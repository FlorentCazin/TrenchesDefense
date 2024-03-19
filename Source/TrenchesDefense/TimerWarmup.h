// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "TimerWarmup.generated.h"


UCLASS()
class TRENCHESDEFENSE_API ATimerWarmup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATimerWarmup();

	UPROPERTY(BlueprintReadOnly, category = "timer warmup")
	UTextRenderComponent* TimerText;

	UPROPERTY(BlueprintReadOnly, category = "timer warmup")
	int TimeInSeconds;

	int ActualTime;

	FTimerHandle TimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartTimer();

	//change text but launch wave too
	void ChangeText();

	void InitTimer();


};
