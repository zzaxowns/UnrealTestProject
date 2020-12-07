// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine.h"
#include "TestPlayer.h"

// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ĳ���� ��ü�� �����̼� �ϴ°��� ���� : ī�޶�� �����̼��� ��Ű�� ���ؼ� =======================================
	bUseControllerRotationPitch = false; 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement() ->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;


	//===========================================================================================================
	//���̷�Ż �޽� �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyAsset(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));

	if (BodyAsset.Succeeded()) { // �޽ð� �� ������ Ȯ���ϴ� �Լ�
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}

	GetMesh()->RelativeLocation.Z = -88.f;
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // ĳ���Ͱ� ���� ������ �ٲ�

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);  //Arm�� ĸ�����ٰ� �ٿ�����

	Arm->TargetArmLength = 300.f; // ��ī���� ����
	Arm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm,USpringArmComponent::SocketName); // ī�޶� ��ī���� ���ӽ�Ŵ

	Camera->bUsePawnControlRotation = false;

	//�ִ� �ν��Ͻ��� Ȱ���� �ִϸ��̼� �κ�
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>BLADER_ANIM(TEXT("AnimBlueprint'/Game/BluePrint/Shinbi_Animation_BP.Shinbi_Animation_BP_C'"));

	if (BLADER_ANIM.Succeeded()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BLADER success"));
		GetMesh()->SetAnimInstanceClass(BLADER_ANIM.Class);
	}


	//=============================================== ���� ====================================
	usingMoveForward = false; // Moveforward�� �������� �ִ��� MoveRight���� Ȯ���ϴ� ����
	usingAttack = false; // ������ �ϰ� �ִ��� Ȯ���ϴ� ����
	usingDash = false; // �뽬�� ���� �ִ��� Ȯ���ϴ� ����

	playerState = idle; // �� ó�� �÷��̾��� ���¸� idle�� ����
	comboCount = 0;
}

// Called when the game starts or when spawned
void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	animInstance = GetMesh()->GetAnimInstance();

	myAnimInst = Cast<UMyAnimInstance>(animInstance);
}

void ATestPlayer::PostInitilizeComponent()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ATestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerAnimation(); // ������Ʈ�� ���� �ִϸ��̼��� ��������ִ� �Լ�
}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//turn �� lookup ���� �Լ��� �����Ŵ
	PlayerInputComponent->BindAxis("Turn", this, &ATestPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestPlayer::AddControllerPitchInput);

	//ĳ���� �̵� ���� �Լ� ���ε�
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestPlayer::MoveForward); // �����̵� �����صа� ����� ���� �Լ��� ����
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestPlayer::MoveRight);// �����̵� �����صа� ����� ���� �Լ��� ����

	//ĳ���� �ִϸ��̼� ���� �Լ� ���ε�
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATestPlayer::DoAttack); // ���� �ִϸ��̼� �߰�

	//�뽬 ���� �Լ� ����
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ATestPlayer::DoDash);
	//PlayerInputComponent->BindAction("Dash", IE_Released, this, &ATestPlayer::GoToIdle);
}

void ATestPlayer::MoveForward(float Value) {

	/*FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);*/

	if (playerState != attack) {
		if (Value == 0) { // ������ ���� value ���� 0�̸� �������� �ʴ´ٴ� ��
			usingMoveForward = false; // ���� �Լ��� Ȱ�� ����
			playerState = idle;
		}
		else { //�� �̿��̸� �����δٴ� �� playerState�� run ���� �ΰ�.
			usingMoveForward = true; // ���� �Լ��� Ȱ�� ���� 

			if (playerState != run && playerState != dash) { // ���°� run�Ǵ� dash�� �ƴ϶�� run�� �־�޶� 
				playerState = run;
			}

			FRotator Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
			//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

			if (playerState == dash) { // �뽬�� ��쿡 1.5�� ������ �뽬�� �ϰ� �ϰ�
				AddMovementInput(Direction, 2.0 *Value);
			}
			else { // �뽬�� �ƴϴ�, �� �Ϲ� �̵��� ��쿡 �Ϲ� �̵� ��ġ��ŭ �̵��Ѵ�.
				AddMovementInput(Direction, Value);
			}
		}
	}
	else if (playerState == attack) { // ���� ������ ���� �̵�

		usingMoveForward = true; // ���� �Լ��� Ȱ�� ���� 

		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, 0.2 *Value);
	}
}

