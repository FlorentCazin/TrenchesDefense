// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class TRENCHESDEFENSE_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	ULifeComponent();

	//MaxLife
	UPROPERTY(BlueprintReadWrite, Category = "LifeProperties")
	int LifeInitialization;

	UPROPERTY(BlueprintReadOnly, Category = "LifeProperties")
	int Life;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//return true if the target is dead
	UFUNCTION(BlueprintCallable)
	bool TakeDamage(int damage);

	UFUNCTION(BlueprintCallable)
	void RegenerateLife();
};
