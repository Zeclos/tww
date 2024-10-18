//
// Generated by dtk
// Translation Unit: J2DPrint.cpp
//

#include "JSystem/J2DGraph/J2DPrint.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "stdlib.h"
#include "dolphin/types.h"

char* J2DPrint::mStrBuff;
bool J2DPrint::mHeapFlag;
u32 J2DPrint::mStrBuffSize;
u8 J2DPrint::mBufferNotEnough;

/* 802CE108-802CE194       .text __ct__8J2DPrintFP7JUTFontffQ28JUtility6TColorQ28JUtility6TColorQ28JUtility6TColorQ28JUtility6TColor */
J2DPrint::J2DPrint(JUTFont* pFont, f32 param_2, f32 param_3, JUtility::TColor param_4, JUtility::TColor param_5, JUtility::TColor param_6, JUtility::TColor param_7) {
    private_initiate(pFont, param_2, param_3, param_4, param_5, param_6, param_7, false);
}

static f32 dummy() {
    return 0.0f;
}

/* 802CE194-802CE384       .text private_initiate__8J2DPrintFP7JUTFontffQ28JUtility6TColorQ28JUtility6TColorQ28JUtility6TColorQ28JUtility6TColorb */
void J2DPrint::private_initiate(JUTFont* pFont, f32 param_2, f32 param_3, JUtility::TColor param_4, JUtility::TColor param_5, JUtility::TColor param_6, JUtility::TColor param_7, bool param_8) {
    if (mStrBuff == NULL) {
        setBuffer(0x400);
    }
    mFont = pFont;
    field_0x48 = param_2;
    field_0x4c = 32.0f;

    if (mFont != NULL) {
        f32 temp;
        if (param_8 == false) {
            temp = param_3;
        } else {
            temp = mFont->getLeading();
        }
        field_0x4c = temp;
    }

    field_0x5a = 1;
    locate(0.0f, 0.0f);
    mCharColor = param_4;
    mGradColor = param_5;
    field_0x38 = param_6;
    field_0x3c = param_7;

    if (mFont == NULL) {
        field_0x58 = 80;
    } else {
        field_0x58 = mFont->getWidth() << 2;
    }

    if (mFont != NULL) {
        setFontSize();
        mFont->setGX(field_0x38, field_0x3c);
    }
    initchar();
}

/* 802CE384-802CE424       .text setBuffer__8J2DPrintFUl */
char* J2DPrint::setBuffer(u32 size) {
    JUT_ASSERT(324, size > 0);
    char* tmp = mStrBuff;
    if (mHeapFlag) {
        delete mStrBuff;
    }
    mStrBuff = new(JKRHeap::sSystemHeap, 0) char[size];
    mStrBuffSize = size;
    mHeapFlag = true;
    return tmp;
}

/* 802CE424-802CE4BC       .text setFontSize__8J2DPrintFv */
void J2DPrint::setFontSize() {
    if (mFont) {
        mFontSizeX = mFont->getCellWidth();
        mFontSizeY = mFont->getCellHeight();
    }
}

/* 802CE4BC-802CE4D8       .text locate__8J2DPrintFff */
void J2DPrint::locate(f32 param_1, f32 param_2) {
    field_0x24 = param_1;
    field_0x28 = param_2;
    field_0x2c = param_1;
    mCursorV = param_2;
    field_0x34 = 0.0f;
}

