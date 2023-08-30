#pragma once


#define DEVICE	CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetDeviceContext()

#define CLONE(type) public: virtual type* Clone() { return new type(*this); }//복사생성자를 호출시킨다.
#define CLONE_DISABLE(type) public: virtual type* Clone() { return nullptr; assert(nullptr); }

#define KEY_TAP(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::TAP
#define KEY_PRESSED(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::PRESSED
#define KEY_RELEASE(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::RELEASE
#define KEY_NONE(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::NONE


#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define EditorDT CTimeMgr::GetInst()->GetEditorDeltaTime()

#define MAX_LAYER 32
#define SINGLE(type) private: type(); ~type(); friend class CSingleton<type>;

enum class COMPONENT_TYPE
{
	//update
	TRANSFORM,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	LIGHT2D,
	LIGHT3D,
	CAMERA,
	FSMCOM,
	RIGIDBODY,

	//render
	MESHRENDER,
	PARTICLESYSTEM,
	TILEMAP,
	LANDSCAPE,
	DECAL,
	END,

	//custom
	SCRIPT,
	
};

extern const char* COMPONENT_TYPE_STR[(UINT)COMPONENT_TYPE::END];
extern const wchar_t* COMPONENT_TYPE_WSTR[(UINT)COMPONENT_TYPE::END];

enum class RES_TYPE
{
	MESHDATA,
	MATERIAL,
	PREFAB,

	MESH,			// 형태
	TEXTURE,		// 이미지
	SOUND,

	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

//extern으로 선언시 구현부가 있어야함.
//extern.cpp에 구현
extern const char* RES_TYPE_STR[(UINT)RES_TYPE::END];
extern const wchar_t* RES_TYPE_WSTR[(UINT)RES_TYPE::END];

enum class CB_TYPE
{
	TRANSFORM,	// b0
	MATERIAL,	// b1
	GLOBAL,		// b2

	END,
};

enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,
	INT_4,
	INT_5,
	INT_6,
	INT_7,
	

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,

	TEX_CUBE_0,
	TEX_CUBE_1,

	TEX_ARR_0,
	TEX_ARR_1,

	TEX_END,
};

enum PIPELINE_STAGE
{
	PS_VERTEX = 0x01,
	PS_HULL = 0x02,
	PS_DOMAIN = 0x04,
	PS_GEOMETRY = 0x08,
	PS_PIXEL = 0x10,

	PS_ALL = PS_VERTEX | PS_HULL | PS_DOMAIN | PS_GEOMETRY | PS_PIXEL,
};

enum class RS_TYPE
{
	CULL_BACK, // Default,뒷면이 안보인다.
	CULL_FRONT, // 앞면이 안보인다, 구 안에서 하늘 설계할때 사용
	CULL_NONE, // 앞뒷면 다 보임
	WIRE_FRAME, // 정점 제대로 찍혔는지 확인
	END,
};

enum class DS_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
	NO_WRITE,			// LESS, DepthWrite X
	NO_TEST_NO_WRITE,	// Test X, DepthWrite X
	END,
};


enum class BS_TYPE
{
	DEFAULT,		// No Blending
	MASK,			// Alpha Coverage
	ALPHA_BLEND,	// Alpha 계수 
	ONE_ONE,		// 1:1 혼합
	END,
};


enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};

enum class PROJ_TYPE
{
	ORTHOGRAPHIC, //직교
	PERSPECTIVE, //원근
};

enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,		// 불투명 오브젝트
	DOMAIN_MASK,		// 불투명, 투명
	DOMAIN_TRANSPARENT,	// 반투명
	DOMAIN_POSTPROCESS, // 후 처리
	DOMAIN_UI,
	DOMAIN_UNDEFINED,	// 미정
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,

	ADD_CHILD,

	DELETE_RESOURCE, // wParam : RES_TYPE, lParam : Resource Address

	LEVEL_CHANGE,
	CHANGE_AI_STATE,
};

enum class SHAPE_TYPE
{
	RECT,
	CIRCLE,
	CUBE,
	SPHERE,
	END,
};


enum class COLLIDER2D_TYPE
{
	RECT,
	CIRCLE,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
};


enum class LEVEL_STATE
{
	PLAY,
	PAUSE,
	STOP,
};

enum class SB_TYPE
{
	READ_ONLY,
	READ_WRITE,
};

enum class PARTICLE_MODULE
{
	PARTICLE_SPAWN,
	COLOR_CHANGE,
	SCALE_CHANGE,
	ADD_VELOCITY,

	DRAG,
	NOISE_FORCE,
	RENDER,
	GRAVITY,
	END,
};