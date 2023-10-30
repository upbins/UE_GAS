// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BasePlayerController.h"
#include "Player/BasePlayerState.h"
#include "UI/HUD/BaseHUD.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 APlayerCharacter::GetObjectLevel_Implementation()
{
	const ABasePlayerState* AuraPlayerState = GetPlayerState<ABasePlayerState>();
    check(AuraPlayerState);
    return AuraPlayerState->GetObjectLevel();
}

void APlayerCharacter::InitAbilityActorInfo()
{

	ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check(BasePlayerState);
	AbilitySystemComponent = BasePlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(BasePlayerState,this);
	Cast<UBaseAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = BasePlayerState->GetAttributeSet();
	if (ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetController()))
	{
		if(ABaseHUD* BaseHUD = Cast<ABaseHUD>(PlayerController->GetHUD()))
		{
			BaseHUD->InitOverlay(PlayerController,BasePlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}





