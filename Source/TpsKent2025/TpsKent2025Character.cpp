// Copyright Epic Games, Inc. All Rights Reserved.

#include "TpsKent2025Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TpsKent2025.h"

ATpsKent2025Character::ATpsKent2025Character()
{
	// El tamaño de la capsula de colision del personaje 
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configura velocidad de rotacion 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them

	//aca hace un get de las variables y las deja para poder modificarlas
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Aca crea un camara Boom, que es un tipo de camara 
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Aca esta creando una componente camara
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//aca esta lo que la funcion AddCoins hace , agrega y suma coins y muestra un mensaje 
void ATpsKent2025Character::AddCoins_Implementation(int AddCoins)
{
	// aca se agarra monedas y se le suma addcoins para que sume de a 10 
	Coins+=AddCoins;

	//aca se agrega un mensaje de cuantas monedas tiene
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Coins));
	
}


//aca se setea el sistema de inputs
void ATpsKent2025Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Aca preguntá si esta bindeando alguna tecla ? 
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

//aca se agregan los 3 nuevos input con el sistema de imput component
		PlayerInputComponent->BindAction("MostrarMensajeConInput", IE_Pressed, this, &ATpsKent2025Character::MostrarMensajeConInput);

		PlayerInputComponent->BindAction("RotarDerecha", IE_Pressed, this, &ATpsKent2025Character::RotarDerecha);
		
		PlayerInputComponent->BindAction("RotarIzquierda", IE_Pressed, this, &ATpsKent2025Character::RotarIzquierda);
		
		// Saltar
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moverse
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATpsKent2025Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATpsKent2025Character::Look);

		// Mirar
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATpsKent2025Character::Look);
	}
	else
	{
		UE_LOG(LogTpsKent2025, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATpsKent2025Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ATpsKent2025Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}


// aca estan las 3 funciones que agregue para los input. Mostar mensaje, rotar derecha y rotar izquierda

void ATpsKent2025Character::MostrarMensajeConInput()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Se apreto mostrar mensaje"));
}

void ATpsKent2025Character::RotarDerecha()
{
	FRotator RotacionDerechaConInput = GetActorRotation();
	RotacionDerechaConInput.Yaw += 45.f;
	SetActorRotation(RotacionDerechaConInput);
}

void ATpsKent2025Character::RotarIzquierda()
{
	FRotator RotacionIzquierdaConInput = GetActorRotation();
	RotacionIzquierdaConInput.Yaw -= 45.f;
	SetActorRotation(RotacionIzquierdaConInput);
}


//Funcion que hace que el personaje se mueva 
void ATpsKent2025Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}


//funcion que hace que el personaje mire al rotar el mouse)
void ATpsKent2025Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATpsKent2025Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ATpsKent2025Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}


//aca esta haciendo que MostrarMensajeOverLap muestre un mensaje 
void ATpsKent2025Character::MostrarMensajeOverLap()
{
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hiciste Overlap!!"));


	}
}
