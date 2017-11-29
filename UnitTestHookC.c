
#include "stdafx.h"

//List of API support

#define EXT_IUTIL
#define EXT_ICINIFILE
#define EXT_ICOMMAND

//Future API support
//#define EXT_HKEXTERNAL

#include "..\Add-on API\Add-on API.h"
#pragma comment(lib, "../Add-on API/Add-on API.lib")


addon_info EXTPluginInfo = { L"Unit Test Hook C", L"1.0.0.0",
                            L"DZS|All-In-One, founder of DZS",
                            L"Used for verifying each hooks are working right in C language under C99 standard.",
                            L"UnitTestHook",
                            L"unit_test_hook",
                            L"",
                            L"",
                            L"",
                            L"" };

unsigned int EAOhashID = 0;

ICIniFile* pICIniFile = NULL;
ICommand* pICommand = NULL;

wchar_t iniFileStr[] = L"HookTestC.ini";
IUtil* pIUtil = NULL;

const wchar_t eao_unittesthook_saveStr[] = L"eao_unittesthook_save_c";

CMD_RETURN eao_unittesthook_save(PlayerInfo plI, ArgContainer* arg, MSG_PROTOCOL protocolMsg, unsigned int idTimer, bool* showChat) {
    if (pICIniFile) {
        CALL_MEMBER_FN(pICIniFile, m_save);
    }
    return CMD_SUCCESS;
}

dllAPI EAO_RETURN WINAPIC EXTOnEAOLoad(unsigned int uniqueHash) {
    EAOhashID = uniqueHash;
    /*pIPlayer = getIPlayer(uniqueHash);
    if (!pIPlayer)
        goto initFail;*/
    pICIniFile = getICIniFile(uniqueHash);
    if (!pICIniFile)
        goto initFail;
    if (CALL_MEMBER_FN(pICIniFile, m_open_file, iniFileStr)) {
        if (!CALL_MEMBER_FN(pICIniFile, m_delete_file, iniFileStr)) {
            goto initFail;
        }
        if (CALL_MEMBER_FN(pICIniFile, m_open_file, iniFileStr)) {
            goto initFail;
        }
    }
    if (!CALL_MEMBER_FN(pICIniFile, m_create_file, iniFileStr)) {
        goto initFail;
    }
    if (!CALL_MEMBER_FN(pICIniFile, m_open_file, iniFileStr)) {
        goto initFail;
    }
    pICommand = getICommand(uniqueHash);
    if (!pICommand) {
        goto initFail;
    }
    if (!pICommand->m_add(uniqueHash, eao_unittesthook_saveStr, eao_unittesthook_save, EXTPluginInfo.sectors.sect_name1, 1, 1, 0, modeAll)) {
        goto initFail;
    }
    pIUtil = getIUtil(uniqueHash);
    if (!pIUtil) {
        goto initFail;
    }
    return EAO_CONTINUE;
initFail:
    if (pICIniFile) {
        CALL_MEMBER_FN(pICIniFile, m_release);
    }
    if (pICommand) {
        pICommand->m_delete(uniqueHash, eao_unittesthook_save, eao_unittesthook_saveStr);
    }
    return EAO_FAIL;
}
dllAPI void WINAPIC EXTOnEAOUnload() {
    if (pICIniFile) {
        CALL_MEMBER_FN(pICIniFile, m_save);
        CALL_MEMBER_FN(pICIniFile, m_close);
        CALL_MEMBER_FN(pICIniFile, m_release);
    }
    if (pICommand) {
        pICommand->m_delete(EAOhashID, eao_unittesthook_save, eao_unittesthook_saveStr);
    }
}

