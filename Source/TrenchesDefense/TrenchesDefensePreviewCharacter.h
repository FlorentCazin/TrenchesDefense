// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TrenchesDefenseCharacter.h"
#include "TrenchesDefensePreviewCharacter.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesDefensePreviewCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrenchesDefensePreviewCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATrenchesDefenseCharacter* CharacterToPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* WeaponAttachedToSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetPreview(ATrenchesDefenseCharacter* character);

	UFUNCTION(BlueprintCallable)
	void StopPreview();

};
