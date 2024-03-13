// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseGameMode.h"

ATrenchesDefenseGameMode::ATrenchesDefenseGameMode() {
	Wave = 0;
}

void ATrenchesDefenseGameMode::IncrWave() {
	Wave++;
}