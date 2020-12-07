// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine.h"
#include "TestPlayer.h"

// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터 자체로 로테이션 하는것을 막음 : 카메라로 로테이션을 시키기 위해서 =======================================
	bUseControllerRotationPitch = false; 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement() ->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;


	//===========================================================================================================
	//스켈레탈 메시 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyAsset(TEXT("SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'"));

	if (BodyAsset.Succeeded()) { // 메시가 잘 들어갔는지 확인하는 함수
		GetMesh()->SetSkeletalMesh(BodyAsset.Object);
	}

	GetMesh()->RelativeLocation.Z = -88.f;
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); // 캐릭터가 보는 방향을 바꿈

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);  //Arm을 캡슐에다가 붙여놓음

	Arm->TargetArmLength = 300.f; // 셀카봉의 길이
	Arm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm,USpringArmComponent::SocketName); // 카메라를 셀카봉에 종속시킴

	Camera->bUsePawnControlRotation = false;

	//애님 인스턴스를 활용한 애니메이션 부분
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>BLADER_ANIM(TEXT("AnimBlueprint'/Game/BluePrint/Shinbi_Animation_BP.Shinbi_Animation_BP_C'"));

	if (BLADER_ANIM.Succeeded()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BLADER success"));
		GetMesh()->SetAnimInstanceClass(BLADER_ANIM.Class);
	}


	//=============================================== 변수 ====================================
	usingMoveForward = false; // Moveforward의 움직임이 있는지 MoveRight에서 확인하는 변수
	usingAttack = false; // 공격을 하고 있는지 확인하는 변수
	usingDash = false; // 대쉬를 쓰고 있는지 확인하는 변수

	playerState = idle; // 맨 처음 플레이어의 상태를 idle로 지정
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
	playerAnimation(); // 스테이트에 따른 애니메이션을 실행시켜주는 함수
}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//turn 과 lookup 관련 함수를 연결시킴
	PlayerInputComponent->BindAxis("Turn", this, &ATestPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestPlayer::AddControllerPitchInput);

	//캐릭터 이동 관련 함수 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestPlayer::MoveForward); // 전방이동 세팅해둔걸 만들어 놓은 함수랑 연결
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestPlayer::MoveRight);// 측면이동 세팅해둔걸 만들어 놓은 함수랑 연결

	//캐릭터 애니메이션 관련 함수 바인딩
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATestPlayer::DoAttack); // 공격 애니메이션 추가

	//대쉬 관련 함수 연결
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ATestPlayer::DoDash);
	//PlayerInputComponent->BindAction("Dash", IE_Released, this, &ATestPlayer::GoToIdle);
}

void ATestPlayer::MoveForward(float Value) {

	/*FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);*/

	if (playerState != attack) {
		if (Value == 0) { // 움직일 때의 value 값이 0이면 움직이지 않는다는 것
			usingMoveForward = false; // 전진 함수가 활동 안함
			playerState = idle;
		}
		else { //그 이외이면 움직인다는 것 playerState가 run 상태 인것.
			usingMoveForward = true; // 전진 함수가 활동 중임 

			if (playerState != run && playerState != dash) { // 상태가 run또는 dash가 아니라면 run을 넣어달라 
				playerState = run;
			}

			FRotator Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
			//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

			if (playerState == dash) { // 대쉬일 경우에 1.5배 속으로 대쉬를 하게 하고
				AddMovementInput(Direction, 2.0 *Value);
			}
			else { // 대쉬가 아니다, 즉 일반 이동일 경우에 일반 이동 수치만큼 이동한다.
				AddMovementInput(Direction, Value);
			}
		}
	}
	else if (playerState == attack) { // 공격 상태일 때의 이동

		usingMoveForward = true; // 전진 함수가 활동 중임 

		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, 0.2 *Value);
	}
}

void ATestPlayer::MoveRight(float Value) {

	if (playerState != attack) {
		if (Value == 0 && !usingMoveForward) { // 움직이지 않는 경우
			playerState = idle;
		}
		else { // 움직이는 경우 

			if (playerState != run && playerState != dash) { // 상태가 run또는 dash가 아니라면 run을 넣어달라
				playerState = run;
			}

			FRotator Rotation = Controller->GetControlRotation();
			FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

			FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
			//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

			if (playerState == dash) { // 대쉬일 경우에 1.5배 속으로 대쉬를 하게 하고
				AddMovementInput(Direction, 1.5 *Value);
			}
			else { // 대쉬가 아니다, 즉 일반 이동일 경우에 일반 이동 수치만큼 이동한다.
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
	else if (playerState == attack && usingAttack && comboCount <2) { //콤보 0->1->2 따라서 2가 마지막 공격임
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
	if (playerState != attack && playerState != idle && !usingDash) { // 공격중에는 대쉬를 사용하지 못함
		if (playerState != dash) { playerState = dash; }

		if (myAnimInst != nullptr) {
			usingDash = true; // 대쉬를 하고 있다는 변수를 true
			myAnimInst->Dash(); // 대쉬 애니메이션을 사용
		}
	}
}

void ATestPlayer::playerAnimation()
{
	if (myAnimInst != nullptr) { //myAnimInst가 null이 아니라면 상태에 따라 애니메이션 ㅅ

		switch (playerState) {
			case idle:
				if (usingDash && !(myAnimInst->Montage_IsPlaying(myAnimInst->dashMontage))) {
					// 대쉬를 사용했다는 변수가 true이고 대쉬 애니메이션이 작동하지 않고 있다 = 대쉬가 끝났다.
					usingDash = false; // 대쉬 변수를 false 로 해줌 
					playerState = idle; // 대쉬가 끝나면 Idle로 상태를 초기화 해줌
				}else if (playerState == idle && !(myAnimInst->Montage_IsPlaying(myAnimInst->idleMontage))) {
					DoIdle(); // idle 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
				}
				break;
			case run:
				if (playerState == run && !(myAnimInst->Montage_IsPlaying(myAnimInst->runMontage))) {
					if (myAnimInst != nullptr) { // 이동 상태인데 이동 애니메이션을 안쓰고 있으면
						myAnimInst->Run();       // 이동 애니메이션을 불러온다 
					}
				}
				break;
			case dash:
				if (usingDash && !(myAnimInst->Montage_IsPlaying(myAnimInst->dashMontage))) {
					// 대쉬를 사용했다는 변수가 true이고 대쉬 애니메이션이 작동하지 않고 있다 = 대쉬가 끝났다.
					usingDash = false; // 대쉬 변수를 false 로 해줌 
					playerState = idle; // 대쉬가 끝나면 Idle로 상태를 초기화 해줌
				} 
				break;
			case attack:
				if (usingAttack && !(myAnimInst->Montage_IsPlaying(myAnimInst->attackMontage))) {
					// 공격 사용 변수가 true이고 현재 공격 애니메이션을 쓰지 않는다 = 공격이 끝났다.
					usingAttack = false; // 공격 사용 변수 false
					comboCount = 0;
					playerState = idle; // idle 애니메이션으로 변경
				
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
