// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestPlayer.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Sound/SoundCue.h"

// Sets default values
AMyTestPlayer::AMyTestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ĳ���� ��ü�� �����̼� �ϴ°��� ���� : ī�޶�� �����̼��� ��Ű�� ���ؼ�
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);


	//ī�޶� ���� ����
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);  //Arm�� ĸ�����ٰ� �ٿ�����

	Arm->TargetArmLength = 300.f; // ��ī���� ����
	Arm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm, USpringArmComponent::SocketName); // ī�޶� ��ī���� ���ӽ�Ŵ

	Camera->bUsePawnControlRotation = false;

	//�ִ� �ν��Ͻ��� Ȱ���� �ִϸ��̼� �κ�
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLATER_ANIM (TEXT("AnimBlueprint'/Game/_My/MyTestPlayerAnimation_BP.MyTestPlayerAnimation_BP_C'"));

	if (PLATER_ANIM.Succeeded()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BLADER success"));
		GetMesh()->SetAnimInstanceClass(PLATER_ANIM.Class);
	}

	//��ƼŬ ���� ���� �����ϱ�
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/ParagonShinbi/FX/Particles/Abilities/Primary/FX/P_Mudang_Primary_Impact.P_Mudang_Primary_Impact'"));
	HitFx = ParticleAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>Attack(TEXT("SoundCue'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Sounds/SoundCues/Shinbi_Effort_Attack.Shinbi_Effort_Attack'"));

	if (Attack.Succeeded()) {
		AttackSoundCue = Attack.Object;
		AttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackAudioComponent"));
		AttackAudioComponent->SetupAttachment(RootComponent);
	}


	//=============================================== ���� ====================================
	usingMoveForward = false; // Moveforward�� �������� �ִ��� MoveRight���� Ȯ���ϴ� ����
	usingAttack = false; // ������ �ϰ� �ִ��� Ȯ���ϴ� ����
	usingDash = false; // �뽬�� ���� �ִ��� Ȯ���ϴ� ����
	isCombo = false;

	playerState = idle; // �� ó�� �÷��̾��� ���¸� idle�� ����
	comboCount = 0;



	playerHp = 1.0f;
	playerStamina = 1.0f;
	recoverStaminaDelay = 2.0f;


	setup_stimulus();
}

// Called when the game starts or when spawned
void AMyTestPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	animInstance = GetMesh()->GetAnimInstance();

	myTestPlayerAnimInst = Cast<UMyTestPlayerAnimInstance>(animInstance);

	if (AttackAudioComponent && AttackSoundCue) // ���� �߻�
	{
		AttackAudioComponent->SetSound(AttackSoundCue);
	}

}

// Called every frame
void AMyTestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerAnimation();
	RecoverST(DeltaTime); // ���׹̳� ȸ�� ���� �Լ�
}


void AMyTestPlayer::RecoverST(float DeltaTime)
{

	if (recoverStaminaDelay < 0) {
		recoverStaminaDelay = -0.1;
	}
	else {
		recoverStaminaDelay -= DeltaTime;
	}

	if (playerStamina < 1.0f && recoverStaminaDelay < 0) {
		playerStamina += 0.01;
	}
}

void AMyTestPlayer::Damaged()
{
	playerHp -= 0.3;
}

void AMyTestPlayer::setUsingAttack(bool usingAttack)
{
	this->usingAttack = usingAttack;
}

void AMyTestPlayer::ShowFX()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFx, GetActorLocation());
}

// Called to bind functionality to input
void AMyTestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//turn �� lookup ���� �Լ��� �����Ŵ
	PlayerInputComponent->BindAxis("Turn", this, &AMyTestPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyTestPlayer::AddControllerPitchInput);

	//ĳ���� �̵� ���� �Լ� ���ε�
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTestPlayer::MoveForward); // �����̵� �����صа� ����� ���� �Լ��� ����
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTestPlayer::MoveRight);// �����̵� �����صа� ����� ���� �Լ��� ����

	//ĳ���� �ִϸ��̼� ���� �Լ� ���ε�
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyTestPlayer::DoAttack); // ���� �ִϸ��̼� �߰�

	//�뽬 ���� �Լ� ����
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyTestPlayer::DoDash);

}

void AMyTestPlayer::MoveForward(float value) {

	/*FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);*/
	if (playerState != attack) {
		if (value == 0) { // ������ ���� value ���� 0�̸� �������� �ʴ´ٴ� ��
			usingMoveForward = false; // ���� �Լ��� Ȱ�� ����
			playerState = idle;
		}
		else { //�� �̿��̸� �����δٴ� �� playerState�� run ���� �ΰ�.
			usingMoveForward = true; // ���� �Լ��� Ȱ�� ���� 

			if (playerState != run && playerState != dash) { // ���°� run�Ǵ� dash�� �ƴ϶�� run�� �־�޶� 
				playerState = run;
			}

			if ((Controller != NULL && (value != 0.0f))) {
				FRotator Rotation = Controller->GetControlRotation();
				FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

				FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

				AddMovementInput(Direction, value);
			}
		}
	}
	else if (playerState == attack) { // ���� ������ ���� �̵�

		usingMoveForward = true; // ���� �Լ��� Ȱ�� ���� 

		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, 0.1 *value);
	}
}

