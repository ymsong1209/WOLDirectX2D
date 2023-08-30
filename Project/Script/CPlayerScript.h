#pragma once
#include <Engine/CScript.h>
#include "CPlayerInfo.h"


class CTexture;

class CPlayerScript :
    public CScript
{
private:
    float       m_fSpeed;
   
    int         m_iPlayerDir;//비트연산자
    Vec4        m_vCapeColor;

    Vec3        m_vDashStartPos;

    PLAYER_SKILL m_ELBtnSkill;
    PLAYER_SKILL m_ERBtnSkill;
    PLAYER_SKILL m_EQSkill;
    PLAYER_SKILL m_EESkill;
    PLAYER_SKILL m_ERSkill;

    float        m_fLBtnCoolTime;
    float        m_fRBtnCoolTime;
    float        m_fECoolTime;
    float        m_fQCoolTime;
    float        m_fRCoolTime;

    float        m_fLBtnCurCoolTime;
    float        m_fRBtnCurCoolTime;
    float        m_fECurCoolTime;
    float        m_fQCurCoolTime;
    float        m_fRCurCoolTime;

    PLAYER_ATTACKBUTTON m_EAttackBtn;
    bool         m_bUltReady;
    bool         m_bIsDeadState;

    PlayerStat          m_Stat;


    CGameObject* m_pTileMap;

public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;
    virtual void OnOverlap(CCollider2D* _Other) override;
    virtual void EndOverlap(CCollider2D* _Other) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

public:
    const int& GetPlayerDir() { return m_iPlayerDir; }
    void SetPlayerDir(int _dir) { m_iPlayerDir = _dir; }
    const float& GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _speed) { m_fSpeed = _speed; }

    const Vec4& GetCapeColor() { return m_vCapeColor; }
    void SetCapeColor(Vec4 color) { m_vCapeColor = color; }

    const Vec3& GetDashStartPos() { return m_vDashStartPos; }
    void SetDashStartPos(Vec3 _Pos) { m_vDashStartPos = _Pos; }

    const PLAYER_ATTACKBUTTON& GetAttackBtn() { return m_EAttackBtn; }
    void SetAttackBtn(PLAYER_ATTACKBUTTON _btn) { m_EAttackBtn = _btn; }

    // 현재 버튼이 무슨 skill을 담당하고 있는지 return, AttackScript용도로 정함
    const PLAYER_SKILL& GetSkillPerAttackBtn();
    // UI를 통해 스킬 재배치
    // 성공 1 반환 실패 2 반환;
    int ChangePlayerSkill(PLAYER_ATTACKBUTTON _Originbtn, PLAYER_SKILL _OriginSkill, float _OriginCoolTime,
                           PLAYER_ATTACKBUTTON _Destbtn, PLAYER_SKILL _DestSkill, float _DestCoolTime);
    // 스킬 재배치를 하는데 스킬 쿨타임이 돌고 있으면 안됨
    // 성공 1반환 실패 2반환
    int CheckOtherSkillSlot();
    
    //아르카나 획득시 SetSkill 호출
    void SetSkill(PLAYER_ATTACKBUTTON _btn, PLAYER_SKILL _skill, float _CoolTime);

    //레벨이 생성되고 나서 레벨이 전환된다. 플레이어의 정보를 PlayerInfo에 저장하기 위해 Teleport에서 미리 호출
    void SetPlayerInfo();


    const PLAYER_SKILL& GetSkillPerBtn(int BtnNum);
    const float& GetCoolTimePerSkill(int BtnNum);

    const float& GetCurCoolTimePerBtn(PLAYER_ATTACKBUTTON _btn);
    void SetCoolTimePerBtn(PLAYER_ATTACKBUTTON _btn, float _CoolTime);
    void SetCurCoolTimetoMax(PLAYER_ATTACKBUTTON _btn);

    bool GetUltReady() { return m_bUltReady; }
    const PlayerStat& GetStat() { return m_Stat; }
    void SetStat(PlayerStat stat) { m_Stat = stat; }

    bool IsPlayerOnGround();

    const bool& IsPlayerDeadState() { return m_bIsDeadState; }
    void SetPlayerDeadState(bool _bool) { m_bIsDeadState = _bool; }

    const PLAYER_SKILL& GetLBtnSkill() { return m_ELBtnSkill; }
    const PLAYER_SKILL& GetRBtnSkill() { return m_ERBtnSkill; }
    const PLAYER_SKILL& GetQSkill() { return m_EQSkill; }
    const PLAYER_SKILL& GetESkill() { return m_EESkill; }
    const PLAYER_SKILL& GetRSkill() { return m_ERSkill; }

    const float& GetLBtnCurCoolTime() { return m_fLBtnCurCoolTime; }
    const float& GetRBtnCurCoolTime() { return m_fRBtnCurCoolTime; }
    const float& GetQCurCoolTime() { return m_fQCurCoolTime; }
    const float& GetECurCoolTime() { return m_fECurCoolTime; }
    const float& GetRCurCoolTime() { return m_fRCurCoolTime; }

    const float& GetLBtnCoolTime() { return m_fLBtnCoolTime; }
    const float& GetRBtnCoolTime() { return m_fRBtnCoolTime; }
    const float& GetQCoolTime() { return m_fQCoolTime; }
    const float& GetECoolTime() { return m_fECoolTime; }
    const float& GetRCoolTime() { return m_fRCoolTime; }


public:
    void NormalAttackCoolTimeCheck();

private:
    void Shoot();
   
    void GetAngle();
    float m_fAngle;
  
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    CPlayerScript(const CPlayerScript& _other);
    ~CPlayerScript();
};

