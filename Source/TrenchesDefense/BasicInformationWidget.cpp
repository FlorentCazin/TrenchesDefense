// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInformationWidget.h"
#include "Components/TextBlock.h"
#include "CameraPlayerController.h"


void UBasicInformationWidget::NativeOnInitialized() {
	SetVisibility(ESlateVisibility::Visible);
	ACameraPlayerController* PC = Cast<ACameraPlayerController>(GetOwningPlayerPawn()->GetController());
	PLS = PC->GetLocalPlayer()->GetSubsystem<UTrenchesDefLocalPlayerSubsystem>();
	PLS->GiveMoneyEvent.AddDynamic(this, &UBasicInformationWidget::ChangeMoneyText);
}


void UBasicInformationWidget::ChangeMoneyText(int money) {
	FString MoneyTmp = FString::Printf(TEXT("%d"), PLS->Money);
	MoneyPlayer->SetText(FText::FromString(MoneyTmp));

	GetWorld()->GetAuthGameMode();
}

void UBasicInformationWidget::ChangeWaveText(int wave) {
	FString WaveTmp = FString::Printf(TEXT("%d"), wave);
	WaveNumber->SetText(FText::FromString(WaveTmp));
}