const wchar_t HookNames[][40] = { L"EXTOnPlayerJoin"
                            , L"EXTOnPlayerQuit"
                            , L"EXTOnPlayerDeath"
                            , L"EXTOnPlayerChangeTeamAttempt"
                            , L"EXTOnPlayerJoinDefault"
                            , L"EXTOnNewGame"
                            , L"EXTOnEndGame"
                            , L"EXTOnObjectInteraction"
                            , L"EXTOnWeaponAssignmentDefault"
                            , L"EXTOnWeaponAssignmentCustom"
                            , L"EXTOnServerIdle"
                            , L"EXTOnPlayerScoreCTF"
                            , L"EXTOnWeaponDropAttemptMustBeReadied"
                            , L"EXTOnPlayerSpawn"
                            , L"EXTOnPlayerVehicleEntry"
                            , L"EXTOnPlayerVehicleEject"
                            , L"EXTOnPlayerSpawnColor"
                            , L"EXTOnPlayerValidateConnect"
                            , L"EXTOnWeaponReload"
                            , L"EXTOnObjectCreate"
                            , L"EXTOnKillMultiplier"
                            , L"EXTOnVehicleRespawnProcess"
                            , L"EXTOnObjectDeleteAttempt"
                            , L"EXTOnObjectDamageLookupProcess"
                            , L"EXTOnObjectDamageApplyProcess"
                            // Featured in 0.5.1 and newer
                            , L"EXTOnMapLoad"
                            , L"EXTOnAIVehicleEntry"
                            , L"EXTOnWeaponDropCurrent"
                            , L"EXTOnServerStatus"
                            // Featured in 0.5.2.3 and newer
                            , L"EXTOnPlayerUpdate"
                            , L"EXTOnMapReset"
                            // Featured in 0.5.3.0 and newer
                            , L"EXTOnObjectCreateAttempt"
                            // Featured in 0.5.3.2 and newer
                            , L"EXTOnGameSpyValidationCheck"
                            // Featured in 0.5.3.3 and newer
                            , L"EXTOnWeaponExchangeAttempt"
                            // Featured in 0.5.3.4 and newer
                            , L"EXTOnObjectDelete" };

typedef struct checkList {
    int EXTOnPlayerJoin;
    int EXTOnPlayerQuit;
    int EXTOnPlayerDeath;
    int EXTOnPlayerChangeTeamAttempt;
    int EXTOnPlayerJoinDefault;
    int EXTOnNewGame;
    int EXTOnEndGame;
    int EXTOnObjectInteraction;
    int EXTOnWeaponAssignmentDefault;
    int EXTOnWeaponAssignmentCustom;
    int EXTOnServerIdle;
    int EXTOnPlayerScoreCTF;
    int EXTOnWeaponDropAttemptMustBeReadied;
    int EXTOnPlayerSpawn;
    int EXTOnPlayerVehicleEntry;
    int EXTOnPlayerVehicleEject;
    int EXTOnPlayerSpawnColor;
    int EXTOnPlayerValidateConnect;
    int EXTOnWeaponReload;
    int EXTOnObjectCreate;
    int EXTOnKillMultiplier;
    int EXTOnVehicleRespawnProcess;
    int EXTOnObjectDeleteAttempt;
    int EXTOnObjectDamageLookupProcess;
    int EXTOnObjectDamageApplyProcess;
    int EXTOnMapLoad;
    int EXTOnAIVehicleEntry;
    int EXTOnWeaponDropCurrent;
    int EXTOnServerStatus;
    int EXTOnPlayerUpdate;
    int EXTOnMapReset;
    int EXTOnObjectCreateAttempt;
    int EXTOnGameSpyValidationCheck;
    int EXTOnWeaponExchangeAttempt;
    int EXTOnObjectDelete;
} checkList;
checkList checkHooks = { 0 };

#define MAX_HOOK_COUNTER 5
const wchar_t nullStr[] = L"NULL";

// List of all available hooks

dllAPI void WINAPIC EXTOnPlayerJoin(PlayerInfo plI) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerJoin < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerJoin++;
        _itow_s(checkHooks.EXTOnPlayerJoin, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTshort(&vars[1], plI.plEx->adminLvl);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, Admin: {1:hd}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[0], index, output);
    }
}

