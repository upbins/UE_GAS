// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));//附加到挂接点上
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置碰撞类型
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return  AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}





