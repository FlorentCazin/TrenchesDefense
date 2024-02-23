// Fill out your copyright notice in the Description page of Project Settings.


#include "PreviewCharacterWidget.h"
#include "Components/TextBlock.h"
#include "WeaponComponent.h"

void UPreviewCharacterWidget::SetPreviewValuesFromCharacter(ATrenchesDefenseCharacter* character) {
	//TSubclassOf need to have an instance to get variables
	TSubclassOf<UWeaponComponent> WeaponComponentClass = character->SoldierDataAsset->WeaponComponent;
	UWeaponComponent* WeaponComponent = NewObject<UWeaponComponent>(this, WeaponComponentClass);
	ULifeComponent *lifeComponent = character->LifeComponent;
	FString DmgTmp = FString::Printf(TEXT("ERROR DMG"));
	FString LifeTmp = FString::Printf(TEXT("%d/%d"), lifeComponent->Life, lifeComponent->LifeInitialization);
	if(WeaponComponent)	DmgTmp = FString::Printf(TEXT("%d DMG"), static_cast<int>(character->CharacterDataAsset->AttackDamage)); //maybe to change, no cast and get juste 2 digits
	FString HSTmp = FString::Printf(TEXT("%d%%HS"), WeaponComponent->HeadShotPrecisionPercentage);

	LifeText->SetText(FText::FromString(LifeTmp));
	DamageText->SetText(FText::FromString(DmgTmp));
	HeadShotText->SetText(FText::FromString(HSTmp));
	ChangeProgressBarColor(lifeComponent->Life);
}

void UPreviewCharacterWidget::ChangeProgressBarColor(int life) {
	life = 75;
	LifeProgressBar->SetPercent(static_cast<float>(life));
	int highLevelLife = life - (life / 3);
	int lowLevelLife = life / 3;
	if (life >= highLevelLife) LifeProgressBar->SetFillColorAndOpacity(HighLifeColor);
	else if(life>lowLevelLife) LifeProgressBar->SetFillColorAndOpacity(MiddleLifeColor);
	else LifeProgressBar->SetFillColorAndOpacity(LowLifeColor);
}