dllAPI void WINAPIC EXTOnPlayerQuit(PlayerInfo plI) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerQuit < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerQuit++;
        _itow_s(checkHooks.EXTOnPlayerQuit, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTshort(&vars[1], plI.plEx->adminLvl);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, Admin: {1:hd}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[1], index, output);
    }
}

dllAPI void WINAPIC EXTOnPlayerDeath(PlayerInfo killer, PlayerInfo victim, int mode, bool* showMessage) {
    VARIANT vars[4];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerDeath < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerDeath++;
        _itow_s(checkHooks.EXTOnPlayerDeath, index, 4, 10);
        VARIANTwstr(&vars[0], killer.plS ? killer.plS->Name : nullStr);
        VARIANTwstr(&vars[1], victim.plS ? victim.plS->Name : nullStr);
        VARIANTint(&vars[2], mode);
        VARIANTbool(&vars[3], *showMessage);
        pIUtil->m_formatVariantW(output, 128, L"Killer: {0:s}, Victim: {1:s}, Mode: {2:d}, showMessage: {3:d}", 4, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[2], index, output);
    }
}

dllAPI bool WINAPIC EXTOnPlayerChangeTeamAttempt(PlayerInfo plI, e_color_team_index team, bool forceChange) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerChangeTeamAttempt < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerChangeTeamAttempt++;
        _itow_s(checkHooks.EXTOnPlayerChangeTeamAttempt, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], team);
        VARIANTbool(&vars[2], forceChange);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, Team: {1:d}, forceChange: {2:d}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[3], index, output);
    }
    return 1; //If set to false, it will prevent change team. Unless forceChange is true, this value is ignored.
}

dllAPI e_color_team_index WINAPIC EXTOnPlayerJoinDefault(s_machine_slot* mS, e_color_team_index cur_team) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerJoinDefault < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerJoinDefault++;
        _itow_s(checkHooks.EXTOnPlayerJoinDefault, index, 4, 10);
        VARIANTshort(&vars[0], mS->machineIndex);
        VARIANTstr(&vars[1], mS->SessionKey);
        VARIANTint(&vars[2], mS->isAvailable);
        pIUtil->m_formatVariantW(output, 128, L"mIndex: {0:hd}, SessionKey: {1:s}, isAvailable: {2:d}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[4], index, output);
    }
    return COLOR_TEAM_NONE; //If set to 0 will force set to red team. Or set to 1 will force set to blue team. -1 is default team.
}

__declspec(deprecated("Do not use EXTOnNewGame hook, use EXTOnMapLoad hook instead."))
dllAPI void WINAPIC EXTOnNewGame(wchar_t* map) {
    VARIANT vars[1];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnNewGame < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnNewGame++;
        _itow_s(checkHooks.EXTOnNewGame, index, 4, 10);
        VARIANTwstr(&vars[0], map);
        pIUtil->m_formatVariantW(output, 128, L"Map: {0:s}", 1, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[5], index, output);
    }
}

dllAPI void WINAPIC EXTOnEndGame(int mode) {
    VARIANT vars[1];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnEndGame < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnEndGame++;
        _itow_s(checkHooks.EXTOnEndGame, index, 4, 10);
        VARIANTint(&vars[0], mode);
        pIUtil->m_formatVariantW(output, 128, L"Mode: {0:d}", 1, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[6], index, output);
    }

}

dllAPI bool WINAPIC EXTOnObjectInteraction(PlayerInfo plI, s_ident obj_id, s_object* objectStruct, hTagHeader* hTag) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectInteraction < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectInteraction++;
        _itow_s(checkHooks.EXTOnObjectInteraction, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], obj_id.Tag);
        VARIANTint(&vars[2], objectStruct->ModelTag.Tag);
        VARIANTshort(&vars[3], objectStruct->GameObject);
        VARIANTstr(&vars[4], hTag->tag_name);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, ObjectID: {1:08X}, ModelTag: {2:08X}, GameObject: {3:hd}, tagName: {4:s}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[7], index, output);
    }
    return 1; //If set to false, it will deny interaction to an object.
}

