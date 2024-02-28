// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefLocalPlayerSubsystem.h"

UTrenchesDefLocalPlayerSubsystem::UTrenchesDefLocalPlayerSubsystem() {
	Money = 0;
}

void UTrenchesDefLocalPlayerSubsystem::ChangeMoney(int value) {
	Money += value;
}