void AMyTestPlayer::MoveRight(float value) {

	if (playerState != attack) {
		if (value == 0 && !usingMoveForward) { // �������� �ʴ� ���
			playerState = idle;
		}
		else { // �����̴� ��� 

			////���� 
			if (playerState != run && playerState != dash) { // ���°� run�Ǵ� dash�� �ƴ϶�� run�� �־�޶�
				playerState = run;

			}

			// �̵�
			if ((Controller != NULL && (value != 0.0f))) {
				FRotator Rotation = Controller->GetControlRotation();
				FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

				FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

				AddMovementInput(Direction, value);
			}
		}
	}
}

void AMyTestPlayer::DoIdle()
{
	if (playerState != idle) { playerState = idle; }

	if (myTestPlayerAnimInst != nullptr) {
		myTestPlayerAnimInst->Idle();
	}
}

void AMyTestPlayer::DoAttack()
{
	if (playerStamina > 0) {
		if (playerState != attack && !usingAttack) {
			playerState = attack;
			isCombo = true;

			if (myTestPlayerAnimInst != nullptr) {
				//usingAttack = true;
				myTestPlayerAnimInst->Attack();

				if (AttackAudioComponent && AttackSoundCue) // ���� �߻�
				{
					AttackAudioComponent->Play(0.0f);
				}

				playerStamina -= 0.1;// ���׹̳� ���
				recoverStaminaDelay = 2.0f;//���׹̳� ��Ŀ���� �ð� �ʱ�ȭ
			}

		}
		else if (isCombo && playerState == attack && comboCount < 2) { //�޺� 0->1->2 ���� 2�� ������ ������
			comboCount++;

			if (myTestPlayerAnimInst != nullptr) {
				//usingAttack = true;
				myTestPlayerAnimInst->Attack();

				if (AttackAudioComponent && AttackSoundCue) // ���� �߻�
				{
					AttackAudioComponent->Play(0.0f);
				}

				playerStamina -= 0.1; // ���׹̳� ���
				recoverStaminaDelay = 2.0f; //���׹̳� ��Ŀ���� �ð� �ʱ�ȭ
			}

			myTestPlayerAnimInst->Montage_JumpToSection(FName(comboList[comboCount]), myTestPlayerAnimInst->attackMontage);
		}
	}
}

void AMyTestPlayer::DoRun()
{
	if (playerState != run){
		playerState = run;

		if (myTestPlayerAnimInst != nullptr) {
			myTestPlayerAnimInst->Run();
		}
	}
	else if (playerState == run && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->runMontage))) {
		if (myTestPlayerAnimInst != nullptr) {
			myTestPlayerAnimInst->Run();
		}
	}

}

void AMyTestPlayer::DoDash()
{
	if (playerState != attack && playerState != idle && !usingDash) { // �����߿��� �뽬�� ������� ����
		if (playerState != dash) { playerState = dash; }

		if (myTestPlayerAnimInst != nullptr) {
			usingDash = true; // �뽬�� �ϰ� �ִٴ� ������ true
			myTestPlayerAnimInst->Dash(); // �뽬 �ִϸ��̼��� ���
		}
	}
}

void AMyTestPlayer::playerAnimation()
{
	if (myTestPlayerAnimInst != nullptr) { //myAnimInst�� null�� �ƴ϶�� ���¿� ���� �ִϸ��̼� ��

		switch (playerState) {
		case idle:
			if (usingDash && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->dashMontage))) {
				// �뽬�� ����ߴٴ� ������ true�̰� �뽬 �ִϸ��̼��� �۵����� �ʰ� �ִ� = �뽬�� ������.
				usingDash = false; // �뽬 ������ false �� ���� 
				playerState = idle; // �뽬�� ������ Idle�� ���¸� �ʱ�ȭ ����
			}
			else if (playerState == idle && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->idleMontage))) {
				DoIdle(); // idle �����ε� �ִϸ��̼��� �۵����� ������ �ִϸ��̼��� �۵���Ŵ
			}
			break;
		case run:
			if (playerState == run && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->runMontage))) {
				if (myTestPlayerAnimInst != nullptr) { // �̵� �����ε� �̵� �ִϸ��̼��� �Ⱦ��� ������
					myTestPlayerAnimInst->Run();
				}
			}
			break;
		case dash:
			if (usingDash && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->dashMontage))) {
				// �뽬�� ����ߴٴ� ������ true�̰� �뽬 �ִϸ��̼��� �۵����� �ʰ� �ִ� = �뽬�� ������.
				usingDash = false; // �뽬 ������ false �� ���� 
				playerState = idle; // �뽬�� ������ Idle�� ���¸� �ʱ�ȭ ����
			}
			break;
		case attack:
			if (isCombo && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->attackMontage))) {
				// ���� ��� ������ true�̰� ���� ���� �ִϸ��̼��� ���� �ʴ´� = ������ ������.
				//usingAttack = false; // ���� ��� ���� false
				isCombo = false;
				comboCount = 0;
				playerState = idle; // idle �ִϸ��̼����� ����

			}
			break;
		default:
			break;
		}
	}
}

bool AMyTestPlayer::getUsingAttack()
{
	return usingAttack;
}

void AMyTestPlayer::setup_stimulus(){
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}