dllAPI void WINAPIC EXTOnWeaponAssignmentDefault(PlayerInfo plI, s_ident owner_obj_id, s_tag_reference* cur_weap_id, unsigned int order, s_ident* new_weap_id) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponAssignmentDefault < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponAssignmentDefault++;
        _itow_s(checkHooks.EXTOnWeaponAssignmentDefault, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], owner_obj_id.Tag);
        VARIANTstr(&vars[2], cur_weap_id->name);
        VARIANTint(&vars[3], order);
        VARIANTint(&vars[4], new_weap_id->Tag);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, OwnerObjectID: {1:08X}, Weapon Name: {2:s}, Order: {3:d}, newWeapID: {4:08X}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[8], index, output);
    }
}

dllAPI void WINAPIC EXTOnWeaponAssignmentCustom(PlayerInfo plI, s_ident owner_obj_id, s_ident cur_weap_id, unsigned int order, s_ident* new_weap_id) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponAssignmentCustom < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponAssignmentCustom++;
        _itow_s(checkHooks.EXTOnWeaponAssignmentCustom, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], owner_obj_id.Tag);
        VARIANTint(&vars[2], cur_weap_id.Tag);
        VARIANTint(&vars[3], order);
        VARIANTint(&vars[4], new_weap_id->Tag);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, OwnerObjectID: {1:08X}, curWeaponID: {2:08X}, Order: {3:d}, newWeapID: {4:08X}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[9], index, output);
    }
}

dllAPI void WINAPIC EXTOnServerIdle() {
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnServerIdle < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnServerIdle++;
        _itow_s(checkHooks.EXTOnServerIdle, index, 4, 10);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[10], index, L"Idle");
    }
}

dllAPI bool WINAPIC EXTOnPlayerScoreCTF(PlayerInfo plI, s_ident cur_weap_id, unsigned int team, bool isGameObject) {
    VARIANT vars[4];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerScoreCTF < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerScoreCTF++;
        _itow_s(checkHooks.EXTOnPlayerScoreCTF, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], cur_weap_id.Tag);
        VARIANTint(&vars[2], team);
        VARIANTint(&vars[3], isGameObject);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, curWeaponID: {1:08X}, Team: {2:d}, isGameObject: {3:d}", 4, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[11], index, output);
    }
    return 1; //If set to false, it will prevent player to score a flag.
}

dllAPI bool WINAPIC EXTOnWeaponDropAttemptMustBeReadied(PlayerInfo plI, s_ident owner_obj_id, s_biped* pl_Biped) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponDropAttemptMustBeReadied < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponDropAttemptMustBeReadied++;
        _itow_s(checkHooks.EXTOnWeaponDropAttemptMustBeReadied, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], owner_obj_id.Tag);
        VARIANTint(&vars[2], pl_Biped->sObject.ModelTag.Tag);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, ownerObjID: {1:08X}, pl_Biped: {2:08X}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[12], index, output);
    }
    return 1; //If set to false, it will prevent player to drop an object.

}

dllAPI void WINAPIC EXTOnPlayerSpawn(PlayerInfo plI, s_ident obj_id, s_biped* pl_Biped) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerSpawn < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerSpawn++;
        _itow_s(checkHooks.EXTOnPlayerSpawn, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTint(&vars[1], obj_id.Tag);
        VARIANTuint(&vars[2], (unsigned int)pl_Biped);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, obj_id: {1:08X}, pl_Biped: {2:08X}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[13], index, output);
    }
}

dllAPI bool WINAPIC EXTOnPlayerVehicleEntry(PlayerInfo plI, bool forceEntry) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerVehicleEntry < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerVehicleEntry++;
        _itow_s(checkHooks.EXTOnPlayerVehicleEntry, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTbool(&vars[1], forceEntry);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, forceEntry: {1:d}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[14], index, output);
    }
    return 1; //If set to false, it will prevent player enter a vehicle.
}

