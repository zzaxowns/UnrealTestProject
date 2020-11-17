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

	static ConstructorHelpers::FClassFinder<UAnimInstance>BLADER_ANIM(TEXT("AnimBlueprint'/Game/Animation_BP/Shinbi_Animation_BP.Shinbi_Animation_BP_C'"));

	if (BLADER_ANIM.Succeeded()) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BLADER success"));
		GetMesh()->SetAnimInstanceClass(BLADER_ANIM.Class);
	}

	playerState = idle; // 맨 처음 플레이어의 상태를 idle로 지정
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
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATestPlayer::DoRun); //이동 애니메이션 추가
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ATestPlayer::DoIdle); // 이동하지 않을 때의 애니메이션

	//대쉬 관련 함수 연결
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ATestPlayer::DoDash);
	//PlayerInputComponent->BindAction("Dash", IE_Released, this, &ATestPlayer::GoToIdle);
}

void ATestPlayer::MoveForward(float Value) {
	/*FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);*/

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	
	FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ATestPlayer::MoveRight(float Value) {

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	
	FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);

}

void ATestPlayer::DoAttack()
{
	if (playerState != attack) { playerState = attack; }
	
	if (myAnimInst != nullptr) {
		myAnimInst->Attack();
	}
}

void ATestPlayer::DoRun() {
	if (playerState != run) { playerState = run; }

	if (myAnimInst != nullptr) {
		myAnimInst->Run();
	}
}

void ATestPlayer::DoIdle() {
	if (playerState != idle) { playerState = idle; }

	if (myAnimInst != nullptr) {
		myAnimInst->Idle();
	}
}

void ATestPlayer::DoDash(){
	if (playerState != dash) { playerState = dash; }

	if (myAnimInst != nullptr) {
		myAnimInst->Dash();
	}
}

void ATestPlayer::playerAnimation()
{
	if (myAnimInst != nullptr) { //myAnimInst가 null이 아니라면 상태에 따라 애니메이션 ㅅ

		switch (playerState) {
			case idle:
				if (playerState == idle && !(myAnimInst->Montage_IsPlaying(myAnimInst->idleMontage))) {
					DoIdle(); // idle 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
				}
				break;
			case run:
				if (playerState == run && !(myAnimInst->Montage_IsPlaying(myAnimInst->runMontage))) {
					DoRun(); // run 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
				}
				break;
			case dash:
				if (playerState == dash && !(myAnimInst->Montage_IsPlaying(myAnimInst->dashMontage))) {
					DoDash(); // dash 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
				}
				break;
			case attack:
				if (playerState == attack && !(myAnimInst->Montage_IsPlaying(myAnimInst->attackMontage))) {
					DoAttack(); // attack 상태인데 애니메이션이 작동하지 않으면 애니메이션을 작동시킴
				}
				break;
			default:
				break;
		}
	}
}
