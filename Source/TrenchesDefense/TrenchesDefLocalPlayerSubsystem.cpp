// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefLocalPlayerSubsystem.h"

void UTrenchesDefLocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	GiveMoneyEvent.AddDynamic(this, &UTrenchesDefLocalPlayerSubsystem::ChangeMoney);
}


UTrenchesDefLocalPlayerSubsystem::UTrenchesDefLocalPlayerSubsystem() {
	Money = 0;
}

void UTrenchesDefLocalPlayerSubsystem::ChangeMoney(int MoneyToGive) {
	Money += MoneyToGive;
}