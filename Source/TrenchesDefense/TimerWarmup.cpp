// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWarmup.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "TrenchesDefenseGameMode.h"

// Sets default values
ATimerWarmup::ATimerWarmup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimerText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TimerTextComponent"));
}

// Called when the game starts or when spawned
void ATimerWarmup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATimerWarmup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerWarmup::InitTimer() {
	ActualTime = TimeInSeconds;
}

void ATimerWarmup::StartTimer() {
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerWarmup::ChangeText, 1.f, true, 1.0f);
}

void ATimerWarmup::ChangeText() {
	if (ActualTime < 0) {
		ATrenchesDefenseGameMode *GM = Cast<ATrenchesDefenseGameMode>(GetWorld()->GetAuthGameMode());
		if (GM) {
			GM->StartWave(); //start wave
		}
		GetWorldTimerManager().ClearTimer(TimerHandle);
		InitTimer();
	}
	else {
		FString TimerTmp;
		int minutes = ActualTime / 60;
		int seconds = ActualTime - (minutes * 60);
		if (minutes <= 0 && seconds <= 0) {
			TimerTmp = FString::Printf(TEXT("00:00"));
		}
		else if (minutes < 10) {
			if (seconds < 10) {
				TimerTmp = FString::Printf(TEXT("0%d:0%d"), minutes, seconds);
			}
			else {
				TimerTmp = FString::Printf(TEXT("0%d:%d"), minutes, seconds);
			}
		}
		else if (seconds < 10) {
			if (minutes < 10) {
				TimerTmp = FString::Printf(TEXT("0%d:0%d"), minutes, seconds);
			}
			else {
				TimerTmp = FString::Printf(TEXT("%d:0%d"), minutes, seconds);
			}
		}
		else {
			TimerTmp = FString::Printf(TEXT("%d:%d"), minutes, seconds);
		}
		TimerText->SetText(FText::FromString(TimerTmp));
		ActualTime--;
	}
}
