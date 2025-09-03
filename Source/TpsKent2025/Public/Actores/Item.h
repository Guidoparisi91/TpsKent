// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()

class TPSKENT2025_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props");
	int Salud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props");
	int Armadura;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props", meta = (tooltip = "Velocidad del item", uimin = "1.0", uimax = "100.0"));
	int Velocidad;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Props", meta = (tooltip = "Danio que el item", uimin = "1.0", uimax = "100.0"));
	int Danio;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
