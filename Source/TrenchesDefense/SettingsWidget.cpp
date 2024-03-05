// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"
#include "Components/TextBlock.h"

void USettingsWidget::ChangeWindowModeText(FString text) {
	FullScreenText->SetText(FText::FromString(text));
}


void USettingsWidget::ChangeResolutionText(FString text) {
	ResolutionText->SetText(FText::FromString(text));
}


void USettingsWidget::ChangeGraphicsText(FString text) {
	QualityText->SetText(FText::FromString(text));
}


void USettingsWidget::ChangeVSyncText(FString text) {
	VSyncText->SetText(FText::FromString(text));
}
