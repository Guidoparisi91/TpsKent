// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "Logging/LogMacros.h"
#include "TpsKent2025Character.generated.h"

//Aqui agrega las clases que vamos a usar 
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)

// aca le avisa al programa que va esta heredando de Character, y que usa una Interfaz
class ATpsKent2025Character : public ACharacter, public IPlayerInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */

	//aca se agrega el componente de la camara
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:
//aca se seclaran los inputs del personaje. tiene por defecto input de salto, de mirar, de mover, y del mouse
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	

public:
//aca declara el constructor de la clase 
	/** Constructor */
	ATpsKent2025Character();


	//aca se esta agregando la interfaz de agarrar monedas 
	//Interface
	virtual void AddCoins_Implementation(int AddCoins) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Inventario")
	int Coins = 0;

protected:

	/** Inicializa las acciones del input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	// Funciones para las acciones del ejercicio
	
	UFUNCTION()
	void MostrarMensajeConInput();

	UFUNCTION()
	void RotarDerecha();

	UFUNCTION()
	void RotarIzquierda();

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();


	//aca se agrega la funcion mostrar mensaje cuando overlapea con la moneda
	
	UFUNCTION(BlueprintCallable)
	void MostrarMensajeOverLap();
	

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