/* 802CE4D8-802CE888       .text printReturn__8J2DPrintFPCcff18J2DTextBoxHBinding18J2DTextBoxVBindingffUc */
void J2DPrint::printReturn(const char* param_1, f32 param_2, f32 param_3, J2DTextBoxHBinding param_4, J2DTextBoxVBinding param_5, f32 param_6, f32 param_7, u8 param_8) {
    if (mFont != NULL) {
        initchar();
        field_0x24 = s32(field_0x2c);
        field_0x28 = s32(mCursorV);
        size_t sVar6 = strlen(param_1);
        if (sVar6 >= mStrBuffSize) {
            sVar6 = mStrBuffSize - 1;
            mBufferNotEnough = 1;
        }
        u16 local_2b0[260];
        TSize aTStack_2b8;
        f32 dVar10 = parse((const u8*)param_1, sVar6, param_2, local_2b0, aTStack_2b8,
                               param_8, false);
        f32 dVar12 = mFont->getAscent()*(mFontSizeY / mFont->getCellHeight());
        f32 dVar13 = dVar10 + dVar12;
        switch (param_5)
        {
        case VBIND_TOP:
            break;
        case VBIND_BOTTOM:
            param_7 += param_3 - (s32)(dVar13 + 0.5f);
            break;
        case VBIND_CENTER:
            param_7 += (param_3 - (s32)(dVar13 + 0.5f)) / 2.0f;
        default:
            break;
        }

        for (int iVar8 = 0; local_2b0[iVar8] != 0xffff; iVar8++) {
            switch (param_4) {
            case HBIND_LEFT:
                local_2b0[iVar8] = 0;
                break;
            case HBIND_RIGHT:
                local_2b0[iVar8] = param_2 - local_2b0[iVar8];
                break;
            case HBIND_CENTER:
                f32 fVar1 = (local_2b0[iVar8]);
                fVar1 = param_2 - fVar1;
                f32 ratio = 0.5f;
                local_2b0[iVar8] = fVar1 * ratio;
                break;
            }
        }
        initchar();
        field_0x2c += param_6;
        mCursorV += param_7 + dVar12;
        field_0x24 = s32(field_0x2c);
        field_0x28 = s32(mCursorV);
        parse((const u8*)param_1, sVar6, param_2, local_2b0, aTStack_2b8, param_8, true);
    }
}

