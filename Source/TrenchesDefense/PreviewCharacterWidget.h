// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrenchesDefenseCharacter.h"
#include "PreviewCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UPreviewCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATrenchesDefenseCharacter* CharacterPreview;
	
};
