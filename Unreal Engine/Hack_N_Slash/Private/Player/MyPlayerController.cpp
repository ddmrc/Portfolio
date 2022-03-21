// Code Created By Diego Demarco


#include "Player/MyPlayerController.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerCharacterBase == nullptr)
	{
		PlayerCharacterBase = Cast<AMyPlayerCharacterBase>(GetCharacter());
	}

	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


		InputComponent->BindAxis(FName(TEXT("MoveForward")), this, &AMyPlayerController::RequestMoveForward);
		InputComponent->BindAxis(FName(TEXT("MoveRight")), this, &AMyPlayerController::RequestMoveRight);
		InputComponent->BindAxis(FName(TEXT("Turn")), this, &AMyPlayerController::RequestTurn);
		InputComponent->BindAxis(FName(TEXT("LookUp")), this, &AMyPlayerController::RequestLookUp);

		InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::RequestJump);
		InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::RequestInteract);
		InputComponent->BindAction("Dash", IE_Pressed, this, &AMyPlayerController::RequestDash);
		InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyPlayerController::RequestStartLeftClick);
		InputComponent->BindAction("LeftClick", IE_Released, this, &AMyPlayerController::RequestStopLeftClick);
		InputComponent->BindAction("RightClick", IE_Pressed, this, &AMyPlayerController::RequestStartRightClick);
		InputComponent->BindAction("RightClick", IE_Released, this, &AMyPlayerController::RequestStopRightClick);



}

void AMyPlayerController::RequestMoveForward(float AxisValue)
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->MoveForward(AxisValue);
}

void AMyPlayerController::RequestMoveRight(float AxisValue)
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->MoveRight(AxisValue);
}

void AMyPlayerController::RequestTurn(float AxisValue)
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->Turn(AxisValue);
}

void AMyPlayerController::RequestLookUp(float AxisValue)
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->LookUp(AxisValue);
}

void AMyPlayerController::RequestJump()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->StartJump();
}

void AMyPlayerController::RequestInteract()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->Interact();
}

void AMyPlayerController::RequestDash()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->Dash();
}

void AMyPlayerController::RequestStartLeftClick()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->StartLeftClick();
}

void AMyPlayerController::RequestStopLeftClick()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->StopLeftClick();
}

void AMyPlayerController::RequestStartRightClick()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->StartRightClick();
}

void AMyPlayerController::RequestStopRightClick()
{
	if (PlayerCharacterBase)
	PlayerCharacterBase->StopRightClick();
}