// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UStaticMeshComponent;



UCLASS()

class TPSKENT2025_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props", meta = (ToolTip ="Salud del item"))
	int Salud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props", meta=(ToolTip="Armadura del item", UIMin= "10.0", UIMax = "50.0"))
	int Armadura;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props", meta = (tooltip = "Velocidad del item", uimin = "1.0", uimax = "100.0"))
	int Velocidad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props", meta = (tooltip = "Danio que el item", uimin = "1.0", uimax = "100.0"))
	int Danio;

	UPROPERTY(EditAnywhere)
	FString MiNombre;

	//UFUNCTION(BlueprintCallable)
	//void MostrarOtroMensaje();	

	UFUNCTION(BlueprintCallable)
	void MostrarMensaje();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent>SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent>SphereMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int AmountCoins = 10;

	
	

	
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	

};
