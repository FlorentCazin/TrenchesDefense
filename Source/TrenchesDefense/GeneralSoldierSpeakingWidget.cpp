// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralSoldierSpeakingWidget.h"
#include "TrenchesDefenseGameMode.h"
#include "Components/TextBlock.h"


void UGeneralSoldierSpeakingWidget::NativeOnInitialized() {
	UWorld *World = GetOwningPlayer()->GetWorld();
	ATrenchesDefenseGameMode* GM = Cast<ATrenchesDefenseGameMode>(World->GetAuthGameMode());
	GM->GeneralSpeakingEvent.AddDynamic(this, &UGeneralSoldierSpeakingWidget::UdpateGeneralSpeaking);
}
void UGeneralSoldierSpeakingWidget::ChangeText(FString text) {
	GeneralSpeaking->SetText(FText::FromString(text));
	IsAlreadyTalking = true;
}

void UGeneralSoldierSpeakingWidget::UdpateGeneralSpeaking(FString GeneralTalking) {
	ChangeText(GeneralTalking);
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UGeneralSoldierSpeakingWidget::DisableSpeaking, TimeToShowSpeaking);
}

void UGeneralSoldierSpeakingWidget::DisableSpeaking() {
	SetVisibility(ESlateVisibility::Hidden);
	IsAlreadyTalking = false;
}