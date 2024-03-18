// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseGameInstance.h"

UTrenchesDefenseGameInstance::UTrenchesDefenseGameInstance() {
	SettingsManager = CreateDefaultSubobject<USettingsManager>(TEXT("SettingsManager"));
	TotalWave = 1;
}

void UTrenchesDefenseGameInstance::initDefaultValueGameInstance() {
	TotalWave = 1;
}

