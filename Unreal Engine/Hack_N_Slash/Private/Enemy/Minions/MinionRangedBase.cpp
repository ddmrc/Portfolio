// Code Created By Diego Demarco


#include "Enemy/Minions/MinionRangedBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/EnergyComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMinionRangedBase::AMinionRangedBase()
{
	ConstructorHelpers::FObjectFinder<UBlueprint> ProjectileBP(TEXT("Blueprint'/Game/A_MainContent/Enemy/Minions/Projectiles/RangedMinionProjectile_BP.RangedMinionProjectile_BP'"));

	if (ProjectileBP.Object)
	{
		Projectile = (UClass*)ProjectileBP.Object->GeneratedClass;
	}
}

void AMinionRangedBase::BeginPlay()
{
	Super::BeginPlay();

	if (EnergyComponent == nullptr)
		EnergyComponent = FindComponentByClass<UEnergyComponent>();
}

void AMinionRangedBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttacking)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerCharacter->GetActorLocation());

		SetActorRotation(Rotation);
	}
}

void AMinionRangedBase::AttackPlayer()
{
	Super::AttackPlayer();
	

	if (!bIsAttacking)
	{
		bIsAttacking = true;
	 }

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	if (PlayerCharacter)
	{
		FName SocketName = "head";
		FTransform MeshTransform = GetMesh()->GetSocketTransform(SocketName, ERelativeTransformSpace::RTS_World);

		FVector LinetraceStart = MeshTransform.GetLocation();
		//FVector LinetraceStart = GetMesh()->GetComponentLocation();
		FVector LinetraceEnd = PlayerCharacter->GetActorLocation();

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		FVector SpawnLocation;
		FRotator SpawnRotation;
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = true ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		if (GetWorld()->LineTraceSingleByChannel(HitResult, LinetraceStart, LinetraceEnd,
			ECollisionChannel::ECC_Visibility, CollisionParams))
		{
			SpawnLocation = HitResult.Location;
			SpawnLocation = MeshTransform.GetLocation();
			//SpawnRotation = UKismetMathLibrary::FindLookAtRotation(MeshTransform.GetLocation(), HitResult.Location);
			
		}
		else
		{

			SpawnLocation = MeshTransform.GetLocation();
			SpawnRotation = (FRotator)MeshTransform.GetRotation();

		}

		SpawnRotation = UKismetMathLibrary::FindLookAtRotation(MeshTransform.GetLocation(), LinetraceEnd);
		ARangedMinionProjectile* RangedProjectile = GetWorld()->SpawnActor<ARangedMinionProjectile>(Projectile, SpawnLocation, SpawnRotation, SpawnInfo);
		if (EnergyComponent)
		{
			EnergyComponent->ModifyEnergy(-20.f);
			EnergyComponent->RechargeEnergy(true);
		}

			//DrawDebugLine(GetWorld(), LinetraceStart, LinetraceEnd, FColor::Red, false, 4.0f);

	}


}