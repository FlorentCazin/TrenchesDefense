// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInformationWidget.h"
#include "Components/TextBlock.h"



void UBasicInformationWidget::ChangeMoneyText(int money) {
	FString MoneyTmp = FString::Printf(TEXT("%d"), money);
	MoneyPlayer->SetText(FText::FromString(MoneyTmp));
}

void UBasicInformationWidget::ChangeWaveText(int wave) {
	FString WaveTmp = FString::Printf(TEXT("%d"), wave);
	WaveNumber->SetText(FText::FromString(WaveTmp));
}