/* 802CE888-802CEF9C       .text parse__8J2DPrintFPCUciiPUsRQ28J2DPrint5TSizeUcb */
f32 J2DPrint::parse(const u8* param_1, int param_2, int param_3, u16* param_4, J2DPrint::TSize& param_5, u8 param_6, bool param_7) {
    if (mFont == NULL) {
        return 0.0f;
    }
    const u8* local_a4 = param_1;
    u16 r29 = 0;
    f32 f30 = field_0x2c;
    f32 f28 = mCursorV;
    f32 f31 = 0.0f;
    f32 local_a8 = f31;
    int r27 = *(param_1++);
    f32 f29 = field_0x2c;
    f32 local_ac = field_0x2c;
    f32 local_b0 = mCursorV;
    f32 local_b4 = mCursorV;
    JUtility::TColor local_b8 = field_0x8;
    JUtility::TColor local_bc = field_0xc;
    f32 local_c0;
    local_b8.a = local_b8.a * param_6 / 0xff;
    local_bc.a = local_bc.a * param_6 / 0xff;
    JUtility::TColor* local_d8;
    if (field_0x22) {
        local_d8 = &local_bc;
    } else {
        local_d8 = &local_b8;
    }
    mFont->setGradColor(local_b8, *local_d8);
    u8 local_f0;
    bool r25;
    do {
        local_f0 = 0;
        if (mFont->isLeadByte(r27)) {
            r27 = (r27 << 8) | (*(param_1++));
            local_f0 = 1;
        }

        if (r27 == 0 || ((u32)param_1 - (u32)local_a4) > param_2) {
            if (param_7 == 0 && param_4 != NULL) {
                param_4[r29] = 0.5f + f31;
            }
            r29++;
            break;
        } else {
            r25 = true;
            local_c0 = field_0x2c;
            if (r27 < 0x20) {
                if (r27 == 0x1b) {
                    u16 local_e8 = doEscapeCode(&param_1, param_6);
                    if (local_e8 == 'HM') {
                        if ((param_7 == 0) && (param_4 != NULL)) {
                            param_4[r29] = 0.5f + f31;
                        }
                        field_0x2c = f30;
                        mCursorV = f28;
                        r29++;
                        if (r29 == 0x100) {
                            break;
                        }
                        f31 = 0.0f;
                    }
                    if (local_e8) {
                        r25 = false;
                    }
                } else {
                    doCtrlCode(r27);
                    r25 = false;
                    if (r27 == 10) {
                        if ((!param_7) && (param_4 != NULL)) {
                            param_4[r29] = 0.5f + f31;
                        }
                        r29++;
                        if (r29 == 0x100) {
                            break;
                        }
                        f31 = 0.0f;
                    }
                }
            } else if (local_f0 && ((u32)param_1 - (u32)local_a4 > (u32)param_2)) {
                if ((!param_7) && (param_4 != NULL)) {
                    param_4[r29] = 0.5f + f31;
                }
                r29++;
                break;
            } else {
                if (mFont->isFixed()) {
                    field_0x34 = mFont->getFixedWidth();
                } else {
                    JUTFont::TWidth uStack_ec;
                    mFont->getWidthEntry(r27, &uStack_ec);
                    field_0x34 = uStack_ec.field_0x1;
                }

                field_0x34 *= field_0x18 / mFont->getCellWidth();
                f32 fVar6 = ((field_0x2c + field_0x34) - field_0x24);
                fVar6 = 10000.0f * fVar6;
                f32 local_90 = ((s32)fVar6) / 10000.0f;
                if (local_90 > param_3 && field_0x2c > f30) {
                    u32 local_e4;
                    if (local_f0) {
                        local_e4 = 2;
                    } else {
                        local_e4 = 1;
                    }
                    param_1 -= local_e4;
                    mCursorV += field_0x14;
                    if (!param_7 && (param_4 != NULL)) {
                        param_4[r29] = 0.5f + f31;
                    }
                    r29++;
                    if (r29 == 0x100) {
                        break;
                    }
                    field_0x2c = field_0x24;
                    f31 = 0.0f;
                    r25 = false;
                } else {
                    if (param_7) {
                        if (param_4 != NULL) {
                            mFont->drawChar_scale(field_0x2c + (f32)(s16)param_4[r29], mCursorV,
                                field_0x18, field_0x1c, r27, true);
                        } else {
                            mFont->drawChar_scale(field_0x2c, mCursorV,
                                field_0x18, field_0x1c, r27, true);
                        }
                    }
                    field_0x2c += field_0x34;
                }
            }
        }

        if (r25) {
            if (field_0x2c - f30 > f31) {
                f31 = field_0x2c - f30;
            }
            field_0x2c += field_0x10;
            field_0x34 += field_0x10;
            f32 local_cc = (field_0x1c / mFont->getHeight()) * mFont->getDescent();
            if (local_a8 < mCursorV + local_cc) {
                local_a8 = mCursorV + local_cc;
            }
            if (field_0x2c > local_ac) {
                local_ac = field_0x2c;
            }
            if (field_0x2c < f29) {
                f29 = field_0x2c;
            }
            if (local_c0 < f29) {
                f29 = local_c0;
            }
            if (mCursorV > local_b4) {
                local_b4 = mCursorV;
            }
            if (mCursorV < local_b0) {
                local_b0 = mCursorV;
            }
        }
        r27 = *(param_1++);
    } while (true);

    if (param_4 != NULL) {
        param_4[r29] = 0xffff;
    }
    param_5.field_0x0 = local_ac - f29;
    param_5.field_0x4 = local_b4 - local_b0 + mFont->getLeading();
    if (!param_7) {
        field_0x2c = f30;
        mCursorV = f28;
    }
    return local_a8;
}