dllAPI bool WINAPIC EXTOnPlayerVehicleEject(PlayerInfo plI, bool forceEject) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerVehicleEject < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerVehicleEject++;
        _itow_s(checkHooks.EXTOnPlayerVehicleEject, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTbool(&vars[1], forceEject);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, forceEject: {1:d}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[15], index, output);
    }
    return 1; //If set to false, it will prevent player leave a vehicle.
}

dllAPI bool WINAPIC EXTOnPlayerSpawnColor(PlayerInfo plI, bool isTeamPlay) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerSpawnColor < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerSpawnColor++;
        _itow_s(checkHooks.EXTOnPlayerSpawnColor, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        VARIANTshort(&vars[1], plI.plR->ColorIndex);
        VARIANTbool(&vars[2], isTeamPlay);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, Color Index: {1:hd}, isTeamPlay: {2:d}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[16], index, output);
    }
    return 1; //If set to false, it will use custom color instead of team color.
}

dllAPI PLAYER_VALIDATE WINAPIC EXTOnPlayerValidateConnect(PlayerExtended plEx, s_machine_slot mS, s_ban_check banCheckPlayer, bool isBanned, toggle svPass, PLAYER_VALIDATE isForceReject) {
    VARIANT vars[6];
    wchar_t output[INIFILEVALUEMAX];
    char banCheckPlayerHashA[33] = { 0 };
    static wchar_t index[8] = { 0 };
    int indexLength;
    if (checkHooks.EXTOnPlayerValidateConnect < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerValidateConnect++;
        _itow_s(checkHooks.EXTOnPlayerValidateConnect, index, 4, 10);
        indexLength = wcslen(index);
        pIUtil->m_strcatA(banCheckPlayerHashA, 32, banCheckPlayer.cdKeyHash);
        VARIANTwstr(&vars[0], plEx.CDHashW);
        VARIANTstr(&vars[1], banCheckPlayerHashA);
        VARIANTwstr(&vars[2], banCheckPlayer.requestPlayerName);
        VARIANTbool(&vars[3], isBanned);
        VARIANTchar(&vars[4], svPass);
        VARIANTint(&vars[5], isForceReject);
        index[indexLength] = '.';
        indexLength++;
        index[indexLength] = '1';
        index[indexLength + 1] = 0;
        pIUtil->m_formatVariantW(output, 128, L"plEx.CDHashW: {0:s}, banCheckPlayer.cdKeyHash: {1:s}", 6, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[17], index, output);
        index[indexLength] = '2';
        pIUtil->m_formatVariantW(output, 128, L"Request Name: {2:s}, isBanned: {3:d}, svPass: {4:hhd} isForceReject: {5:d}", 6, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[17], index, output);
    }
    return PLAYER_VALIDATE_DEFAULT; //Look in PLAYER_VALIDATE enum for available options to return.
}

dllAPI bool WINAPIC EXTOnWeaponReload(s_object* obj_Struct, bool allowReload) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponReload < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponReload++;
        _itow_s(checkHooks.EXTOnWeaponReload, index, 4, 10);
        VARIANTint(&vars[0], obj_Struct->ModelTag.Tag);
        VARIANTint(&vars[1], allowReload);
        pIUtil->m_formatVariantW(output, 128, L"Object Model Tag: {0:08X}, allowReload: {1:d}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[18], index, output);
    }
    return 1; //If set to false, weapon will not reload. Unless allowReload is false, then this value is ignored.
}

// Enabled in 0.5.3.4
dllAPI void WINAPIC EXTOnObjectCreate(s_ident obj_id, s_object* obj_Struct, hTagHeader* header) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectCreate < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectCreate++;
        _itow_s(checkHooks.EXTOnObjectCreate, index, 4, 10);
        VARIANTint(&vars[0], obj_Struct->ModelTag.Tag);
        VARIANTstr(&vars[1], header->tag_name);
        pIUtil->m_formatVariantW(output, 128, L"Object Model Tag: {0:08X}, tag_name: {1:s}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[19], index, output);
    }
}

