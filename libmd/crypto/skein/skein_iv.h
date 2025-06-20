#ifndef _SKEIN_IV_H_
#define _SKEIN_IV_H_

#include "skein.h"    /* get Skein macros and types */

/*
***************** Pre-computed Skein IVs *******************
**
** NOTE: these values are not "magic" constants, but
** are generated using the Threefish block function.
** They are pre-computed here only for speed; i.e., to
** avoid the need for a Threefish call during Init().
**
** The IV for any fixed hash length may be pre-computed.
** Only the most common values are included here.
**
************************************************************
**/

#define MK_64 SKEIN_MK_64

/* blkSize =  256 bits. hashSize =  128 bits */
static const u64b_t SKEIN_256_IV_128[] =
    {
    MK_64(0xE1111906,0x964D7260),
    MK_64(0x883DAAA7,0x7C8D811C),
    MK_64(0x10080DF4,0x91960F7A),
    MK_64(0xCCF7DDE5,0xB45BC1C2)
    };

/* blkSize =  256 bits. hashSize =  160 bits */
static const u64b_t SKEIN_256_IV_160[] =
    {
    MK_64(0x14202314,0x72825E98),
    MK_64(0x2AC4E9A2,0x5A77E590),
    MK_64(0xD47A5856,0x8838D63E),
    MK_64(0x2DD2E496,0x8586AB7D)
    };

/* blkSize =  256 bits. hashSize =  224 bits */
static const u64b_t SKEIN_256_IV_224[] =
    {
    MK_64(0xC6098A8C,0x9AE5EA0B),
    MK_64(0x876D5686,0x08C5191C),
    MK_64(0x99CB88D7,0xD7F53884),
    MK_64(0x384BDDB1,0xAEDDB5DE)
    };

/* blkSize =  256 bits. hashSize =  256 bits */
static const u64b_t SKEIN_256_IV_256[] =
    {
    MK_64(0xFC9DA860,0xD048B449),
    MK_64(0x2FCA6647,0x9FA7D833),
    MK_64(0xB33BC389,0x6656840F),
    MK_64(0x6A54E920,0xFDE8DA69)
    };

/* blkSize =  512 bits. hashSize =  128 bits */
static const u64b_t SKEIN_512_IV_128[] =
    {
    MK_64(0xA8BC7BF3,0x6FBF9F52),
    MK_64(0x1E9872CE,0xBD1AF0AA),
    MK_64(0x309B1790,0xB32190D3),
    MK_64(0xBCFBB854,0x3F94805C),
    MK_64(0x0DA61BCD,0x6E31B11B),
    MK_64(0x1A18EBEA,0xD46A32E3),
    MK_64(0xA2CC5B18,0xCE84AA82),
    MK_64(0x6982AB28,0x9D46982D)
    };

/* blkSize =  512 bits. hashSize =  160 bits */
static const u64b_t SKEIN_512_IV_160[] =
    {
    MK_64(0x28B81A2A,0xE013BD91),
    MK_64(0xC2F11668,0xB5BDF78F),
    MK_64(0x1760D8F3,0xF6A56F12),
    MK_64(0x4FB74758,0x8239904F),
    MK_64(0x21EDE07F,0x7EAF5056),
    MK_64(0xD908922E,0x63ED70B8),
    MK_64(0xB8EC76FF,0xECCB52FA),
    MK_64(0x01A47BB8,0xA3F27A6E)
    };

/* blkSize =  512 bits. hashSize =  224 bits */
static const u64b_t SKEIN_512_IV_224[] =
    {
    MK_64(0xCCD06162,0x48677224),
    MK_64(0xCBA65CF3,0xA92339EF),
    MK_64(0x8CCD69D6,0x52FF4B64),
    MK_64(0x398AED7B,0x3AB890B4),
    MK_64(0x0F59D1B1,0x457D2BD0),
    MK_64(0x6776FE65,0x75D4EB3D),
    MK_64(0x99FBC70E,0x997413E9),
    MK_64(0x9E2CFCCF,0xE1C41EF7)
    };

/* blkSize =  512 bits. hashSize =  256 bits */
static const u64b_t SKEIN_512_IV_256[] =
    {
    MK_64(0xCCD044A1,0x2FDB3E13),
    MK_64(0xE8359030,0x1A79A9EB),
    MK_64(0x55AEA061,0x4F816E6F),
    MK_64(0x2A2767A4,0xAE9B94DB),
    MK_64(0xEC06025E,0x74DD7683),
    MK_64(0xE7A436CD,0xC4746251),
    MK_64(0xC36FBAF9,0x393AD185),
    MK_64(0x3EEDBA18,0x33EDFC13)
    };

