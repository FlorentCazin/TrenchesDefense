// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesSelector.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnerEnemy.h"


// Sets default values
ATrenchesSelector::ATrenchesSelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrenchesSelector::BeginPlay()
{
	Super::BeginPlay();

	numberOfTrencheToExplore = TrenchesToExploreArray.Num();
	ASpawnerEnemy *spawner = Cast<ASpawnerEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnerEnemy::StaticClass()));
	if (spawner) {
		totalEnemies = spawner->NumberOfEnemy;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ASpawnerEnemy is nullptr ATrenchesSelector"));
	}

	if (totalEnemies % numberOfTrencheToExplore != 0) {
		UE_LOG(LogTemp, Warning, TEXT("problem, totalEnemies % numberOfTrencheToExplore != 0, should be 0 to avoid problems"));
	}

	for (ATrencheToExplore* trenche : TrenchesToExploreArray) {
		trenche->NumberMaxInsideTrenche = totalEnemies / numberOfTrencheToExplore;
	}
	
}

// Called every frame
void ATrenchesSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrenchesSelector::SetTrenchesValues() {
	// t0 => give 50% to t4
	//t1 => give 25% to t3
	//t2 don't move
	// should stay 2 enemies minimum / trenches

	if (TrencheToExploreOrderScoreArray.Num() == 5) {
		GiveToTrenche(TrencheToExploreOrderScoreArray[0], TrencheToExploreOrderScoreArray[4], 0.5);
		GiveToTrenche(TrencheToExploreOrderScoreArray[1], TrencheToExploreOrderScoreArray[3], 0.25);
	}
	//reset array
	TrencheToExploreOrderScoreArray.Reset();

	
}

void ATrenchesSelector::GiveToTrenche(ATrencheToExplore* trencheGiver, ATrencheToExplore* trencheReceiver, float percentage) {
	//always check if we have 2 minimum enemies inside the trenche
	//give percentage
	if ((trencheGiver->NumberMaxInsideTrenche - (trencheGiver->NumberMaxInsideTrenche * percentage)) >= 2) {
		//add value to receiver
		trencheReceiver->NumberMaxInsideTrenche += trencheGiver->NumberMaxInsideTrenche * percentage;
		//remove value from giver
		trencheGiver->NumberMaxInsideTrenche -= trencheGiver->NumberMaxInsideTrenche * percentage;
	}
	else {
		//give the rest
		if (trencheGiver->NumberMaxInsideTrenche - 2 >= 2) {
			trencheReceiver->NumberMaxInsideTrenche += trencheGiver->NumberMaxInsideTrenche-2;
			trencheGiver->NumberMaxInsideTrenche = (2 - trencheGiver->NumberMaxInsideTrenche) * -1;
		}
	}
}

ATrencheToExplore* ATrenchesSelector::GetTrenche() {
	for (ATrencheToExplore* trenche : TrenchesToExploreArray) {
		if (trenche->ActualNumberInsideTrenche < trenche->NumberMaxInsideTrenche) {
			trenche->ActualNumberInsideTrenche++;
			return trenche;
		}
	}
	//avoid problem
	if (TrenchesToExploreArray.Num() > 0) {
		return TrenchesToExploreArray[0];
	}
	else return nullptr;
}


