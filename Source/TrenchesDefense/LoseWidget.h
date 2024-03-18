// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LoseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API ULoseWidget : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindWidget), category="LoseWidget")
	class UTextBlock* MessageWave;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindWidget), category = "LoseWidget")
	class UTextBlock* MenuText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindWidget), category = "LoseWidget")
	class UTextBlock* LeaveText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindWidget), category = "LoseWidget")
	UButton* MenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (bindWidget), category = "LoseWidget")
	UButton* LeaveButton;


protected:

	virtual void NativeOnInitialized() override;
	

	UFUNCTION(BlueprintCallable)
	void TotalWaveMessage();


	
};
