// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
//#include "AbilitySystemInterface.h"
#include "AbilitySystem/BaseAttributeSet.h"
//#include "Components/SphereComponent.h"


// Sets default values
ABaseEffectActor::ABaseEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// SetRootComponent(Mesh);
	//
	// Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	// Sphere->SetupAttachment(GetRootComponent());
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
}

// Called when the game starts or when spawned
void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();
	// //添加碰撞监听
	// Sphere->OnComponentBeginOverlap.AddDynamic(this,&ABaseEffectActor::OnOverlap);
	// Sphere->OnComponentEndOverlap.AddDynamic(this,&ABaseEffectActor::EndOverlap);
}

void ABaseEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(Target);
	// if (ASCInterface)
	// {
	// 	UAbilitySystemComponent* AbilitySystemComponent = ASCInterface->GetAbilitySystemComponent();
	// }
	UAbilitySystemComponent* TargetAbilitySystemComponent =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent != nullptr)
	{
		FGameplayEffectContextHandle EffectContextHandle =  TargetAbilitySystemComponent->MakeEffectContext();// 构建gameplayeeffect上下文
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,EffectActorLevel,EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if (bIsInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle,TargetAbilitySystemComponent);
		}
	}
}

void ABaseEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGamePlayEffectClass);
	}
}

void ABaseEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if(InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC))
		{
			return; 	
		}
		TArray<FActiveGameplayEffectHandle> HandlesRemove;
		for (TTuple<FActiveGameplayEffectHandle,UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesRemove.Add(HandlePair.Key);
			}
		}
		for (auto &Handle:HandlesRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

// void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	//TODO:change this to apply a gameplay effect. for now, using const_cast as a hack!
// 	if (IAbilitySystemInterface* ASCInteraface = Cast<IAbilitySystemInterface>(OtherActor))
// 	{
// 		const UBaseAttributeSet* BaseAttributeSet = Cast<UBaseAttributeSet>(ASCInteraface->GetAbilitySystemComponent()->GetAttributeSet(UBaseAttributeSet::StaticClass()));
// 		UBaseAttributeSet* MutableBaseAttributeSet = const_cast<UBaseAttributeSet*>(BaseAttributeSet);
// 		MutableBaseAttributeSet->SetHealth(BaseAttributeSet->GetHealth()+25.f);
// 		Destroy();
// 	}
// }

// void ABaseEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// }



