// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralSoldierSpeakingWidget.h"
#include "Components/TextBlock.h"

void UGeneralSoldierSpeakingWidget::ChangeText(FString text) {
	GeneralSpeaking->SetText(FText::FromString(text));
	IsAlreadyTalking = true;
}