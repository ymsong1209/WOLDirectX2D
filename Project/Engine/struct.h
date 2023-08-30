#pragma once

struct tVertex
{
	Vec3 vPos; //NDC ��ǥ�� 
	Vec4 vColor;
	Vec2 vUV; //UV ��ǥ��
};

typedef tVertex Vtx;

// Event
struct tEvent
{
	EVENT_TYPE	Type;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
	DWORD_PTR   CustomParam;
};

struct tDebugShapeInfo
{
	SHAPE_TYPE	eShape;
	Matrix		matWorld;
	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRotation;
	Vec4		vColor;
	float		fMaxTime;
	float		fCurTime;
};

struct tLightColor
{
	Vec4 vDiffuse;	// ���� ����
	Vec4 vAmbient;	// �ֺ� ��(ȯ�� ��), �ּ��� ������ �� �ִ� ��
};

// LightInfo
struct tLightInfo
{
	tLightColor Color;		 // ���� ����

	Vec4		vWorldPos;   // ������ ���� �����̽� ��ġ, finaltick���� transform�� worldpos������
	Vec4		vWorldDir;	 // ���� ������ ����, finaltick���� transform�� right���� ������

	UINT		LightType;   // ���� Ÿ��(���⼺, ��, ����Ʈ)
	float		Radius;		 // ���� �ݰ�(��Ÿ�)
	float		Angle;		 // ���� ����
	int			padding;
};



// TileMap
struct tTile
{
	int Type; //0:Default, 1:Ground 2:Pit
	Vec3 vCenterPos;

	Vec2 vLeftTop;
	Vec2 vSlice;
};

// Animator2D
struct tAnim2DFrm
{
	Vec2	LeftTopUV;
	Vec2	SliceUV;
	Vec2	Offset;
	float	fDuration;
};


// Particle
struct tParticle
{
	Vec4	vLocalPos;		// ������Ʈ�κ��� ������ �Ÿ�
	Vec4	vWorldPos;		// ��ƼŬ ���� ������ġ
	Vec4	vWorldScale;	// ��ƼŬ ũ��
	Vec4	vColor;			// ��ƼŬ ����
	Vec4	vVelocity;		// ��ƼŬ ���� �ӵ�
	Vec4	vForce;			// ��ƼŬ�� �־��� ��
	Vec4	vRandomForce;	// ��ƼŬ�� ����Ǵ� �������� ��

	float   Age;			// ���� �ð�
	float   PrevAge;		// ���� ������ ���� �ð�
	float   NormalizedAge;	// ������ �����ð��� 0~1�� ����ȭ �� ��
	float	LifeTime;		// ����
	float	Mass;			// ����
	float   ScaleFactor;	// �߰� ũ�� ����

	int     Active;			// ��ƼŬ Ȱ��ȭ ����
	int     pad;
};

struct tRWParticleBuffer
{
	int		SpawnCount;			// ���� ��ų ��ƼŬ ����
	int		padding[3];
};


struct tParticleModule
{
	// ���� ���
	Vec4    vSpawnColor;
	Vec4	vSpawnScaleMin;
	Vec4	vSpawnScaleMax;
	Vec3	vBoxShapeScale;
	float	fSphereShapeRadius;
	int		SpawnShapeType;		// 0 : BOX, 1 : Sphere
	int		SpawnRate;			// �ʴ� ���� ����
	int		Space;				// ��ƼŬ ������Ʈ ��ǥ�� ( 0 : World,  1 : Local)
	float   MinLifeTime;		// �ּ� ����
	float   MaxLifeTime;		// �ִ� ����
	int     spawnpad[3];

	// Color Change ���
	Vec4	vStartColor;		// �ʱ� ����
	Vec4	vEndColor;			// ���� ����

	// Scale Change ���
	float	StartScale;			// �ʱ� ����
	float	EndScale;			// ���� ����	

	// ���� �ִ�ũ��
	int		iMaxParticleCount;
	int		ipad;

	// Add Velocity ���
	Vec4	vVelocityDir;
	int     AddVelocityType;	// 0 : From Center, 1: To Center, 2 : Fixed Direction	
	float	OffsetAngle;
	float	Speed;
	int     addvpad;

	// Drag ��� - �ӵ� ����
	float	StartDrag;
	float	EndDrag;
	
	// NoiseForce ��� - ���� �� ����	
	float	fNoiseTerm;		// ���� �� ���� ����
	float	fNoiseForce;	// ���� �� ũ��

	// Gravity ��� - �߷� �߰�
	float	fGravityForce;	
	float	GravityPad[3];


	// Render ���
	int		VelocityAlignment;	// 1 : �ӵ����� ���(�̵� �������� ȸ��) 0 : ��� ����
	int		VelocityScale;		// 1 : �ӵ��� ���� ũ�� ��ȭ ���, 0 : ��� ����	
	int		AnimationUse;		// 1 : �ִϸ��̼� ���, 0 : ��� ����
	int		AnimationLoop;		// 1 : �ִϸ��̼� ����, 0 : ���� �°� �ѹ���
	int     bRotate;			// 1 : ȸ����, 0 : ȸ������

	float   vMaxSpeed;			// �ִ� ũ�⿡ �����ϴ� �ӷ�
	float   fRotationAngle;
	float   fRotateSpeed;
	Vec4	vMaxVelocityScale;	// �ӷ¿� ���� ũ�� ��ȭ�� �ִ�ġ

	int		iAnimXCount;
	int		iAnimYCount;
	float	fAnimFrmTime;

	int		renderpad;

	// Module Check
	int		ModuleCheck[(UINT)PARTICLE_MODULE::END];

	
};


// ===================
// ������� ���� ����ü
// ===================
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;

	Matrix matWV;
	Matrix matWVP;
};

extern tTransform g_transform; //��� cpp���� �����ִ� ��������, ����� extern.cpp���� �����������.

struct tMtrlConst
{
	int arrInt[8];
	float arrFloat[4];
	Vec2 arrV2[4];
	Vec4 arrV4[4];
	Matrix arrMat[4];

	int arrTex[(UINT)TEX_PARAM::TEX_END];
};

struct tGlobal
{
	Vec2  Resolution;		//CDevice���� ����
	float tDT;				//TimeMgr���� ����
	float tAccTime;			//TimeMgr
	UINT  Light2DCount;		//RenderMgr	
	UINT  Light3DCount;
	int	  globalpadding[2];
};

extern tGlobal GlobalData;


