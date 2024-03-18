// Fill out your copyright notice in the Description page of Project Settings.


#include "LoseWidget.h"
#include "TrenchesDefLocalPlayerSubsystem.h"
#include "Components/TextBlock.h"
#include "TrenchesDefenseGameInstance.h"
#include "Engine/World.h"


void ULoseWidget::NativeOnInitialized() {
	TotalWaveMessage();
	SetVisibility(ESlateVisibility::Visible);
}


void ULoseWidget::TotalWaveMessage() {
	UTrenchesDefenseGameInstance* GI = Cast<UTrenchesDefenseGameInstance>(GetGameInstance());
	FString WaveMessageTmp = FString::Printf(TEXT("Votre bataillon a survécu jusqu'à la manche %d"), GI->TotalWave);
	MessageWave->SetText(FText::FromString(WaveMessageTmp));
	GI->initDefaultValueGameInstance();
}

