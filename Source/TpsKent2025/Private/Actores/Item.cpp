// Fill out your copyright notice in the Description page of Project Settings.

#include <string>
#include "Actores/Item.h"

#include "TpsKent2025Character.h"
#include "AI/Navigation/NavAreaBase.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"
#include "Engine/RendererSettings.h"

// Sets default values
AItem::AItem()
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MiNombre = TEXT("Hola soy el item");

	SphereCollision=CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	SphereMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Esfera de Colision"));
	SphereMesh->SetupAttachment(SphereCollision);
	
	

	
}

//void AItem::MostrarOtroMensaje()
//{
//	if (GEngine)
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, MiNombre);
//}

void AItem::MostrarMensaje()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Los comandos de los inputs son Z,X,C"));
	
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	MostrarMensaje();
	//MostrarOtroMensaje();
	
  
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->Implements<UPlayerInterface>())
	{
		IPlayerInterface::Execute_AddCoins(OtherActor, AmountCoins);
		
	}
	
}

