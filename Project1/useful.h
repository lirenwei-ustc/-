#ifndef __USEFUL_H
#define __USEFUL_H

#include <iostream>
#include <vector>

using namespace std;

#define CHANGE_SMALL(x) (((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000) | ((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00))
#define GET_INDEX_INT_DATA(p, x) (*((int*)(p) + x))
#define BYTE_ALIGNMENT(p, x) (((p) % x == 0 ? (p) : (p) / x * x + x))

//KOVS
#define KOVS 0x53564F4B
#define KOVS_AFTER ".kvs"

//HBW
#define HBW 0x5742485f
#define DBW 0x5742445f

//WAV
#define WAV_AFTER ".wav"

//stbin
#define STBIN_AFTER ".ktsl2stbin"

//asbin
#define ASBIN_AFTER ".ktsl2asbin"

//SM4
#define SM4_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM4_SRC/"

#define SM4_VOICE_FILE "LINKVOI.BIN"
#define SM4_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM4_OUTPUT/SM4_VOICE/"

#define SM4_BGM_FILE "LINKBGM.BIN"
#define SM4_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM4_OUTPUT/SM4_BGM/"

#define SM4_EFFECT_FILE "LINKSE.BIN"
#define SM4_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM4_OUTPUT/SM4_EFFECT/"

//SM5
#define SM5_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM5_SRC/"

#define SM5_VOICE_FILE "LINKDATA_T.BIN"
#define SM5_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM5_OUTPUT/SM5_VOICE/"

#define SM5_BGM_FILE "BGMLink.g1l"
#define SM5_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM5_OUTPUT/SM5_BGM/"

#define SM5_EFFECT_FILE "LINKDATA_T.BIN"
#define SM5_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM5_OUTPUT/SM5_EFFECT/"

//SM6
#define SM6_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM6_SRC/"

#define SM6_VOICE_FILE "LINKDATA3.BIN"
#define SM6_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM6_OUTPUT/SM6_VOICE/"

#define SM6_BGM_FILE "BGMLink.g1l"
#define SM6_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM6_OUTPUT/SM6_BGM/" 

//SM7
#define SM7_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7_SRC/"

#define SM7_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7_OUTPUT/SM7_VOICE/"

#define SM7_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7_OUTPUT/SM7_BGM/"

//SM7E
#define SM7E_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7E_SRC/"

#define SM7E_VOICE_FILE "LINKDATA0.BIN"
#define SM7E_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7E_OUTPUT/SM7E_VOICE/"

#define SM7E_BGM_FILE "LINKDATA0.BIN"
#define SM7E_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM7E_OUTPUT/SM7E_BGM/"

//SM8
#define SM8_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SM8_SRC/"

#define SM8_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM8_OUTPUT/SM8_VOICE/"

#define SM8_BGM_FILE "bgm.atsl"
#define SM8_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM8_OUTPUT/SM8_BGM/"

//SMOL
#define SMOL_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SMOL_SRC/"

#define SMOL_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMOL_OUTPUT/SMOL_VOICE/"

#define SMOL_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMOL_OUTPUT/SMOL_BGM/"

#define SMOL_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMOL_OUTPUT/SMOL_EFFECT/"

//Î´½â¾ö
#define SM6_EFFECT_FILE "LINKDATA3.BIN"
#define SM6_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SM6_EFFECT/"

//ORI
#define ORI_INPUT_PREFER "I:/HDD-History/Koei Shin Source/ORI_SRC/"

#define ORI_VOICE_FILE "LINK_VODAT.BDX"
#define ORI_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/ORI_OUTPUT/ORI_VOICE/"

#define ORI_BGM_FILE "LINK_BGM.BDX"
#define ORI_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/ORI_OUTPUT/ORI_BGM/"

#define ORI_EFFECT_FILE_HEADER "LINK_SEBANK.HDX"
#define ORI_EFFECT_FILE "LINK_SEBANK.BDX"
#define ORI_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/ORI_OUTPUT/ORI_EFFECT/"

//SMZ
#define SMZ_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SMZ_SRC/"

#define SMZ_VOICE_FILE "Voice.bin"
#define SMZ_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMZ_OUTPUT/SMZ_VOICE/"

#define SMZ_BGM_FILE "BGMLink.g1l"
#define SMZ_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMZ_OUTPUT/SMZ_BGM/"

#define SMZ_EFFECT_FILE "LINKDATA1.BIN"
#define SMZ_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SMZ_OUTPUT/SMZ_EFFECT/"

//SR2
#define SR2_INPUT_PREFER "I:/HDD-History/Koei Shin Source/SR2_SRC/"

#define SR2_VOICE_FILE "LINKDATA_ANS_TWN.LNK"
#define SR2_VOICE_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SR2_OUTPUT/SR2_VOICE/"

#define SR2_EFFECT_FILE_HEADRE "LINK_SEBANK_TWN.idx"
#define SR2_EFFECT_FILE "LINK_SEBANK_TWN.LNK"
#define SR2_EFFECT_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SR2_OUTPUT/SR2_EFFECT/"

#define SR2_BGM_FILE "LINK_BGM.LNK"
#define SR2_BGM_OUTPUT_PREFER "I:/HDD-History/Koei Shin Source/SR2_OUTPUT/SR2_BGM/"

#endif