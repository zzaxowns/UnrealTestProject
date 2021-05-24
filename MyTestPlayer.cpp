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

	// 캐릭터 자체로 로테이션 하는것을 막음 : 카메라로 로테이션을 시키기 위해서
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);


	//카메라 관련 내용
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);  //Arm을 캡슐에다가 붙여놓음

	Arm->TargetArmLength = 300.f; // 셀카봉의 길이
	Arm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm, USpringArmComponent::SocketName); // 카메라를 셀카봉에 종속시킴

	Camera->bUsePawnControlRotation = false;

	//애님 인스턴스를 활용한 애니메이션 부분
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> PLATER_ANIM (TEXT("AnimBlueprint'/Game/_My/MyTestPlayerAnimation_BP.MyTestPlayerAnimation_BP_C'"));

	if (PLATER_ANIM.Succeeded()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BLADER success"));
		GetMesh()->SetAnimInstanceClass(PLATER_ANIM.Class);
	}

	//파티클 관련 변수 저장하기
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("ParticleSystem'/Game/ParagonShinbi/FX/Particles/Abilities/Primary/FX/P_Mudang_Primary_Impact.P_Mudang_Primary_Impact'"));
	HitFx = ParticleAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue>Attack(TEXT("SoundCue'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Sounds/SoundCues/Shinbi_Effort_Attack.Shinbi_Effort_Attack'"));

	if (Attack.Succeeded()) {
		AttackSoundCue = Attack.Object;
		AttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackAudioComponent"));
		AttackAudioComponent->SetupAttachment(RootComponent);
	}


	//=============================================== 변수 ====================================
	usingMoveForward = false; // Moveforward의 움직임이 있는지 MoveRight에서 확인하는 변수
	usingAttack = false; // 공격을 하고 있는지 확인하는 변수
	usingDash = false; // 대쉬를 쓰고 있는지 확인하는 변수
	isCombo = false;

	playerState = idle; // 맨 처음 플레이어의 상태를 idle로 지정
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

	if (AttackAudioComponent && AttackSoundCue) // 사운드 발생
	{
		AttackAudioComponent->SetSound(AttackSoundCue);
	}

}

// Called every frame
void AMyTestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerAnimation();
	RecoverST(DeltaTime); // 스테미나 회복 관련 함수
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

	//turn 과 lookup 관련 함수를 연결시킴
	PlayerInputComponent->BindAxis("Turn", this, &AMyTestPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyTestPlayer::AddControllerPitchInput);

	//캐릭터 이동 관련 함수 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTestPlayer::MoveForward); // 전방이동 세팅해둔걸 만들어 놓은 함수랑 연결
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTestPlayer::MoveRight);// 측면이동 세팅해둔걸 만들어 놓은 함수랑 연결

	//캐릭터 애니메이션 관련 함수 바인딩
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyTestPlayer::DoAttack); // 공격 애니메이션 추가

	//대쉬 관련 함수 연결
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyTestPlayer::DoDash);

}

void AMyTestPlayer::MoveForward(float value) {

	/*FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);*/
	if (playerState != attack) {
		if (value == 0) { // 움직일 때의 value 값이 0이면 움직이지 않는다는 것
			usingMoveForward = false; // 전진 함수가 활동 안함
			playerState = idle;
		}
		else { //그 이외이면 움직인다는 것 playerState가 run 상태 인것.
			usingMoveForward = true; // 전진 함수가 활동 중임 

			if (playerState != run && playerState != dash) { // 상태가 run또는 dash가 아니라면 run을 넣어달라 
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
	else if (playerState == attack) { // 공격 상태일 때의 이동

		usingMoveForward = true; // 전진 함수가 활동 중임 

		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, 0.1 *value);
	}
}

void AMyTestPlayer::MoveRight(float value) {

	if (playerState != attack) {
		if (value == 0 && !usingMoveForward) { // 움직이지 않는 경우
			playerState = idle;
		}
		else { // 움직이는 경우 

			////제어 
			if (playerState != run && playerState != dash) { // 상태가 run또는 dash가 아니라면 run을 넣어달라
				playerState = run;

			}

			// 이동
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

				if (AttackAudioComponent && AttackSoundCue) // 사운드 발생
				{
					AttackAudioComponent->Play(0.0f);
				}

				playerStamina -= 0.1;// 스테미나 사용
				recoverStaminaDelay = 2.0f;//스테미나 리커버리 시간 초기화
			}

		}
		else if (isCombo && playerState == attack && comboCount < 2) { //콤보 0->1->2 따라서 2가 마지막 공격임
			comboCount++;

			if (myTestPlayerAnimInst != nullptr) {
				//usingAttack = true;
				myTestPlayerAnimInst->Attack();

				if (AttackAudioComponent && AttackSoundCue) // 사운드 발생
				{
					AttackAudioComponent->Play(0.0f);
				}

				playerStamina -= 0.1; // 스테미나 사용
				recoverStaminaDelay = 2.0f; //스테미나 리커버리 시간 초기화
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
	if (playerState != attack && playerState != idle && !usingDash) { // 공격중에는 대쉬를 사용하지 못함
		if (playerState != dash) { playerState = dash; }

		if (myTestPlayerAnimInst != nullptr) {
			usingDash = true; // 대쉬를 하고 있다는 변수를 true
			myTestPlayerAnimInst->Dash(); // 대쉬 애니메이션을 사용
		}
	}
}

void AMyTestPlayer::playerAnimation()
{
	if (myTestPlayerAnimInst != nullptr) { //myAnimInst가 null이 아니라면 상태에 따라 애니메이션 ㅅ

		switch (playerState) {
		case idle:
			if (usingDash && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->dashMontage))) {
				// 대쉬를 사용했다는 변수가 true이고 대쉬 애니메이션이 작동하지 않고 있다 = 대쉬가 끝났다.
				usingDash = false; // 대쉬 변수를 false 로 해줌 
				playerState = idle; // 대쉬가 끝나면 Idle로 상태를 초기화 해줌
			}
			else if (playerState == idle && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->idleMontage))) {
				DoIdle(); // idle 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
			}
			break;
		case run:
			if (playerState == run && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->runMontage))) {
				if (myTestPlayerAnimInst != nullptr) { // 이동 상태인데 이동 애니메이션을 안쓰고 있으면
					myTestPlayerAnimInst->Run();
				}
			}
			break;
		case dash:
			if (usingDash && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->dashMontage))) {
				// 대쉬를 사용했다는 변수가 true이고 대쉬 애니메이션이 작동하지 않고 있다 = 대쉬가 끝났다.
				usingDash = false; // 대쉬 변수를 false 로 해줌 
				playerState = idle; // 대쉬가 끝나면 Idle로 상태를 초기화 해줌
			}
			break;
		case attack:
			if (isCombo && !(myTestPlayerAnimInst->Montage_IsPlaying(myTestPlayerAnimInst->attackMontage))) {
				// 공격 사용 변수가 true이고 현재 공격 애니메이션을 쓰지 않는다 = 공격이 끝났다.
				//usingAttack = false; // 공격 사용 변수 false
				isCombo = false;
				comboCount = 0;
				playerState = idle; // idle 애니메이션으로 변경

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