dllAPI void WINAPIC EXTOnKillMultiplier(PlayerInfo killer, unsigned int multiplier) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnKillMultiplier < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnKillMultiplier++;
        _itow_s(checkHooks.EXTOnKillMultiplier, index, 4, 10);
        VARIANTwstr(&vars[0], killer.plS->Name);
        VARIANTint(&vars[1], multiplier);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, Multiplier: {1:d}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[20], index, output);
    }
}

dllAPI VEHICLE_RESPAWN WINAPIC EXTOnVehicleRespawnProcess(s_ident obj_id, s_object* cur_object, objManaged* managedObj) {
    VARIANT vars[4];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnVehicleRespawnProcess < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnVehicleRespawnProcess++;
        _itow_s(checkHooks.EXTOnVehicleRespawnProcess, index, 4, 10);
        VARIANTint(&vars[0], cur_object->ModelTag.Tag);
        VARIANTfloat(&vars[1], managedObj->world.x);
        VARIANTfloat(&vars[2], managedObj->world.y);
        VARIANTfloat(&vars[3], managedObj->world.z);
        pIUtil->m_formatVariantW(output, 128, L"ModelTag: {0:08X}, World X: {1:f}, Y: {2:f}, Z: {3:f}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[21], index, output);
    }
    return VEHICLE_RESPAWN_DEFAULT; //Look in VEHICLE_RESPAWN enum for available options to return.
}

// Enabled in 0.5.3.4
dllAPI OBJECT_ATTEMPT WINAPIC EXTOnObjectDeleteAttempt(s_ident obj_id, s_object* cur_object, int curTicks) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectDeleteAttempt < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectDeleteAttempt++;
        _itow_s(checkHooks.EXTOnObjectDeleteAttempt, index, 4, 10);
        VARIANTint(&vars[0], cur_object->ModelTag.Tag);
        VARIANTint(&vars[1], curTicks);
        VARIANTbool(&vars[2], isManaged);
        pIUtil->m_formatVariantW(output, 128, L"ModelTag: {0:08X}, Current Ticks: {1:d}, isManaged: {2:d}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[22], index, output);
    }
    return OBJECT_ATTEMPT_DEFAULT; //Look in OBJECT_ATTEMPT enum for available options to return.
}

dllAPI bool WINAPIC EXTOnObjectDamageLookupProcess(objDamageInfo* damageInfo, s_ident* obj_recv, bool* allowDamage, bool isManaged) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectDamageLookupProcess < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectDamageLookupProcess++;
        _itow_s(checkHooks.EXTOnObjectDamageLookupProcess, index, 4, 10);
        VARIANTint(&vars[0], damageInfo->causer.Tag);
        VARIANTint(&vars[1], damageInfo->player_causer.Tag);
        VARIANTint(&vars[2], obj_recv ? obj_recv->Tag : 0);
        VARIANTbool(&vars[3], *allowDamage);
        VARIANTbool(&vars[4], isManaged);
        pIUtil->m_formatVariantW(output, 128, L"Causer: {0:08X}, PlayerCauser: {1:08X}, obj_recv: {2:08X}, allowDamage: {3:d}, isManaged: {4:d}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[23], index, output);
    }
    return 1; //If set to false, it is managed by you. True for default.

}

dllAPI bool WINAPIC EXTOnObjectDamageApplyProcess(const objDamageInfo* damageInfo, s_ident* obj_recv, objHitInfo* hitInfo, bool isBacktap, bool* allowDamage, bool isManaged) {
    VARIANT vars[6];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectDamageApplyProcess < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectDamageApplyProcess++;
        _itow_s(checkHooks.EXTOnObjectDamageApplyProcess, index, 4, 10);
        VARIANTint(&vars[0], damageInfo->causer.Tag);
        VARIANTint(&vars[1], damageInfo->player_causer.Tag);
        VARIANTint(&vars[2], obj_recv ? obj_recv->Tag : 0);
        VARIANTbool(&vars[3], isBacktap);
        VARIANTbool(&vars[4], *allowDamage);
        VARIANTbool(&vars[5], isManaged);
        pIUtil->m_formatVariantW(output, 128, L"Causer: {0:08X}, PlayerCauser: {1:08X}, obj_recv: {2:08X}, isBacktap: {3:d}, allowDamage: {4:d}, isManaged: {5:d}", 6, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[24], index, output);
    }
    return 1; //If set to false, it is managed by you. True for default.
}