void ATestPlayer::MoveRight(float Value) {

	if (playerState != attack) {
		if (Value == 0 && !usingMoveForward) { // �������� �ʴ� ���
			playerState = idle;
		}
		else { // �����̴� ��� 

			if (playerState != run && playerState != dash) { // ���°� run�Ǵ� dash�� �ƴ϶�� run�� �־�޶�
				playerState = run;
			}

			FRotator Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
			//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

			if (playerState == dash) { // �뽬�� ��쿡 1.5�� ������ �뽬�� �ϰ� �ϰ�
				AddMovementInput(Direction, 1.5 *Value);
			}
			else { // �뽬�� �ƴϴ�, �� �Ϲ� �̵��� ��쿡 �Ϲ� �̵� ��ġ��ŭ �̵��Ѵ�.
				AddMovementInput(Direction, Value);
			}
		}
	}
}

void ATestPlayer::DoAttack()
{
	if (playerState != attack && !usingAttack ) {
		playerState = attack; 
	
		if (myAnimInst != nullptr) {
			usingAttack = true;
			myAnimInst->Attack();
		}

	}
	else if (playerState == attack && usingAttack && comboCount <2) { //�޺� 0->1->2 ���� 2�� ������ ������
		comboCount++;

		if (myAnimInst != nullptr) {
			usingAttack = true;
			myAnimInst->Attack();
		}

		myAnimInst->Montage_JumpToSection(FName(comboList[comboCount]),myAnimInst->attackMontage);
	}

}

void ATestPlayer::DoRun() {
	if (playerState != run) {
		playerState = run; 

		if (myAnimInst != nullptr) {
			myAnimInst->Run();
		}

	}
	else if (playerState == run && !(myAnimInst->Montage_IsPlaying(myAnimInst->runMontage))) {
		if (myAnimInst != nullptr) {
			myAnimInst->Run();
		}
	}

}

void ATestPlayer::DoIdle() {
	if (playerState != idle) { playerState = idle; }

	if (myAnimInst != nullptr) {
		myAnimInst->Idle();
	}
}

void ATestPlayer::DoDash(){
	if (playerState != attack && playerState != idle && !usingDash) { // �����߿��� �뽬�� ������� ����
		if (playerState != dash) { playerState = dash; }

		if (myAnimInst != nullptr) {
			usingDash = true; // �뽬�� �ϰ� �ִٴ� ������ true
			myAnimInst->Dash(); // �뽬 �ִϸ��̼��� ���
		}
	}
}

void ATestPlayer::playerAnimation()
{
	if (myAnimInst != nullptr) { //myAnimInst�� null�� �ƴ϶�� ���¿� ���� �ִϸ��̼� ��

		switch (playerState) {
			case idle:
				if (usingDash && !(myAnimInst->Montage_IsPlaying(myAnimInst->dashMontage))) {
					// �뽬�� ����ߴٴ� ������ true�̰� �뽬 �ִϸ��̼��� �۵����� �ʰ� �ִ� = �뽬�� ������.
					usingDash = false; // �뽬 ������ false �� ���� 
					playerState = idle; // �뽬�� ������ Idle�� ���¸� �ʱ�ȭ ����
				}else if (playerState == idle && !(myAnimInst->Montage_IsPlaying(myAnimInst->idleMontage))) {
					DoIdle(); // idle �����ε� �ִϸ��̼��� �۵����� ������ �ִϸ��̼��� �۵���Ŵ
				}
				break;
			case run:
				if (playerState == run && !(myAnimInst->Montage_IsPlaying(myAnimInst->runMontage))) {
					if (myAnimInst != nullptr) { // �̵� �����ε� �̵� �ִϸ��̼��� �Ⱦ��� ������
						myAnimInst->Run();       // �̵� �ִϸ��̼��� �ҷ��´� 
					}
				}
				break;
			case dash:
				if (usingDash && !(myAnimInst->Montage_IsPlaying(myAnimInst->dashMontage))) {
					// �뽬�� ����ߴٴ� ������ true�̰� �뽬 �ִϸ��̼��� �۵����� �ʰ� �ִ� = �뽬�� ������.
					usingDash = false; // �뽬 ������ false �� ���� 
					playerState = idle; // �뽬�� ������ Idle�� ���¸� �ʱ�ȭ ����
				} 
				break;
			case attack:
				if (usingAttack && !(myAnimInst->Montage_IsPlaying(myAnimInst->attackMontage))) {
					// ���� ��� ������ true�̰� ���� ���� �ִϸ��̼��� ���� �ʴ´� = ������ ������.
					usingAttack = false; // ���� ��� ���� false
					comboCount = 0;
					playerState = idle; // idle �ִϸ��̼����� ����
				
				}
				break;
			default:
				break;
		}
	}
}

//void ATestPlayer::EndAttacking()
//{
//	usingAttack = false;
//}