/* blkSize =  512 bits. hashSize =  384 bits */
static const u64b_t SKEIN_512_IV_384[] =
    {
    MK_64(0xA3F6C6BF,0x3A75EF5F),
    MK_64(0xB0FEF9CC,0xFD84FAA4),
    MK_64(0x9D77DD66,0x3D770CFE),
    MK_64(0xD798CBF3,0xB468FDDA),
    MK_64(0x1BC4A666,0x8A0E4465),
    MK_64(0x7ED7D434,0xE5807407),
    MK_64(0x548FC1AC,0xD4EC44D6),
    MK_64(0x266E1754,0x6AA18FF8)
    };

/* blkSize =  512 bits. hashSize =  512 bits */
static const u64b_t SKEIN_512_IV_512[] =
    {
    MK_64(0x4903ADFF,0x749C51CE),
    MK_64(0x0D95DE39,0x9746DF03),
    MK_64(0x8FD19341,0x27C79BCE),
    MK_64(0x9A255629,0xFF352CB1),
    MK_64(0x5DB62599,0xDF6CA7B0),
    MK_64(0xEABE394C,0xA9D5C3F4),
    MK_64(0x991112C7,0x1A75B523),
    MK_64(0xAE18A40B,0x660FCC33)
    };

/* blkSize = 1024 bits. hashSize =  384 bits */
static const u64b_t SKEIN1024_IV_384[] =
    {
    MK_64(0x5102B6B8,0xC1894A35),
    MK_64(0xFEEBC9E3,0xFE8AF11A),
    MK_64(0x0C807F06,0xE32BED71),
    MK_64(0x60C13A52,0xB41A91F6),
    MK_64(0x9716D35D,0xD4917C38),
    MK_64(0xE780DF12,0x6FD31D3A),
    MK_64(0x797846B6,0xC898303A),
    MK_64(0xB172C2A8,0xB3572A3B),
    MK_64(0xC9BC8203,0xA6104A6C),
    MK_64(0x65909338,0xD75624F4),
    MK_64(0x94BCC568,0x4B3F81A0),
    MK_64(0x3EBBF51E,0x10ECFD46),
    MK_64(0x2DF50F0B,0xEEB08542),
    MK_64(0x3B5A6530,0x0DBC6516),
    MK_64(0x484B9CD2,0x167BBCE1),
    MK_64(0x2D136947,0xD4CBAFEA)
    };

/* blkSize = 1024 bits. hashSize =  512 bits */
static const u64b_t SKEIN1024_IV_512[] =
    {
    MK_64(0xCAEC0E5D,0x7C1B1B18),
    MK_64(0xA01B0E04,0x5F03E802),
    MK_64(0x33840451,0xED912885),
    MK_64(0x374AFB04,0xEAEC2E1C),
    MK_64(0xDF25A0E2,0x813581F7),
    MK_64(0xE4004093,0x8B12F9D2),
    MK_64(0xA662D539,0xC2ED39B6),
    MK_64(0xFA8B85CF,0x45D8C75A),
    MK_64(0x8316ED8E,0x29EDE796),
    MK_64(0x053289C0,0x2E9F91B8),
    MK_64(0xC3F8EF1D,0x6D518B73),
    MK_64(0xBDCEC3C4,0xD5EF332E),
    MK_64(0x549A7E52,0x22974487),
    MK_64(0x67070872,0x5B749816),
    MK_64(0xB9CD28FB,0xF0581BD1),
    MK_64(0x0E2940B8,0x15804974)
    };

/* blkSize = 1024 bits. hashSize = 1024 bits */
static const u64b_t SKEIN1024_IV_1024[] =
    {
    MK_64(0xD593DA07,0x41E72355),
    MK_64(0x15B5E511,0xAC73E00C),
    MK_64(0x5180E5AE,0xBAF2C4F0),
    MK_64(0x03BD41D3,0xFCBCAFAF),
    MK_64(0x1CAEC6FD,0x1983A898),
    MK_64(0x6E510B8B,0xCDD0589F),
    MK_64(0x77E2BDFD,0xC6394ADA),
    MK_64(0xC11E1DB5,0x24DCB0A3),
    MK_64(0xD6D14AF9,0xC6329AB5),
    MK_64(0x6A9B0BFC,0x6EB67E0D),
    MK_64(0x9243C60D,0xCCFF1332),
    MK_64(0x1A1F1DDE,0x743F02D4),
    MK_64(0x0996753C,0x10ED0BB8),
    MK_64(0x6572DD22,0xF2B4969A),
    MK_64(0x61FD3062,0xD00A579A),
    MK_64(0x1DE0536E,0x8682E539)
    };

#endif /* _SKEIN_IV_H_ */
