// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefLocalPlayerSubsystem.h"

UTrenchesDefLocalPlayerSubsystem::UTrenchesDefLocalPlayerSubsystem() {
	Wave = 0;
	Money = 0;
}


void UTrenchesDefLocalPlayerSubsystem::IncrWave() {
	Wave++;
}

void UTrenchesDefLocalPlayerSubsystem::ChangeMoney(int value) {
	Money += value;
}