/* 802CEF9C-802CF0C4       .text doCtrlCode__8J2DPrintFi */
void J2DPrint::doCtrlCode(int param_1) {
    switch (param_1) {
    case 8:
        field_0x2c -= field_0x34;
        field_0x34 = 0.0f;
        break;
    case 9:
        if (field_0x20 > 0) {
            f32 fVar1 = field_0x2c;
            field_0x2c = field_0x20 + field_0x20 * (int)((int)field_0x2c / field_0x20);
            field_0x34 = field_0x2c - fVar1;
        }
        break;
    case 10:
        field_0x34 = 0.0f;
        field_0x2c = field_0x24;
        mCursorV += field_0x14;
        break;
    case 0xd:
        field_0x34 = 0.0f;
        field_0x2c = field_0x24;
        break;
    case 0x1c:
        field_0x2c += 1.0f;
        break;
    case 0x1d:
        field_0x2c -= 1.0f;
        break;
    case 0x1e:
        mCursorV -= 1.0f;
        break;
    case 0x1f:
        mCursorV += + 1.0f;
    }
}

/* 802CF0C4-802CF600       .text doEscapeCode__8J2DPrintFPPCUcUc */
u16 J2DPrint::doEscapeCode(const u8** param_1, u8 param_2) {
    u8 const* puVar9 = *param_1;
    u16 uVar11 = 0;
    u16 uVar3;
    for (int iVar10 = 0; iVar10 < 2; iVar10++) {
        if (mFont->isLeadByte(**param_1)) {
            uVar3 = ((**param_1) << 8) | (*param_1)[1];
            (*param_1) += 2;
        } else {
            uVar3 = **param_1;
            (*param_1)++;
        }
        if (uVar3 >= 0x80 || uVar3 < 0x20) {
            *param_1 = puVar9;
            return 0;
        }
        uVar11 = ((uVar11) << 8) | uVar3;
    }

    JUtility::TColor local_40 = field_0x8;
    JUtility::TColor local_44 = field_0xc;
    switch(uVar11) {
    case 'CU':
        mCursorV -= getNumberF32(param_1, 1.0f, 0.0f, 10);
        break;
    case 'CD':
        mCursorV += getNumberF32(param_1, 1.0f, 0.0f, 10);
        break;
    case 'CL':
        field_0x2c -= getNumberF32(param_1, 1.0f, 0.0f, 10);
        break;
    case 'CR':
        field_0x2c += getNumberF32(param_1, 1.0f, 0.0f, 10);
        break;
    case 'LU':
        mCursorV -= field_0x14;
        break;
    case 'LD':
        mCursorV += field_0x14;
        break;
    case 'ST': {
        s32 val = getNumberS32(param_1, field_0x20, field_0x20, 10);
        if (val > 0) {
            field_0x20 = val;
        }
        break;
    }
    case 'CC':
        field_0x8 = getNumberS32(param_1, *(u32*)&mCharColor, *(u32*)&field_0x8, 16);
        local_40 = field_0x8;
        local_40.a = local_40.a * param_2 / 0xff;
        local_44.a = local_44.a * param_2 / 0xff;
        JUtility::TColor* local_68;
        if (field_0x22 != 0) {
            local_68 = &local_44;
        }
        else {
            local_68 = &local_40;
        }
        mFont->setGradColor(local_40, *local_68);
        break;
    case 'GC':
        field_0xc = getNumberS32(param_1, *(u32*)&mGradColor, *(u32*)&field_0xc, 16);
        local_44 = field_0xc;
        local_40.a = local_40.a * param_2 / 0xff;
        local_44.a = local_44.a * param_2 / 0xff;
        JUtility::TColor* local_74;
        if (field_0x22 != 0) {
            local_74 = &local_44;
        }
        else {
            local_74 = &local_40;
        }
        mFont->setGradColor(local_40, *local_74);
        break;
    case 'FX': {
        f32 dVar13 = getNumberF32(param_1, mFontSizeX, field_0x18, 10);
        if (dVar13 >= 0) {
            field_0x18 = dVar13;
        }
        break;
    }
    case 'FY': {
        f32 dVar14 = getNumberF32(param_1, mFontSizeY, field_0x1c, 10);
        if (dVar14 >= 0) {
            field_0x1c = dVar14;
        }
        break;
    }
    case 'SH':
        field_0x10 = getNumberF32(param_1, field_0x48, field_0x10, 10);
        break;
    case 'SV':
        field_0x14 = getNumberF32(param_1, field_0x4c, field_0x14, 10);
        break;
    case 'GM': {
        s32 isZero = getNumberS32(param_1, field_0x22 == 0, field_0x22, 10) == 0;
        field_0x22 = isZero == 0;
        local_40.a = local_40.a * param_2 / 0xff;
        local_44.a = local_44.a * param_2 / 0xff;
        JUtility::TColor* local_80;
        if (field_0x22 != 0) {
            local_80 = &local_44;
        }
        else {
            local_80 = &local_40;
        }
        mFont->setGradColor(local_40, *local_80);
        break;
    }
    case 'HM':
        break;
    default:
        *param_1 = puVar9;
        uVar11 = 0;
        break;
    }
    return uVar11;
}

