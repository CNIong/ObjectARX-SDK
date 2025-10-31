/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 28 12:27:27 2000
 */
/* Compiler settings for C:\ObjectARX 2000\Samples\Smiley\SmileyDbCom\SmileyDbCom.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_AsdkSmileyDbComLib = {0x066DA281,0xCC00,0x11D2,{0xB5,0x85,0x00,0x10,0xA4,0x01,0xA3,0x7F}};


const IID IID_ISmileyEntity = {0x066DA2A2,0xCC00,0x11D2,{0xB5,0x85,0x00,0x10,0xA4,0x01,0xA3,0x7F}};


const CLSID CLSID_SmileyEntity = {0x46765BA4,0xC4CD,0x11D2,{0xB5,0x79,0x00,0x10,0xA4,0x01,0xA3,0xC5}};


#ifdef __cplusplus
}
#endif