// Featured in 0.5.1 and newer
// Changed in 0.5.3.3
dllAPI void WINAPIC EXTOnMapLoad(s_ident map_tag, const wchar_t* map_name, GAME_MODE game_mode) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnMapLoad < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnMapLoad++;
        _itow_s(checkHooks.EXTOnMapLoad, index, 4, 10);
        VARIANTint(&vars[0], map_tag.Tag);
        VARIANTwstr(&vars[1], map_name);
        VARIANTshort(&vars[2], game_mode);
        pIUtil->m_formatVariantW(output, 128, L"Map Tag: {0:08X}, Map: {1:s}, Game Mode: {2:hd}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[25], index, output);
    }
}

dllAPI toggle WINAPIC EXTOnAIVehicleEntry(s_ident bipedTag, s_ident vehicleTag, unsigned short seatNum, toggle isManaged) {
    VARIANT vars[4];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnAIVehicleEntry < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnAIVehicleEntry++;
        _itow_s(checkHooks.EXTOnAIVehicleEntry, index, 4, 10);
        VARIANTint(&vars[0], bipedTag.Tag);
        VARIANTint(&vars[1], vehicleTag.Tag);
        VARIANTushort(&vars[2], seatNum);
        VARIANTchar(&vars[3], isManaged);
        pIUtil->m_formatVariantW(output, 128, L"bipedTag: {0:08X}, vehicleTag: {1:08X}, seatNum: {2:hd}, isManaged: {3:hhd}", 4, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[26], index, output);
    }
    return -1; //-1 = default, 0 = prevent entry, 1 = force entry
}

// Changed in 0.5.3.3
dllAPI void WINAPIC EXTOnWeaponDropCurrent(PlayerInfo plI, s_ident bipedTag, s_biped* biped, s_ident weaponTag, s_weapon* weapon) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponDropCurrent < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponDropCurrent++;
        _itow_s(checkHooks.EXTOnWeaponDropCurrent, index, 4, 10);
        VARIANTint(&vars[0], bipedTag.Tag);
        VARIANTint(&vars[1], weaponTag.Tag);
        pIUtil->m_formatVariantW(output, 128, L"bipedTag: {0:08X}, weaponTag: {1:08X}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[27], index, output);
    }
}

dllAPI toggle WINAPIC EXTOnServerStatus(int execId, toggle isManaged) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnServerStatus < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnServerStatus++;
        _itow_s(checkHooks.EXTOnServerStatus, index, 4, 10);
        VARIANTint(&vars[0], execId);
        VARIANTchar(&vars[1], isManaged);
        pIUtil->m_formatVariantW(output, 128, L"execId: {0:d}, isManaged: {1:hhd}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[28], index, output);
    }
    return -1; //-1 = default, 0 = hide message, 1 = show message
}

// Featured in 0.5.2.3 and newer
dllAPI void WINAPIC EXTOnPlayerUpdate(PlayerInfo plI) {
    VARIANT vars[1];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnPlayerUpdate < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnPlayerUpdate++;
        _itow_s(checkHooks.EXTOnPlayerUpdate, index, 4, 10);
        VARIANTwstr(&vars[0], plI.plS->Name);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}", 1, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[29], index, output);
    }
}

dllAPI void WINAPIC EXTOnMapReset() {
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnMapReset < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnMapReset++;
        _itow_s(checkHooks.EXTOnMapReset, index, 4, 10);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[30], index, L"Reset");
    }
}