/* 802CF600-802CF674       .text initchar__8J2DPrintFv */
void J2DPrint::initchar() {
    field_0x8 = mCharColor;
    field_0xc = mGradColor;
    field_0x10 = field_0x48;
    field_0x14 = field_0x4c;
    field_0x22 = field_0x5a;
    field_0x20 = field_0x58;
    field_0x18 = mFontSizeX;
    field_0x1c = mFontSizeY;
}

/* 802CF674-802CF778       .text getNumberS32__8J2DPrintFPPCUclli */
s32 J2DPrint::getNumberS32(const u8** param_1, s32 param_2, s32 param_3, int base) {
    const u8* puVar1 = *param_1;
    s32 uVar2 = param_2;
    if (*puVar1 != '[') {
        return param_2;
    }
    (*param_1)++;
    uVar2 = 0;
    char* local_28;
    if (base == 10) {
        uVar2 = strtol((char*)*param_1, &local_28, base);
    } else if (base == 16) {
        uVar2 = strtoul((char*)*param_1, &local_28, base);
        if ((u32)local_28 - (u32)*param_1 != 8) {
            if ((u32)local_28 - (u32)*param_1 == 6) {
                uVar2 = (uVar2 << 8) | 0xff;
            } else {
                *param_1 = puVar1;
                return param_3;
            }
        }
    }
    if (local_28[0] != ']') {
        *param_1 = puVar1;
        return param_3;
    } else {
        if ((char*)*param_1 == (char*)local_28) {
            *param_1 = (const u8*)local_28 + 1;
            return param_2;
        } else {
            *param_1 = (const u8*)local_28 + 1;
        }
    }
    return uVar2;
}

/* 802CF778-802CF8AC       .text getNumberF32__8J2DPrintFPPCUcffi */
f32 J2DPrint::getNumberF32(const u8** param_1, f32 param_2, f32 param_3, int base) {
    const u8* puVar1 = *param_1;
    s32 uVar2 = param_2;
    if (*puVar1 != '[') {
        return param_2;
    }
    (*param_1)++;
    uVar2 = 0;
    char* local_28;
    if (base == 10) {
        uVar2 = strtol((char*)*param_1, &local_28, base);
    } else if (base == 16) {
        uVar2 = strtoul((char*)*param_1, &local_28, base);
        if ((u32)local_28 - (u32)*param_1 != 8) {
            if ((u32)local_28 - (u32)*param_1 == 6) {
                uVar2 = (uVar2 << 8) | 0xff;
            } else {
                *param_1 = puVar1;
                return param_3;
            }
        }
    }
    if (local_28[0] != ']') {
        *param_1 = puVar1;
        return param_3;
    } else {
        if ((char*)*param_1 == (char*)local_28) {
            *param_1 = (const u8*)local_28 + 1;
            return param_2;
        } else {
            *param_1 = (const u8*)local_28 + 1;
        }
    }
    return uVar2;
}

static void dummy2() {
    OSReport("buff != 0");
}
