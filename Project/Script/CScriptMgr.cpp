#include "pch.h"
#include "CScriptMgr.h"

#include "CBackHandAttackScript.h"
#include "CBGMScript.h"
#include "CBlackHoleParticleScript.h"
#include "CBossAttackScript.h"
#include "CBossDeadScript.h"
#include "CBossDrillScript.h"
#include "CBossEnterScript.h"
#include "CBossFireflyScript.h"
#include "CBossFlexScript.h"
#include "CBossFloorScript.h"
#include "CBossHitBoxScript.h"
#include "CBossHitScript.h"
#include "CBossHPScript.h"
#include "CBossIdleScript.h"
#include "CBossLeapAttackHitBoxScript.h"
#include "CBossLeapAttackScript.h"
#include "CBossPitScript.h"
#include "CBossScript.h"
#include "CBossUIScript.h"
#include "CBossWallScript.h"
#include "CBossWaveScript.h"
#include "CCameraMoveScript.h"
#include "CChaosBombScript.h"
#include "CChildScript.h"
#include "CDashEffectScript.h"
#include "CDragonArcArcanaScript.h"
#include "CDragonBreathScript.h"
#include "CDragonParticleScript.h"
#include "CESkillSlotScript.h"
#include "CExplosionParticleScript.h"
#include "CFireParticleScript.h"
#include "CForeHandAttackScript.h"
#include "CGhoulAttackScript.h"
#include "CGhoulAttackTraceScript.h"
#include "CGhoulDeadScript.h"
#include "CGhoulFallScript.h"
#include "CGhoulHitBoxScript.h"
#include "CGhoulHitScript.h"
#include "CGhoulIdleScript.h"
#include "CGhoulScript.h"
#include "CGhoulSpawnScript.h"
#include "CGhoulTraceScript.h"
#include "CGhoulWaitScript.h"
#include "CHitEffectScript.h"
#include "CHomeFloorScript.h"
#include "CHomeOverlayScript.h"
#include "CHomeWallScript.h"
#include "CIceCrystalArcanaScript.h"
#include "CLBtnSkillSlotScript.h"
#include "CMageAttackScript.h"
#include "CMageBallAfterImageScript.h"
#include "CMageBallAttackScript.h"
#include "CMageBallDeadScript.h"
#include "CMageBallHitboxScript.h"
#include "CMageBallIdleScript.h"
#include "CMageBallScript.h"
#include "CMageBallSpawnScript.h"
#include "CMageBallTraceScript.h"
#include "CMageDeadScript.h"
#include "CMageHitBoxScript.h"
#include "CMageHitScript.h"
#include "CMageIdleScript.h"
#include "CMageScript.h"
#include "CMageSpawnScript.h"
#include "CMageWaitScript.h"
#include "CMainLightScript.h"
#include "CMainMenuScript.h"
#include "CMapPortalScript.h"
#include "CMapScript.h"
#include "CMerchantRugScript.h"
#include "CMerchantScript.h"
#include "CMeteorArcanaScript.h"
#include "CMeteorDamageZoneScript.h"
#include "CMeteorFloorCrackScript.h"
#include "CMeteorRingScript.h"
#include "CMeteorScript.h"
#include "CMeteorSmokeParticleScript.h"
#include "CMeteorSpawnCircleScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CMonsterSpawnPointScript.h"
#include "CMousePointerScript.h"
#include "COverlayScript.h"
#include "CPitScript.h"
#include "CPlayerAfterImageScript.h"
#include "CPlayerAttackScript.h"
#include "CPlayerCameraScript.h"
#include "CPlayerColorScript.h"
#include "CPlayerDashScript.h"
#include "CPlayerDashStopScript.h"
#include "CPlayerDeadScript.h"
#include "CPlayerDustScript.h"
#include "CPlayerEScript.h"
#include "CPlayerFaceUIScript.h"
#include "CPlayerFallScript.h"
#include "CPlayerHitBoxScript.h"
#include "CPlayerHitScript.h"
#include "CPlayerHPScript.h"
#include "CPlayerHurtUIScript.h"
#include "CPlayerIdleScript.h"
#include "CPlayerLBtnScript.h"
#include "CPlayerMarkerScript.h"
#include "CPlayerMPScript.h"
#include "CPlayerQBtnScript.h"
#include "CPlayerRBtnScript.h"
#include "CPlayerRScript.h"
#include "CPlayerScript.h"
#include "CPlayerSkillBarScript.h"
#include "CPlayerSkillSlotScript.h"
#include "CPlayerSlideScript.h"
#include "CPlayerWalkScript.h"
#include "CPortalParticleScript.h"
#include "CPortalSummonEffectScript.h"
#include "CPotionScript.h"
#include "CPressEnterScript.h"
#include "CQSkillSlotScript.h"
#include "CRainParticleScript.h"
#include "CRBtnSkillSlotScript.h"
#include "CRockFistScript.h"
#include "CRSkillSlotScript.h"
#include "CSelectedSkillSlotScript.h"
#include "CSkillArrowScript.h"
#include "CSkillYellowArrowScript.h"
#include "CSnowFlakeScript.h"
#include "CSnowParticleScript.h"
#include "CSwordManAttackScript.h"
#include "CSwordManAttackTraceScript.h"
#include "CSwordManDeadScript.h"
#include "CSwordManFallScript.h"
#include "CSwordManHitBoxScript.h"
#include "CSwordManHitScript.h"
#include "CSwordManIdleScript.h"
#include "CSwordManScript.h"
#include "CSwordManSpawnScript.h"
#include "CSwordManTraceScript.h"
#include "CSwordManWaitScript.h"
#include "CTerraScript.h"
#include "CTowerScript.h"
#include "CWallScript.h"
#include "CWardrobeArrowScript.h"
#include "CWardrobeScript.h"
#include "CWardrobeUIScript.h"
#include "CWaterBallArcanaScript.h"
#include "CWaterBombScript.h"
#include "CWaveWallHorScript.h"
#include "CWaveWallVerScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackHandAttackScript");
	_vec.push_back(L"CBGMScript");
	_vec.push_back(L"CBlackHoleParticleScript");
	_vec.push_back(L"CBossAttackScript");
	_vec.push_back(L"CBossDeadScript");
	_vec.push_back(L"CBossDrillScript");
	_vec.push_back(L"CBossEnterScript");
	_vec.push_back(L"CBossFireflyScript");
	_vec.push_back(L"CBossFlexScript");
	_vec.push_back(L"CBossFloorScript");
	_vec.push_back(L"CBossHitBoxScript");
	_vec.push_back(L"CBossHitScript");
	_vec.push_back(L"CBossHPScript");
	_vec.push_back(L"CBossIdleScript");
	_vec.push_back(L"CBossLeapAttackHitBoxScript");
	_vec.push_back(L"CBossLeapAttackScript");
	_vec.push_back(L"CBossPitScript");
	_vec.push_back(L"CBossScript");
	_vec.push_back(L"CBossUIScript");
	_vec.push_back(L"CBossWallScript");
	_vec.push_back(L"CBossWaveScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CChaosBombScript");
	_vec.push_back(L"CChildScript");
	_vec.push_back(L"CDashEffectScript");
	_vec.push_back(L"CDragonArcArcanaScript");
	_vec.push_back(L"CDragonBreathScript");
	_vec.push_back(L"CDragonParticleScript");
	_vec.push_back(L"CESkillSlotScript");
	_vec.push_back(L"CExplosionParticleScript");
	_vec.push_back(L"CFireParticleScript");
	_vec.push_back(L"CForeHandAttackScript");
	_vec.push_back(L"CGhoulAttackScript");
	_vec.push_back(L"CGhoulAttackTraceScript");
	_vec.push_back(L"CGhoulDeadScript");
	_vec.push_back(L"CGhoulFallScript");
	_vec.push_back(L"CGhoulHitBoxScript");
	_vec.push_back(L"CGhoulHitScript");
	_vec.push_back(L"CGhoulIdleScript");
	_vec.push_back(L"CGhoulScript");
	_vec.push_back(L"CGhoulSpawnScript");
	_vec.push_back(L"CGhoulTraceScript");
	_vec.push_back(L"CGhoulWaitScript");
	_vec.push_back(L"CHitEffectScript");
	_vec.push_back(L"CHomeFloorScript");
	_vec.push_back(L"CHomeOverlayScript");
	_vec.push_back(L"CHomeWallScript");
	_vec.push_back(L"CIceCrystalArcanaScript");
	_vec.push_back(L"CLBtnSkillSlotScript");
	_vec.push_back(L"CMageAttackScript");
	_vec.push_back(L"CMageBallAfterImageScript");
	_vec.push_back(L"CMageBallAttackScript");
	_vec.push_back(L"CMageBallDeadScript");
	_vec.push_back(L"CMageBallHitboxScript");
	_vec.push_back(L"CMageBallIdleScript");
	_vec.push_back(L"CMageBallScript");
	_vec.push_back(L"CMageBallSpawnScript");
	_vec.push_back(L"CMageBallTraceScript");
	_vec.push_back(L"CMageDeadScript");
	_vec.push_back(L"CMageHitBoxScript");
	_vec.push_back(L"CMageHitScript");
	_vec.push_back(L"CMageIdleScript");
	_vec.push_back(L"CMageScript");
	_vec.push_back(L"CMageSpawnScript");
	_vec.push_back(L"CMageWaitScript");
	_vec.push_back(L"CMainLightScript");
	_vec.push_back(L"CMainMenuScript");
	_vec.push_back(L"CMapPortalScript");
	_vec.push_back(L"CMapScript");
	_vec.push_back(L"CMerchantRugScript");
	_vec.push_back(L"CMerchantScript");
	_vec.push_back(L"CMeteorArcanaScript");
	_vec.push_back(L"CMeteorDamageZoneScript");
	_vec.push_back(L"CMeteorFloorCrackScript");
	_vec.push_back(L"CMeteorRingScript");
	_vec.push_back(L"CMeteorScript");
	_vec.push_back(L"CMeteorSmokeParticleScript");
	_vec.push_back(L"CMeteorSpawnCircleScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CMonsterSpawnPointScript");
	_vec.push_back(L"CMousePointerScript");
	_vec.push_back(L"COverlayScript");
	_vec.push_back(L"CPitScript");
	_vec.push_back(L"CPlayerAfterImageScript");
	_vec.push_back(L"CPlayerAttackScript");
	_vec.push_back(L"CPlayerCameraScript");
	_vec.push_back(L"CPlayerColorScript");
	_vec.push_back(L"CPlayerDashScript");
	_vec.push_back(L"CPlayerDashStopScript");
	_vec.push_back(L"CPlayerDeadScript");
	_vec.push_back(L"CPlayerDustScript");
	_vec.push_back(L"CPlayerEScript");
	_vec.push_back(L"CPlayerFaceUIScript");
	_vec.push_back(L"CPlayerFallScript");
	_vec.push_back(L"CPlayerHitBoxScript");
	_vec.push_back(L"CPlayerHitScript");
	_vec.push_back(L"CPlayerHPScript");
	_vec.push_back(L"CPlayerHurtUIScript");
	_vec.push_back(L"CPlayerIdleScript");
	_vec.push_back(L"CPlayerLBtnScript");
	_vec.push_back(L"CPlayerMarkerScript");
	_vec.push_back(L"CPlayerMPScript");
	_vec.push_back(L"CPlayerQBtnScript");
	_vec.push_back(L"CPlayerRBtnScript");
	_vec.push_back(L"CPlayerRScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerSkillBarScript");
	_vec.push_back(L"CPlayerSkillSlotScript");
	_vec.push_back(L"CPlayerSlideScript");
	_vec.push_back(L"CPlayerWalkScript");
	_vec.push_back(L"CPortalParticleScript");
	_vec.push_back(L"CPortalSummonEffectScript");
	_vec.push_back(L"CPotionScript");
	_vec.push_back(L"CPressEnterScript");
	_vec.push_back(L"CQSkillSlotScript");
	_vec.push_back(L"CRainParticleScript");
	_vec.push_back(L"CRBtnSkillSlotScript");
	_vec.push_back(L"CRockFistScript");
	_vec.push_back(L"CRSkillSlotScript");
	_vec.push_back(L"CSelectedSkillSlotScript");
	_vec.push_back(L"CSkillArrowScript");
	_vec.push_back(L"CSkillYellowArrowScript");
	_vec.push_back(L"CSnowFlakeScript");
	_vec.push_back(L"CSnowParticleScript");
	_vec.push_back(L"CSwordManAttackScript");
	_vec.push_back(L"CSwordManAttackTraceScript");
	_vec.push_back(L"CSwordManDeadScript");
	_vec.push_back(L"CSwordManFallScript");
	_vec.push_back(L"CSwordManHitBoxScript");
	_vec.push_back(L"CSwordManHitScript");
	_vec.push_back(L"CSwordManIdleScript");
	_vec.push_back(L"CSwordManScript");
	_vec.push_back(L"CSwordManSpawnScript");
	_vec.push_back(L"CSwordManTraceScript");
	_vec.push_back(L"CSwordManWaitScript");
	_vec.push_back(L"CTerraScript");
	_vec.push_back(L"CTowerScript");
	_vec.push_back(L"CWallScript");
	_vec.push_back(L"CWardrobeArrowScript");
	_vec.push_back(L"CWardrobeScript");
	_vec.push_back(L"CWardrobeUIScript");
	_vec.push_back(L"CWaterBallArcanaScript");
	_vec.push_back(L"CWaterBombScript");
	_vec.push_back(L"CWaveWallHorScript");
	_vec.push_back(L"CWaveWallVerScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackHandAttackScript" == _strScriptName)
		return new CBackHandAttackScript;
	if (L"CBGMScript" == _strScriptName)
		return new CBGMScript;
	if (L"CBlackHoleParticleScript" == _strScriptName)
		return new CBlackHoleParticleScript;
	if (L"CBossAttackScript" == _strScriptName)
		return new CBossAttackScript;
	if (L"CBossDeadScript" == _strScriptName)
		return new CBossDeadScript;
	if (L"CBossDrillScript" == _strScriptName)
		return new CBossDrillScript;
	if (L"CBossEnterScript" == _strScriptName)
		return new CBossEnterScript;
	if (L"CBossFireflyScript" == _strScriptName)
		return new CBossFireflyScript;
	if (L"CBossFlexScript" == _strScriptName)
		return new CBossFlexScript;
	if (L"CBossFloorScript" == _strScriptName)
		return new CBossFloorScript;
	if (L"CBossHitBoxScript" == _strScriptName)
		return new CBossHitBoxScript;
	if (L"CBossHitScript" == _strScriptName)
		return new CBossHitScript;
	if (L"CBossHPScript" == _strScriptName)
		return new CBossHPScript;
	if (L"CBossIdleScript" == _strScriptName)
		return new CBossIdleScript;
	if (L"CBossLeapAttackHitBoxScript" == _strScriptName)
		return new CBossLeapAttackHitBoxScript;
	if (L"CBossLeapAttackScript" == _strScriptName)
		return new CBossLeapAttackScript;
	if (L"CBossPitScript" == _strScriptName)
		return new CBossPitScript;
	if (L"CBossScript" == _strScriptName)
		return new CBossScript;
	if (L"CBossUIScript" == _strScriptName)
		return new CBossUIScript;
	if (L"CBossWallScript" == _strScriptName)
		return new CBossWallScript;
	if (L"CBossWaveScript" == _strScriptName)
		return new CBossWaveScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CChaosBombScript" == _strScriptName)
		return new CChaosBombScript;
	if (L"CChildScript" == _strScriptName)
		return new CChildScript;
	if (L"CDashEffectScript" == _strScriptName)
		return new CDashEffectScript;
	if (L"CDragonArcArcanaScript" == _strScriptName)
		return new CDragonArcArcanaScript;
	if (L"CDragonBreathScript" == _strScriptName)
		return new CDragonBreathScript;
	if (L"CDragonParticleScript" == _strScriptName)
		return new CDragonParticleScript;
	if (L"CESkillSlotScript" == _strScriptName)
		return new CESkillSlotScript;
	if (L"CExplosionParticleScript" == _strScriptName)
		return new CExplosionParticleScript;
	if (L"CFireParticleScript" == _strScriptName)
		return new CFireParticleScript;
	if (L"CForeHandAttackScript" == _strScriptName)
		return new CForeHandAttackScript;
	if (L"CGhoulAttackScript" == _strScriptName)
		return new CGhoulAttackScript;
	if (L"CGhoulAttackTraceScript" == _strScriptName)
		return new CGhoulAttackTraceScript;
	if (L"CGhoulDeadScript" == _strScriptName)
		return new CGhoulDeadScript;
	if (L"CGhoulFallScript" == _strScriptName)
		return new CGhoulFallScript;
	if (L"CGhoulHitBoxScript" == _strScriptName)
		return new CGhoulHitBoxScript;
	if (L"CGhoulHitScript" == _strScriptName)
		return new CGhoulHitScript;
	if (L"CGhoulIdleScript" == _strScriptName)
		return new CGhoulIdleScript;
	if (L"CGhoulScript" == _strScriptName)
		return new CGhoulScript;
	if (L"CGhoulSpawnScript" == _strScriptName)
		return new CGhoulSpawnScript;
	if (L"CGhoulTraceScript" == _strScriptName)
		return new CGhoulTraceScript;
	if (L"CGhoulWaitScript" == _strScriptName)
		return new CGhoulWaitScript;
	if (L"CHitEffectScript" == _strScriptName)
		return new CHitEffectScript;
	if (L"CHomeFloorScript" == _strScriptName)
		return new CHomeFloorScript;
	if (L"CHomeOverlayScript" == _strScriptName)
		return new CHomeOverlayScript;
	if (L"CHomeWallScript" == _strScriptName)
		return new CHomeWallScript;
	if (L"CIceCrystalArcanaScript" == _strScriptName)
		return new CIceCrystalArcanaScript;
	if (L"CLBtnSkillSlotScript" == _strScriptName)
		return new CLBtnSkillSlotScript;
	if (L"CMageAttackScript" == _strScriptName)
		return new CMageAttackScript;
	if (L"CMageBallAfterImageScript" == _strScriptName)
		return new CMageBallAfterImageScript;
	if (L"CMageBallAttackScript" == _strScriptName)
		return new CMageBallAttackScript;
	if (L"CMageBallDeadScript" == _strScriptName)
		return new CMageBallDeadScript;
	if (L"CMageBallHitboxScript" == _strScriptName)
		return new CMageBallHitboxScript;
	if (L"CMageBallIdleScript" == _strScriptName)
		return new CMageBallIdleScript;
	if (L"CMageBallScript" == _strScriptName)
		return new CMageBallScript;
	if (L"CMageBallSpawnScript" == _strScriptName)
		return new CMageBallSpawnScript;
	if (L"CMageBallTraceScript" == _strScriptName)
		return new CMageBallTraceScript;
	if (L"CMageDeadScript" == _strScriptName)
		return new CMageDeadScript;
	if (L"CMageHitBoxScript" == _strScriptName)
		return new CMageHitBoxScript;
	if (L"CMageHitScript" == _strScriptName)
		return new CMageHitScript;
	if (L"CMageIdleScript" == _strScriptName)
		return new CMageIdleScript;
	if (L"CMageScript" == _strScriptName)
		return new CMageScript;
	if (L"CMageSpawnScript" == _strScriptName)
		return new CMageSpawnScript;
	if (L"CMageWaitScript" == _strScriptName)
		return new CMageWaitScript;
	if (L"CMainLightScript" == _strScriptName)
		return new CMainLightScript;
	if (L"CMainMenuScript" == _strScriptName)
		return new CMainMenuScript;
	if (L"CMapPortalScript" == _strScriptName)
		return new CMapPortalScript;
	if (L"CMapScript" == _strScriptName)
		return new CMapScript;
	if (L"CMerchantRugScript" == _strScriptName)
		return new CMerchantRugScript;
	if (L"CMerchantScript" == _strScriptName)
		return new CMerchantScript;
	if (L"CMeteorArcanaScript" == _strScriptName)
		return new CMeteorArcanaScript;
	if (L"CMeteorDamageZoneScript" == _strScriptName)
		return new CMeteorDamageZoneScript;
	if (L"CMeteorFloorCrackScript" == _strScriptName)
		return new CMeteorFloorCrackScript;
	if (L"CMeteorRingScript" == _strScriptName)
		return new CMeteorRingScript;
	if (L"CMeteorScript" == _strScriptName)
		return new CMeteorScript;
	if (L"CMeteorSmokeParticleScript" == _strScriptName)
		return new CMeteorSmokeParticleScript;
	if (L"CMeteorSpawnCircleScript" == _strScriptName)
		return new CMeteorSpawnCircleScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CMonsterSpawnPointScript" == _strScriptName)
		return new CMonsterSpawnPointScript;
	if (L"CMousePointerScript" == _strScriptName)
		return new CMousePointerScript;
	if (L"COverlayScript" == _strScriptName)
		return new COverlayScript;
	if (L"CPitScript" == _strScriptName)
		return new CPitScript;
	if (L"CPlayerAfterImageScript" == _strScriptName)
		return new CPlayerAfterImageScript;
	if (L"CPlayerAttackScript" == _strScriptName)
		return new CPlayerAttackScript;
	if (L"CPlayerCameraScript" == _strScriptName)
		return new CPlayerCameraScript;
	if (L"CPlayerColorScript" == _strScriptName)
		return new CPlayerColorScript;
	if (L"CPlayerDashScript" == _strScriptName)
		return new CPlayerDashScript;
	if (L"CPlayerDashStopScript" == _strScriptName)
		return new CPlayerDashStopScript;
	if (L"CPlayerDeadScript" == _strScriptName)
		return new CPlayerDeadScript;
	if (L"CPlayerDustScript" == _strScriptName)
		return new CPlayerDustScript;
	if (L"CPlayerEScript" == _strScriptName)
		return new CPlayerEScript;
	if (L"CPlayerFaceUIScript" == _strScriptName)
		return new CPlayerFaceUIScript;
	if (L"CPlayerFallScript" == _strScriptName)
		return new CPlayerFallScript;
	if (L"CPlayerHitBoxScript" == _strScriptName)
		return new CPlayerHitBoxScript;
	if (L"CPlayerHitScript" == _strScriptName)
		return new CPlayerHitScript;
	if (L"CPlayerHPScript" == _strScriptName)
		return new CPlayerHPScript;
	if (L"CPlayerHurtUIScript" == _strScriptName)
		return new CPlayerHurtUIScript;
	if (L"CPlayerIdleScript" == _strScriptName)
		return new CPlayerIdleScript;
	if (L"CPlayerLBtnScript" == _strScriptName)
		return new CPlayerLBtnScript;
	if (L"CPlayerMarkerScript" == _strScriptName)
		return new CPlayerMarkerScript;
	if (L"CPlayerMPScript" == _strScriptName)
		return new CPlayerMPScript;
	if (L"CPlayerQBtnScript" == _strScriptName)
		return new CPlayerQBtnScript;
	if (L"CPlayerRBtnScript" == _strScriptName)
		return new CPlayerRBtnScript;
	if (L"CPlayerRScript" == _strScriptName)
		return new CPlayerRScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerSkillBarScript" == _strScriptName)
		return new CPlayerSkillBarScript;
	if (L"CPlayerSkillSlotScript" == _strScriptName)
		return new CPlayerSkillSlotScript;
	if (L"CPlayerSlideScript" == _strScriptName)
		return new CPlayerSlideScript;
	if (L"CPlayerWalkScript" == _strScriptName)
		return new CPlayerWalkScript;
	if (L"CPortalParticleScript" == _strScriptName)
		return new CPortalParticleScript;
	if (L"CPortalSummonEffectScript" == _strScriptName)
		return new CPortalSummonEffectScript;
	if (L"CPotionScript" == _strScriptName)
		return new CPotionScript;
	if (L"CPressEnterScript" == _strScriptName)
		return new CPressEnterScript;
	if (L"CQSkillSlotScript" == _strScriptName)
		return new CQSkillSlotScript;
	if (L"CRainParticleScript" == _strScriptName)
		return new CRainParticleScript;
	if (L"CRBtnSkillSlotScript" == _strScriptName)
		return new CRBtnSkillSlotScript;
	if (L"CRockFistScript" == _strScriptName)
		return new CRockFistScript;
	if (L"CRSkillSlotScript" == _strScriptName)
		return new CRSkillSlotScript;
	if (L"CSelectedSkillSlotScript" == _strScriptName)
		return new CSelectedSkillSlotScript;
	if (L"CSkillArrowScript" == _strScriptName)
		return new CSkillArrowScript;
	if (L"CSkillYellowArrowScript" == _strScriptName)
		return new CSkillYellowArrowScript;
	if (L"CSnowFlakeScript" == _strScriptName)
		return new CSnowFlakeScript;
	if (L"CSnowParticleScript" == _strScriptName)
		return new CSnowParticleScript;
	if (L"CSwordManAttackScript" == _strScriptName)
		return new CSwordManAttackScript;
	if (L"CSwordManAttackTraceScript" == _strScriptName)
		return new CSwordManAttackTraceScript;
	if (L"CSwordManDeadScript" == _strScriptName)
		return new CSwordManDeadScript;
	if (L"CSwordManFallScript" == _strScriptName)
		return new CSwordManFallScript;
	if (L"CSwordManHitBoxScript" == _strScriptName)
		return new CSwordManHitBoxScript;
	if (L"CSwordManHitScript" == _strScriptName)
		return new CSwordManHitScript;
	if (L"CSwordManIdleScript" == _strScriptName)
		return new CSwordManIdleScript;
	if (L"CSwordManScript" == _strScriptName)
		return new CSwordManScript;
	if (L"CSwordManSpawnScript" == _strScriptName)
		return new CSwordManSpawnScript;
	if (L"CSwordManTraceScript" == _strScriptName)
		return new CSwordManTraceScript;
	if (L"CSwordManWaitScript" == _strScriptName)
		return new CSwordManWaitScript;
	if (L"CTerraScript" == _strScriptName)
		return new CTerraScript;
	if (L"CTowerScript" == _strScriptName)
		return new CTowerScript;
	if (L"CWallScript" == _strScriptName)
		return new CWallScript;
	if (L"CWardrobeArrowScript" == _strScriptName)
		return new CWardrobeArrowScript;
	if (L"CWardrobeScript" == _strScriptName)
		return new CWardrobeScript;
	if (L"CWardrobeUIScript" == _strScriptName)
		return new CWardrobeUIScript;
	if (L"CWaterBallArcanaScript" == _strScriptName)
		return new CWaterBallArcanaScript;
	if (L"CWaterBombScript" == _strScriptName)
		return new CWaterBombScript;
	if (L"CWaveWallHorScript" == _strScriptName)
		return new CWaveWallHorScript;
	if (L"CWaveWallVerScript" == _strScriptName)
		return new CWaveWallVerScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKHANDATTACKSCRIPT:
		return new CBackHandAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::BGMSCRIPT:
		return new CBGMScript;
		break;
	case (UINT)SCRIPT_TYPE::BLACKHOLEPARTICLESCRIPT:
		return new CBlackHoleParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSATTACKSCRIPT:
		return new CBossAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSDEADSCRIPT:
		return new CBossDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSDRILLSCRIPT:
		return new CBossDrillScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSENTERSCRIPT:
		return new CBossEnterScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSFIREFLYSCRIPT:
		return new CBossFireflyScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSFLEXSCRIPT:
		return new CBossFlexScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSFLOORSCRIPT:
		return new CBossFloorScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSHITBOXSCRIPT:
		return new CBossHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSHITSCRIPT:
		return new CBossHitScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSHPSCRIPT:
		return new CBossHPScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSIDLESCRIPT:
		return new CBossIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSLEAPATTACKHITBOXSCRIPT:
		return new CBossLeapAttackHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSLEAPATTACKSCRIPT:
		return new CBossLeapAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSPITSCRIPT:
		return new CBossPitScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new CBossScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSUISCRIPT:
		return new CBossUIScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSWALLSCRIPT:
		return new CBossWallScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSWAVESCRIPT:
		return new CBossWaveScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CHAOSBOMBSCRIPT:
		return new CChaosBombScript;
		break;
	case (UINT)SCRIPT_TYPE::CHILDSCRIPT:
		return new CChildScript;
		break;
	case (UINT)SCRIPT_TYPE::DASHEFFECTSCRIPT:
		return new CDashEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::DRAGONARCARCANASCRIPT:
		return new CDragonArcArcanaScript;
		break;
	case (UINT)SCRIPT_TYPE::DRAGONBREATHSCRIPT:
		return new CDragonBreathScript;
		break;
	case (UINT)SCRIPT_TYPE::DRAGONPARTICLESCRIPT:
		return new CDragonParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::ESKILLSLOTSCRIPT:
		return new CESkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::EXPLOSIONPARTICLESCRIPT:
		return new CExplosionParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::FIREPARTICLESCRIPT:
		return new CFireParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::FOREHANDATTACKSCRIPT:
		return new CForeHandAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULATTACKSCRIPT:
		return new CGhoulAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULATTACKTRACESCRIPT:
		return new CGhoulAttackTraceScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULDEADSCRIPT:
		return new CGhoulDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULFALLSCRIPT:
		return new CGhoulFallScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULHITBOXSCRIPT:
		return new CGhoulHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULHITSCRIPT:
		return new CGhoulHitScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULIDLESCRIPT:
		return new CGhoulIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULSCRIPT:
		return new CGhoulScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULSPAWNSCRIPT:
		return new CGhoulSpawnScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULTRACESCRIPT:
		return new CGhoulTraceScript;
		break;
	case (UINT)SCRIPT_TYPE::GHOULWAITSCRIPT:
		return new CGhoulWaitScript;
		break;
	case (UINT)SCRIPT_TYPE::HITEFFECTSCRIPT:
		return new CHitEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::HOMEFLOORSCRIPT:
		return new CHomeFloorScript;
		break;
	case (UINT)SCRIPT_TYPE::HOMEOVERLAYSCRIPT:
		return new CHomeOverlayScript;
		break;
	case (UINT)SCRIPT_TYPE::HOMEWALLSCRIPT:
		return new CHomeWallScript;
		break;
	case (UINT)SCRIPT_TYPE::ICECRYSTALARCANASCRIPT:
		return new CIceCrystalArcanaScript;
		break;
	case (UINT)SCRIPT_TYPE::LBTNSKILLSLOTSCRIPT:
		return new CLBtnSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEATTACKSCRIPT:
		return new CMageAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLAFTERIMAGESCRIPT:
		return new CMageBallAfterImageScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLATTACKSCRIPT:
		return new CMageBallAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLDEADSCRIPT:
		return new CMageBallDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLHITBOXSCRIPT:
		return new CMageBallHitboxScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLIDLESCRIPT:
		return new CMageBallIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLSCRIPT:
		return new CMageBallScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLSPAWNSCRIPT:
		return new CMageBallSpawnScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEBALLTRACESCRIPT:
		return new CMageBallTraceScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEDEADSCRIPT:
		return new CMageDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEHITBOXSCRIPT:
		return new CMageHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEHITSCRIPT:
		return new CMageHitScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEIDLESCRIPT:
		return new CMageIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGESCRIPT:
		return new CMageScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGESPAWNSCRIPT:
		return new CMageSpawnScript;
		break;
	case (UINT)SCRIPT_TYPE::MAGEWAITSCRIPT:
		return new CMageWaitScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINLIGHTSCRIPT:
		return new CMainLightScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINMENUSCRIPT:
		return new CMainMenuScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPPORTALSCRIPT:
		return new CMapPortalScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPSCRIPT:
		return new CMapScript;
		break;
	case (UINT)SCRIPT_TYPE::MERCHANTRUGSCRIPT:
		return new CMerchantRugScript;
		break;
	case (UINT)SCRIPT_TYPE::MERCHANTSCRIPT:
		return new CMerchantScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORARCANASCRIPT:
		return new CMeteorArcanaScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORDAMAGEZONESCRIPT:
		return new CMeteorDamageZoneScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORFLOORCRACKSCRIPT:
		return new CMeteorFloorCrackScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORRINGSCRIPT:
		return new CMeteorRingScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORSCRIPT:
		return new CMeteorScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORSMOKEPARTICLESCRIPT:
		return new CMeteorSmokeParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::METEORSPAWNCIRCLESCRIPT:
		return new CMeteorSpawnCircleScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSPAWNPOINTSCRIPT:
		return new CMonsterSpawnPointScript;
		break;
	case (UINT)SCRIPT_TYPE::MOUSEPOINTERSCRIPT:
		return new CMousePointerScript;
		break;
	case (UINT)SCRIPT_TYPE::OVERLAYSCRIPT:
		return new COverlayScript;
		break;
	case (UINT)SCRIPT_TYPE::PITSCRIPT:
		return new CPitScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERAFTERIMAGESCRIPT:
		return new CPlayerAfterImageScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERATTACKSCRIPT:
		return new CPlayerAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return new CPlayerCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERCOLORSCRIPT:
		return new CPlayerColorScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERDASHSCRIPT:
		return new CPlayerDashScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERDASHSTOPSCRIPT:
		return new CPlayerDashStopScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERDEADSCRIPT:
		return new CPlayerDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERDUSTSCRIPT:
		return new CPlayerDustScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERESCRIPT:
		return new CPlayerEScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERFACEUISCRIPT:
		return new CPlayerFaceUIScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERFALLSCRIPT:
		return new CPlayerFallScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return new CPlayerHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHITSCRIPT:
		return new CPlayerHitScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHPSCRIPT:
		return new CPlayerHPScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERHURTUISCRIPT:
		return new CPlayerHurtUIScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERIDLESCRIPT:
		return new CPlayerIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERLBTNSCRIPT:
		return new CPlayerLBtnScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMARKERSCRIPT:
		return new CPlayerMarkerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERMPSCRIPT:
		return new CPlayerMPScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERQBTNSCRIPT:
		return new CPlayerQBtnScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERRBTNSCRIPT:
		return new CPlayerRBtnScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERRSCRIPT:
		return new CPlayerRScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSKILLBARSCRIPT:
		return new CPlayerSkillBarScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSKILLSLOTSCRIPT:
		return new CPlayerSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSLIDESCRIPT:
		return new CPlayerSlideScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERWALKSCRIPT:
		return new CPlayerWalkScript;
		break;
	case (UINT)SCRIPT_TYPE::PORTALPARTICLESCRIPT:
		return new CPortalParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::PORTALSUMMONEFFECTSCRIPT:
		return new CPortalSummonEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::POTIONSCRIPT:
		return new CPotionScript;
		break;
	case (UINT)SCRIPT_TYPE::PRESSENTERSCRIPT:
		return new CPressEnterScript;
		break;
	case (UINT)SCRIPT_TYPE::QSKILLSLOTSCRIPT:
		return new CQSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::RAINPARTICLESCRIPT:
		return new CRainParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::RBTNSKILLSLOTSCRIPT:
		return new CRBtnSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::ROCKFISTSCRIPT:
		return new CRockFistScript;
		break;
	case (UINT)SCRIPT_TYPE::RSKILLSLOTSCRIPT:
		return new CRSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::SELECTEDSKILLSLOTSCRIPT:
		return new CSelectedSkillSlotScript;
		break;
	case (UINT)SCRIPT_TYPE::SKILLARROWSCRIPT:
		return new CSkillArrowScript;
		break;
	case (UINT)SCRIPT_TYPE::SKILLYELLOWARROWSCRIPT:
		return new CSkillYellowArrowScript;
		break;
	case (UINT)SCRIPT_TYPE::SNOWFLAKESCRIPT:
		return new CSnowFlakeScript;
		break;
	case (UINT)SCRIPT_TYPE::SNOWPARTICLESCRIPT:
		return new CSnowParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANATTACKSCRIPT:
		return new CSwordManAttackScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANATTACKTRACESCRIPT:
		return new CSwordManAttackTraceScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANDEADSCRIPT:
		return new CSwordManDeadScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANFALLSCRIPT:
		return new CSwordManFallScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANHITBOXSCRIPT:
		return new CSwordManHitBoxScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANHITSCRIPT:
		return new CSwordManHitScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANIDLESCRIPT:
		return new CSwordManIdleScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANSCRIPT:
		return new CSwordManScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANSPAWNSCRIPT:
		return new CSwordManSpawnScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANTRACESCRIPT:
		return new CSwordManTraceScript;
		break;
	case (UINT)SCRIPT_TYPE::SWORDMANWAITSCRIPT:
		return new CSwordManWaitScript;
		break;
	case (UINT)SCRIPT_TYPE::TERRASCRIPT:
		return new CTerraScript;
		break;
	case (UINT)SCRIPT_TYPE::TOWERSCRIPT:
		return new CTowerScript;
		break;
	case (UINT)SCRIPT_TYPE::WALLSCRIPT:
		return new CWallScript;
		break;
	case (UINT)SCRIPT_TYPE::WARDROBEARROWSCRIPT:
		return new CWardrobeArrowScript;
		break;
	case (UINT)SCRIPT_TYPE::WARDROBESCRIPT:
		return new CWardrobeScript;
		break;
	case (UINT)SCRIPT_TYPE::WARDROBEUISCRIPT:
		return new CWardrobeUIScript;
		break;
	case (UINT)SCRIPT_TYPE::WATERBALLARCANASCRIPT:
		return new CWaterBallArcanaScript;
		break;
	case (UINT)SCRIPT_TYPE::WATERBOMBSCRIPT:
		return new CWaterBombScript;
		break;
	case (UINT)SCRIPT_TYPE::WAVEWALLHORSCRIPT:
		return new CWaveWallHorScript;
		break;
	case (UINT)SCRIPT_TYPE::WAVEWALLVERSCRIPT:
		return new CWaveWallVerScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKHANDATTACKSCRIPT:
		return L"CBackHandAttackScript";
		break;

	case SCRIPT_TYPE::BGMSCRIPT:
		return L"CBGMScript";
		break;

	case SCRIPT_TYPE::BLACKHOLEPARTICLESCRIPT:
		return L"CBlackHoleParticleScript";
		break;

	case SCRIPT_TYPE::BOSSATTACKSCRIPT:
		return L"CBossAttackScript";
		break;

	case SCRIPT_TYPE::BOSSDEADSCRIPT:
		return L"CBossDeadScript";
		break;

	case SCRIPT_TYPE::BOSSDRILLSCRIPT:
		return L"CBossDrillScript";
		break;

	case SCRIPT_TYPE::BOSSENTERSCRIPT:
		return L"CBossEnterScript";
		break;

	case SCRIPT_TYPE::BOSSFIREFLYSCRIPT:
		return L"CBossFireflyScript";
		break;

	case SCRIPT_TYPE::BOSSFLEXSCRIPT:
		return L"CBossFlexScript";
		break;

	case SCRIPT_TYPE::BOSSFLOORSCRIPT:
		return L"CBossFloorScript";
		break;

	case SCRIPT_TYPE::BOSSHITBOXSCRIPT:
		return L"CBossHitBoxScript";
		break;

	case SCRIPT_TYPE::BOSSHITSCRIPT:
		return L"CBossHitScript";
		break;

	case SCRIPT_TYPE::BOSSHPSCRIPT:
		return L"CBossHPScript";
		break;

	case SCRIPT_TYPE::BOSSIDLESCRIPT:
		return L"CBossIdleScript";
		break;

	case SCRIPT_TYPE::BOSSLEAPATTACKHITBOXSCRIPT:
		return L"CBossLeapAttackHitBoxScript";
		break;

	case SCRIPT_TYPE::BOSSLEAPATTACKSCRIPT:
		return L"CBossLeapAttackScript";
		break;

	case SCRIPT_TYPE::BOSSPITSCRIPT:
		return L"CBossPitScript";
		break;

	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"CBossScript";
		break;

	case SCRIPT_TYPE::BOSSUISCRIPT:
		return L"CBossUIScript";
		break;

	case SCRIPT_TYPE::BOSSWALLSCRIPT:
		return L"CBossWallScript";
		break;

	case SCRIPT_TYPE::BOSSWAVESCRIPT:
		return L"CBossWaveScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CHAOSBOMBSCRIPT:
		return L"CChaosBombScript";
		break;

	case SCRIPT_TYPE::CHILDSCRIPT:
		return L"CChildScript";
		break;

	case SCRIPT_TYPE::DASHEFFECTSCRIPT:
		return L"CDashEffectScript";
		break;

	case SCRIPT_TYPE::DRAGONARCARCANASCRIPT:
		return L"CDragonArcArcanaScript";
		break;

	case SCRIPT_TYPE::DRAGONBREATHSCRIPT:
		return L"CDragonBreathScript";
		break;

	case SCRIPT_TYPE::DRAGONPARTICLESCRIPT:
		return L"CDragonParticleScript";
		break;

	case SCRIPT_TYPE::ESKILLSLOTSCRIPT:
		return L"CESkillSlotScript";
		break;

	case SCRIPT_TYPE::EXPLOSIONPARTICLESCRIPT:
		return L"CExplosionParticleScript";
		break;

	case SCRIPT_TYPE::FIREPARTICLESCRIPT:
		return L"CFireParticleScript";
		break;

	case SCRIPT_TYPE::FOREHANDATTACKSCRIPT:
		return L"CForeHandAttackScript";
		break;

	case SCRIPT_TYPE::GHOULATTACKSCRIPT:
		return L"CGhoulAttackScript";
		break;

	case SCRIPT_TYPE::GHOULATTACKTRACESCRIPT:
		return L"CGhoulAttackTraceScript";
		break;

	case SCRIPT_TYPE::GHOULDEADSCRIPT:
		return L"CGhoulDeadScript";
		break;

	case SCRIPT_TYPE::GHOULFALLSCRIPT:
		return L"CGhoulFallScript";
		break;

	case SCRIPT_TYPE::GHOULHITBOXSCRIPT:
		return L"CGhoulHitBoxScript";
		break;

	case SCRIPT_TYPE::GHOULHITSCRIPT:
		return L"CGhoulHitScript";
		break;

	case SCRIPT_TYPE::GHOULIDLESCRIPT:
		return L"CGhoulIdleScript";
		break;

	case SCRIPT_TYPE::GHOULSCRIPT:
		return L"CGhoulScript";
		break;

	case SCRIPT_TYPE::GHOULSPAWNSCRIPT:
		return L"CGhoulSpawnScript";
		break;

	case SCRIPT_TYPE::GHOULTRACESCRIPT:
		return L"CGhoulTraceScript";
		break;

	case SCRIPT_TYPE::GHOULWAITSCRIPT:
		return L"CGhoulWaitScript";
		break;

	case SCRIPT_TYPE::HITEFFECTSCRIPT:
		return L"CHitEffectScript";
		break;

	case SCRIPT_TYPE::HOMEFLOORSCRIPT:
		return L"CHomeFloorScript";
		break;

	case SCRIPT_TYPE::HOMEOVERLAYSCRIPT:
		return L"CHomeOverlayScript";
		break;

	case SCRIPT_TYPE::HOMEWALLSCRIPT:
		return L"CHomeWallScript";
		break;

	case SCRIPT_TYPE::ICECRYSTALARCANASCRIPT:
		return L"CIceCrystalArcanaScript";
		break;

	case SCRIPT_TYPE::LBTNSKILLSLOTSCRIPT:
		return L"CLBtnSkillSlotScript";
		break;

	case SCRIPT_TYPE::MAGEATTACKSCRIPT:
		return L"CMageAttackScript";
		break;

	case SCRIPT_TYPE::MAGEBALLAFTERIMAGESCRIPT:
		return L"CMageBallAfterImageScript";
		break;

	case SCRIPT_TYPE::MAGEBALLATTACKSCRIPT:
		return L"CMageBallAttackScript";
		break;

	case SCRIPT_TYPE::MAGEBALLDEADSCRIPT:
		return L"CMageBallDeadScript";
		break;

	case SCRIPT_TYPE::MAGEBALLHITBOXSCRIPT:
		return L"CMageBallHitboxScript";
		break;

	case SCRIPT_TYPE::MAGEBALLIDLESCRIPT:
		return L"CMageBallIdleScript";
		break;

	case SCRIPT_TYPE::MAGEBALLSCRIPT:
		return L"CMageBallScript";
		break;

	case SCRIPT_TYPE::MAGEBALLSPAWNSCRIPT:
		return L"CMageBallSpawnScript";
		break;

	case SCRIPT_TYPE::MAGEBALLTRACESCRIPT:
		return L"CMageBallTraceScript";
		break;

	case SCRIPT_TYPE::MAGEDEADSCRIPT:
		return L"CMageDeadScript";
		break;

	case SCRIPT_TYPE::MAGEHITBOXSCRIPT:
		return L"CMageHitBoxScript";
		break;

	case SCRIPT_TYPE::MAGEHITSCRIPT:
		return L"CMageHitScript";
		break;

	case SCRIPT_TYPE::MAGEIDLESCRIPT:
		return L"CMageIdleScript";
		break;

	case SCRIPT_TYPE::MAGESCRIPT:
		return L"CMageScript";
		break;

	case SCRIPT_TYPE::MAGESPAWNSCRIPT:
		return L"CMageSpawnScript";
		break;

	case SCRIPT_TYPE::MAGEWAITSCRIPT:
		return L"CMageWaitScript";
		break;

	case SCRIPT_TYPE::MAINLIGHTSCRIPT:
		return L"CMainLightScript";
		break;

	case SCRIPT_TYPE::MAINMENUSCRIPT:
		return L"CMainMenuScript";
		break;

	case SCRIPT_TYPE::MAPPORTALSCRIPT:
		return L"CMapPortalScript";
		break;

	case SCRIPT_TYPE::MAPSCRIPT:
		return L"CMapScript";
		break;

	case SCRIPT_TYPE::MERCHANTRUGSCRIPT:
		return L"CMerchantRugScript";
		break;

	case SCRIPT_TYPE::MERCHANTSCRIPT:
		return L"CMerchantScript";
		break;

	case SCRIPT_TYPE::METEORARCANASCRIPT:
		return L"CMeteorArcanaScript";
		break;

	case SCRIPT_TYPE::METEORDAMAGEZONESCRIPT:
		return L"CMeteorDamageZoneScript";
		break;

	case SCRIPT_TYPE::METEORFLOORCRACKSCRIPT:
		return L"CMeteorFloorCrackScript";
		break;

	case SCRIPT_TYPE::METEORRINGSCRIPT:
		return L"CMeteorRingScript";
		break;

	case SCRIPT_TYPE::METEORSCRIPT:
		return L"CMeteorScript";
		break;

	case SCRIPT_TYPE::METEORSMOKEPARTICLESCRIPT:
		return L"CMeteorSmokeParticleScript";
		break;

	case SCRIPT_TYPE::METEORSPAWNCIRCLESCRIPT:
		return L"CMeteorSpawnCircleScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::MONSTERSPAWNPOINTSCRIPT:
		return L"CMonsterSpawnPointScript";
		break;

	case SCRIPT_TYPE::MOUSEPOINTERSCRIPT:
		return L"CMousePointerScript";
		break;

	case SCRIPT_TYPE::OVERLAYSCRIPT:
		return L"COverlayScript";
		break;

	case SCRIPT_TYPE::PITSCRIPT:
		return L"CPitScript";
		break;

	case SCRIPT_TYPE::PLAYERAFTERIMAGESCRIPT:
		return L"CPlayerAfterImageScript";
		break;

	case SCRIPT_TYPE::PLAYERATTACKSCRIPT:
		return L"CPlayerAttackScript";
		break;

	case SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return L"CPlayerCameraScript";
		break;

	case SCRIPT_TYPE::PLAYERCOLORSCRIPT:
		return L"CPlayerColorScript";
		break;

	case SCRIPT_TYPE::PLAYERDASHSCRIPT:
		return L"CPlayerDashScript";
		break;

	case SCRIPT_TYPE::PLAYERDASHSTOPSCRIPT:
		return L"CPlayerDashStopScript";
		break;

	case SCRIPT_TYPE::PLAYERDEADSCRIPT:
		return L"CPlayerDeadScript";
		break;

	case SCRIPT_TYPE::PLAYERDUSTSCRIPT:
		return L"CPlayerDustScript";
		break;

	case SCRIPT_TYPE::PLAYERESCRIPT:
		return L"CPlayerEScript";
		break;

	case SCRIPT_TYPE::PLAYERFACEUISCRIPT:
		return L"CPlayerFaceUIScript";
		break;

	case SCRIPT_TYPE::PLAYERFALLSCRIPT:
		return L"CPlayerFallScript";
		break;

	case SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return L"CPlayerHitBoxScript";
		break;

	case SCRIPT_TYPE::PLAYERHITSCRIPT:
		return L"CPlayerHitScript";
		break;

	case SCRIPT_TYPE::PLAYERHPSCRIPT:
		return L"CPlayerHPScript";
		break;

	case SCRIPT_TYPE::PLAYERHURTUISCRIPT:
		return L"CPlayerHurtUIScript";
		break;

	case SCRIPT_TYPE::PLAYERIDLESCRIPT:
		return L"CPlayerIdleScript";
		break;

	case SCRIPT_TYPE::PLAYERLBTNSCRIPT:
		return L"CPlayerLBtnScript";
		break;

	case SCRIPT_TYPE::PLAYERMARKERSCRIPT:
		return L"CPlayerMarkerScript";
		break;

	case SCRIPT_TYPE::PLAYERMPSCRIPT:
		return L"CPlayerMPScript";
		break;

	case SCRIPT_TYPE::PLAYERQBTNSCRIPT:
		return L"CPlayerQBtnScript";
		break;

	case SCRIPT_TYPE::PLAYERRBTNSCRIPT:
		return L"CPlayerRBtnScript";
		break;

	case SCRIPT_TYPE::PLAYERRSCRIPT:
		return L"CPlayerRScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PLAYERSKILLBARSCRIPT:
		return L"CPlayerSkillBarScript";
		break;

	case SCRIPT_TYPE::PLAYERSKILLSLOTSCRIPT:
		return L"CPlayerSkillSlotScript";
		break;

	case SCRIPT_TYPE::PLAYERSLIDESCRIPT:
		return L"CPlayerSlideScript";
		break;

	case SCRIPT_TYPE::PLAYERWALKSCRIPT:
		return L"CPlayerWalkScript";
		break;

	case SCRIPT_TYPE::PORTALPARTICLESCRIPT:
		return L"CPortalParticleScript";
		break;

	case SCRIPT_TYPE::PORTALSUMMONEFFECTSCRIPT:
		return L"CPortalSummonEffectScript";
		break;

	case SCRIPT_TYPE::POTIONSCRIPT:
		return L"CPotionScript";
		break;

	case SCRIPT_TYPE::PRESSENTERSCRIPT:
		return L"CPressEnterScript";
		break;

	case SCRIPT_TYPE::QSKILLSLOTSCRIPT:
		return L"CQSkillSlotScript";
		break;

	case SCRIPT_TYPE::RAINPARTICLESCRIPT:
		return L"CRainParticleScript";
		break;

	case SCRIPT_TYPE::RBTNSKILLSLOTSCRIPT:
		return L"CRBtnSkillSlotScript";
		break;

	case SCRIPT_TYPE::ROCKFISTSCRIPT:
		return L"CRockFistScript";
		break;

	case SCRIPT_TYPE::RSKILLSLOTSCRIPT:
		return L"CRSkillSlotScript";
		break;

	case SCRIPT_TYPE::SELECTEDSKILLSLOTSCRIPT:
		return L"CSelectedSkillSlotScript";
		break;

	case SCRIPT_TYPE::SKILLARROWSCRIPT:
		return L"CSkillArrowScript";
		break;

	case SCRIPT_TYPE::SKILLYELLOWARROWSCRIPT:
		return L"CSkillYellowArrowScript";
		break;

	case SCRIPT_TYPE::SNOWFLAKESCRIPT:
		return L"CSnowFlakeScript";
		break;

	case SCRIPT_TYPE::SNOWPARTICLESCRIPT:
		return L"CSnowParticleScript";
		break;

	case SCRIPT_TYPE::SWORDMANATTACKSCRIPT:
		return L"CSwordManAttackScript";
		break;

	case SCRIPT_TYPE::SWORDMANATTACKTRACESCRIPT:
		return L"CSwordManAttackTraceScript";
		break;

	case SCRIPT_TYPE::SWORDMANDEADSCRIPT:
		return L"CSwordManDeadScript";
		break;

	case SCRIPT_TYPE::SWORDMANFALLSCRIPT:
		return L"CSwordManFallScript";
		break;

	case SCRIPT_TYPE::SWORDMANHITBOXSCRIPT:
		return L"CSwordManHitBoxScript";
		break;

	case SCRIPT_TYPE::SWORDMANHITSCRIPT:
		return L"CSwordManHitScript";
		break;

	case SCRIPT_TYPE::SWORDMANIDLESCRIPT:
		return L"CSwordManIdleScript";
		break;

	case SCRIPT_TYPE::SWORDMANSCRIPT:
		return L"CSwordManScript";
		break;

	case SCRIPT_TYPE::SWORDMANSPAWNSCRIPT:
		return L"CSwordManSpawnScript";
		break;

	case SCRIPT_TYPE::SWORDMANTRACESCRIPT:
		return L"CSwordManTraceScript";
		break;

	case SCRIPT_TYPE::SWORDMANWAITSCRIPT:
		return L"CSwordManWaitScript";
		break;

	case SCRIPT_TYPE::TERRASCRIPT:
		return L"CTerraScript";
		break;

	case SCRIPT_TYPE::TOWERSCRIPT:
		return L"CTowerScript";
		break;

	case SCRIPT_TYPE::WALLSCRIPT:
		return L"CWallScript";
		break;

	case SCRIPT_TYPE::WARDROBEARROWSCRIPT:
		return L"CWardrobeArrowScript";
		break;

	case SCRIPT_TYPE::WARDROBESCRIPT:
		return L"CWardrobeScript";
		break;

	case SCRIPT_TYPE::WARDROBEUISCRIPT:
		return L"CWardrobeUIScript";
		break;

	case SCRIPT_TYPE::WATERBALLARCANASCRIPT:
		return L"CWaterBallArcanaScript";
		break;

	case SCRIPT_TYPE::WATERBOMBSCRIPT:
		return L"CWaterBombScript";
		break;

	case SCRIPT_TYPE::WAVEWALLHORSCRIPT:
		return L"CWaveWallHorScript";
		break;

	case SCRIPT_TYPE::WAVEWALLVERSCRIPT:
		return L"CWaveWallVerScript";
		break;

	}
	return nullptr;
}