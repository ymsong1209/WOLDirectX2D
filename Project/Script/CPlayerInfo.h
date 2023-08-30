#pragma once

enum class PLAYER_ATTACKBUTTON {
    LBTN,
    RBTN,
    Q,
    E,
    R,
    NONE,
    END,
};

enum class PLAYER_SKILL {
    NORMALATTACK,
    SNOWFLAKE,
    DRAGONBREATH,
    METEOR,
    WATERBALL,
    NONE,
    END,
};

struct PlayerStat {
	float MaxHP;
    float MaxMP;
	float CurHP;
    float CurMP;
};

class CPlayerInfo
    : public CSingleton<CPlayerInfo>
{
private:
    PlayerStat m_Stat;

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

    Vec4         m_vCapeColor;
public:
	SINGLE(CPlayerInfo);

public:
    void SetStat(const PlayerStat& stat) { m_Stat = stat; }
    PlayerStat GetStat() { return m_Stat; }

    const PLAYER_SKILL& GetLBtnSkill() { return m_ELBtnSkill; }
    void SetLBtnSkill(PLAYER_SKILL _skill) { m_ELBtnSkill = _skill; }
    const PLAYER_SKILL& GetRBtnSkill() { return m_ERBtnSkill; }
    void SetRBtnSkill(PLAYER_SKILL _skill) { m_ERBtnSkill = _skill; }
    const PLAYER_SKILL& GetQSkill() { return m_EQSkill; }
    void SetQSkill(PLAYER_SKILL _skill) { m_EQSkill = _skill; }
    const PLAYER_SKILL& GetESkill() { return m_EESkill; }
    void SetESkill(PLAYER_SKILL _skill) { m_EESkill = _skill; }
    const PLAYER_SKILL& GetRSkill() { return m_ERSkill; }
    void SetRSkill(PLAYER_SKILL _skill) { m_ERSkill = _skill; }

    const float& GetLBtnCoolTime() { return m_fLBtnCoolTime; }
    void SetLBtnCoolTime(float _time) { m_fLBtnCoolTime = _time; }
    const float& GetRBtnCoolTime() { return m_fRBtnCoolTime; }
    void SetRBtnCoolTime(float _time) { m_fRBtnCoolTime = _time; }
    const float& GetQCoolTime() { return m_fQCoolTime; }
    void SetQCoolTime(float _time) { m_fQCoolTime = _time; }
    const float& GetECoolTime() { return m_fECoolTime; }
    void SetECoolTime(float _time) { m_fECoolTime = _time; }
    const float& GetRCoolTime() { return m_fRCoolTime; }
    void SetRCoolTime(float _time) { m_fRCoolTime = _time; }

    Vec4 GetCapeColor() { return m_vCapeColor; }
    void SetCapeColor(Vec4 CapeColor) { m_vCapeColor = CapeColor; }

};