// Featured in 0.5.3.0 and newer
// Enabled in 0.5.3.4
dllAPI OBJECT_ATTEMPT WINAPIC EXTOnObjectCreateAttempt(PlayerInfo plOwner, objCreationInfo object_creation, objCreationInfo* change_object) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectCreateAttempt < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectCreateAttempt++;
        _itow_s(checkHooks.EXTOnObjectCreateAttempt, index, 4, 10);
        VARIANTint(&vars[0], object_creation.map_id.Tag);
        VARIANTint(&vars[1], object_creation.parent_id.Tag);
        VARIANTfloat(&vars[2], object_creation.pos.x);
        VARIANTfloat(&vars[3], object_creation.pos.y);
        VARIANTfloat(&vars[4], object_creation.pos.z);
        pIUtil->m_formatVariantW(output, 128, L"map_id: {0:08X}, parent_id: {1:08X}, pos.x: {2:f}, pos.y: {3:f}, pos.z: {4:f}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[31], index, output);
    }
    return OBJECT_ATTEMPT_DEFAULT; //Look in OBJECT_ATTEMPT enum for available options to return.
}

// Featured in 0.5.3.2 and newer
dllAPI bool WINAPIC EXTOnGameSpyValidationCheck(unsigned int UniqueID, bool isValid, bool forceBypass) {
    VARIANT vars[3];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnGameSpyValidationCheck < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnGameSpyValidationCheck++;
        _itow_s(checkHooks.EXTOnGameSpyValidationCheck, index, 4, 10);
        VARIANTint(&vars[0], UniqueID);
        VARIANTbool(&vars[1], isValid);
        VARIANTbool(&vars[2], forceBypass);
        pIUtil->m_formatVariantW(output, 128, L"UniqueID: {0:d}, isValid: {1:d}, forceBypass: {2:d}", 3, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[32], index, output);
    }
    return 1; //Set to false will force bypass. True for default. Use isOverride check.
}

// Featured in 0.5.3.3 and newer
dllAPI bool WINAPIC EXTOnWeaponExchangeAttempt(PlayerInfo plOwner, s_ident bipedTag, s_biped* biped, int slot_index, s_ident weaponTag, s_weapon* weapon, bool allowExchange) {
    VARIANT vars[5];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnWeaponExchangeAttempt < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnWeaponExchangeAttempt++;
        _itow_s(checkHooks.EXTOnWeaponExchangeAttempt, index, 4, 10);
        VARIANTwstr(&vars[0], plOwner.plS==0? nullStr: plOwner.plS->Name);
        VARIANTint(&vars[1], bipedTag.Tag);
        VARIANTint(&vars[2], slot_index);
        VARIANTint(&vars[3], weaponTag.Tag);
        VARIANTbool(&vars[4], allowExchange);
        pIUtil->m_formatVariantW(output, 128, L"Player: {0:s}, bipedTag: {1:08X}, index: {2:d}, weaponTag: {3:08X}, allowExchange: {4:hhd}", 5, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[33], index, output);
    }
    return 1; //If false, then will deny exchange weapon. True by default. Use allowExchange check, if already false. Don't do anything.
}

// Featured in 0.5.3.4 and newer
dllAPI void WINAPIC EXTOnObjectDelete(s_ident obj_id, s_object* obj_Struct, hTagHeader* header) {
    VARIANT vars[2];
    wchar_t output[INIFILEVALUEMAX];
    static wchar_t index[4] = { 0 };
    if (checkHooks.EXTOnObjectDelete < MAX_HOOK_COUNTER) {
        checkHooks.EXTOnObjectDelete++;
        _itow_s(checkHooks.EXTOnObjectDelete, index, 4, 10);
        VARIANTint(&vars[0], obj_Struct->ModelTag.Tag);
        VARIANTstr(&vars[1], header->tag_name);
        pIUtil->m_formatVariantW(output, 128, L"Object Model Tag: {0:08X}, tag_name: {1:s}", 2, vars);
        CALL_MEMBER_FN(pICIniFile, m_value_set, HookNames[34], index, output);
    }
}

#include "..\Add-on API\C\expChecker.h"
