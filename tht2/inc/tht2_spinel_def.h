/**
 * @file tht2_spinel_def.h
 * @author David Zeman (dzeman.elekon@gmail.com)
 * @brief 
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef THT2_SPINEL_DEF_H_
#define THT2_SPINEL_DEF_H_


// SPINEL PACKET
typedef enum
{
    PRE                         = 0,
    FRM                         = 1,
    LEN_H                       = 2,
    LEN_L                       = 3,
    ADR                         = 4,
    SIG                         = 5,
    INST                        = 6,
    DATA                        = 7,
}   SPINEL_PACKET_e;

#define SUM                     DATA + dataLen
#define END                     SUM  + 1


// SPINEL PREFIX (PRE)
#define PREXIF                  0x2A        // prefix    (znak '*')

// SPINEL FORMAT (FRM)
#define FORMAT_97               0x61        // format 97 (znak 'a')
#define FORMAT_66               0x42        // format 66 (znak 'B')

// SPINEL CODE (INST)
#define C_WCOM                  0xe0        // zapis komunikacnich parametru
#define C_RCOM                  0xf0        // cteni komunikacnich parametru
#define C_WSTAT                 0xe1        // zapis status byte
#define C_RSTAT                 0xf1        // cteni status byte
#define C_WUD                   0xe2        // zapis uzivatelskych dat
#define C_RESET                 0xe3        // reset zarizeni
#define C_CEN                   0xe4        // povoleni konfigurace
#define C_SCSC                  0xee        // povoleni checksumu
#define C_RCSC                  0xfe        // cteni povoleni checksumu
#define C_RUD                   0xf2        // cteni uzivatelskych dat
#define C_NAME                  0xf3        // dotaz na jmeno a typ zarizeni
#define C_RCE                   0xf4        // cteni chyb komunikace
#define C_TEMP                  0x51        // cteni teploty

// SPINEL CODE (ACK)
#define	ACK_OK		            0x00		// OK
#define	ACK_BAD_I	            0x02		// neplatna instrukce
#define	ACK_BAD_D	            0x03		// neplatna data
#define	ACK_WD_AD	            0x04		// zakazany zapis / pristup odmitnut
#define	ACK_DEV_ERR	            0x05		// HW chyba zarizeni
#define	ACK_AUTO	            0x0E		// automaticky generovany vystup 

// SPINEL END CHAR (CR)
#define END_CHAR                0x0D        // zakoncovaci znak


#define BIN2HEX_TABLE           (char[]) {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
#define BIN2HEX_L(ch)           BIN2HEX_TABLE[((ch) >> 0) & 0x0F]
#define BIN2HEX_H(ch)           BIN2HEX_TABLE[((ch) >> 4) & 0x0F]


#endif /* THT2_SPINEL_DEF_H_ */
