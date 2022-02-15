/**
 * @file spinel_def.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SPINEL_DEF_H_
#define SPINEL_DEF_H_


// SPINEL MSG FRAME - STRUCT             [ PRE | FRM | LEN_H | LEN_L | ADR | SIG | INST | SUM | CR ]
// ---------------------------------------------------------------------------------------------------

// SPINEL MSG LENGHTS
#define SP_MSG_LEN              0x09    // PRE + FRM + LEN_H + LEN_L + ADR + SIG + INST + SUM + CR = 9
#define SP_MSG_HEAD_LEN         0x04    // PRE + FRM + LEN_H + LEN_L                               = 5
#define SP_MSG_BODY_LEN         0x05    //                             ADR + SIG + INST + SUM + CR = 5
#define SP_MSG_DATA_LEN         msgDataLen
#define SP_MSG_DATA             msgData

// SPINEL MSG BYTES
#define SP_PRE                  0x00
#define SP_FRM                  0x01
#define SP_LEN_H                0x02
#define SP_LEN_L                0x03
#define SP_ADR                  0x04
#define SP_SIG                  0x05
#define SP_INST                 0x06
#define SP_ACK                  0x06
#define SP_DATA                 0x07
#define SP_SUM                  (SP_DATA + SP_MSG_DATA_LEN)
#define SP_END                  (SP_SUM  + 1)

// ---------------------------------------------------------------------------------------------------

// SPINEL MSG FRAME - CONTENT
// ---------------------------------------------------------------------------------------------------

// SPINEL PREFIX [PRE]
#define SP_PREXIF               0x2A        // prefix    (znak '*')

// SPINEL FORMAT [FRM]
#define SP_FRM_97               0x61        // format 97 (znak 'a')
#define SP_FRM_66               0x42        // format 66 (znak 'B')

// SPINEL ADDRESS [ADR]
#define SP_ADR_DFL              0xFE        // univerzalni adresa

// SPINEL CODES [INST]
#define SP_INST_WCOM            0xe0        // zapis komunikacnich parametru
#define SP_INST_RCOM            0xf0        // cteni komunikacnich parametru
#define SP_INST_WSTAT           0xe1        // zapis status byte
#define SP_INST_RSTAT           0xf1        // cteni status byte
#define SP_INST_WUD             0xe2        // zapis uzivatelskych dat
#define SP_INST_RESET           0xe3        // reset zarizeni
#define SP_INST_CEN             0xe4        // povoleni konfigurace
#define SP_INST_SCSC            0xee        // povoleni checksumu
#define SP_INST_RCSC            0xfe        // cteni povoleni checksumu
#define SP_INST_RUD             0xf2        // cteni uzivatelskych dat
#define SP_INST_NAME            0xf3        // dotaz na jmeno a typ zarizeni
#define SP_INST_RCE             0xf4        // cteni chyb komunikace

#define SP_INST_TEMP            0x51        // cteni teploty
#define SP_INST_WUNIT           0x1A        // zapis teplotni jednotky
#define SP_INST_RUNIT           0x1B        // cteni teplotni jednotky

// SPINEL CODES [ACK]
#define SP_ACK_OK               0x00        // OK
#define SP_ACK_BAD_I            0x02        // neplatna instrukce
#define SP_ACK_BAD_D            0x03        // neplatna data
#define SP_ACK_WD_AD            0x04        // zakazany zapis / pristup odmitnut
#define SP_ACK_DEV_ERR          0x05        // HW chyba zarizeni
#define SP_ACK_AUTO             0x0E        // automaticky generovany vystup 

// SPINEL END CHAR [CR]
#define SP_END_CHAR             0x0D        // zakoncovaci znak

// ---------------------------------------------------------------------------------------------------

// SPINEL MSG DATA - CONTENT
// ---------------------------------------------------------------------------------------------------

#define SP_VALID_DATA           0x80

// SPINEL CHANNELS
#define SP_CH0_ALL              0x00
#define SP_CH1_TEMP             0x01
#define SP_CH2_HUMI             0x02
#define SP_CH3_DEWP             0x03

// SPINEL TEMP UNIT
#define SP_UNIT_C               0x00
#define SP_UNIT_F               0x01
#define SP_UNIT_K               0x02

// ---------------------------------------------------------------------------------------------------

// CONVERSIONS (not used)
// ---------------------------------------------------------------------------------------------------

#define BIN2HEX_TABLE           (char[]) {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
#define BIN2HEX_L(ch)           BIN2HEX_TABLE[((ch) >> 0) & 0x0F]
#define BIN2HEX_H(ch)           BIN2HEX_TABLE[((ch) >> 4) & 0x0F]

// ---------------------------------------------------------------------------------------------------

#endif /* SPINEL_DEF_H_ */
