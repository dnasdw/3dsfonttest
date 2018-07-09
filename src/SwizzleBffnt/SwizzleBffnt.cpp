#include <sdw.h>
#include <ResourceFormat.h>

const int s_nDecodeTransByte[64] =
{
	 0,  1,  4,  5, 16, 17, 20, 21,
	 2,  3,  6,  7, 18, 19, 22, 23,
	 8,  9, 12, 13, 24, 25, 28, 29,
	10, 11, 14, 15, 26, 27, 30, 31,
	32, 33, 36, 37, 48, 49, 52, 53,
	34, 35, 38, 39, 50, 51, 54, 55,
	40, 41, 44, 45, 56, 57, 60, 61,
	42, 43, 46, 47, 58, 59, 62, 63
};

int decode(u8* a_pBuffer, n32 a_nWidth, n32 a_nHeight, n32 a_nFormat)
{
	switch (a_nFormat)
	{
	case kFontSheetFormat_CTRRGBA8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 4];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 4; k++)
					{
						pTemp[(i * 64 + j) * 4 + k] = a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 4 + 3 - k];
					}
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 4; k++)
					{
						a_pBuffer[(i * a_nWidth + j) * 4 + k] = pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 4 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRRGB8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 3];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 3; k++)
					{
						pTemp[(i * 64 + j) * 3 + k] = a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 3 + 2 - k];
					}
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 3; k++)
					{
						a_pBuffer[(i * a_nWidth + j) * 3 + k] = pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 3 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRRGB5A1:
	case kFontSheetFormat_CTRRGB565:
	case kFontSheetFormat_CTRRGBA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 2];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						pTemp[(i * 64 + j) * 2 + k] = a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 2 + k];
					}
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						a_pBuffer[(i * a_nWidth + j) * 2 + k] = pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 2 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRLA8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 2];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						pTemp[(i * 64 + j) * 2 + k] = a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 2 + 1 - k];
					}
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						a_pBuffer[(i * a_nWidth + j) * 2 + k] = pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 2 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRA8:
	case kFontSheetFormat_CTRLA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					pTemp[i * 64 + j] = a_pBuffer[i * 64 + s_nDecodeTransByte[j]];
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					a_pBuffer[i * a_nWidth + j] = pTemp[((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8];
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight];
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j += 2)
				{
					pTemp[i * 64 + j] = (a_pBuffer[i * 32 + s_nDecodeTransByte[j] / 2] & 0xF) * 0x11;
					pTemp[i * 64 + j + 1] = (a_pBuffer[i * 32 + s_nDecodeTransByte[j] / 2] >> 4 & 0xF) * 0x11;
				}
			}
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j += 2)
				{
					a_pBuffer[(i * a_nWidth + j) / 2] = ((pTemp[((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8] / 0x11) & 0xF) | ((pTemp[((i / 8) * (a_nWidth / 8) + (j + 1) / 8) * 64 + i % 8 * 8 + (j + 1) % 8] / 0x11) << 4 & 0xF0);
				}
			}
			delete[] pTemp;
		}
		break;
	default:
		return 1;
	}
	return 0;
}

int encode(u8* a_pBuffer, n32 a_nWidth, n32 a_nHeight, n32 a_nFormat)
{
	switch (a_nFormat)
	{
	case kFontSheetFormat_CTRRGBA8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 4];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 4; k++)
					{
						pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 4 + k] = a_pBuffer[(i * a_nWidth + j) * 4 + k];
					}
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 4; k++)
					{
						a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 4 + 3 - k] = pTemp[(i * 64 + j) * 4 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRRGB8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 3];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 3; k++)
					{
						pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 3 + k] = a_pBuffer[(i * a_nWidth + j) * 3 + k];
					}
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 3; k++)
					{
						a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 3 + 2 - k] = pTemp[(i * 64 + j) * 3 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRRGB5A1:
	case kFontSheetFormat_CTRRGB565:
	case kFontSheetFormat_CTRRGBA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 2];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 2 + k] = a_pBuffer[(i * a_nWidth + j) * 2 + k];
					}
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 2 + k] = pTemp[(i * 64 + j) * 2 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRLA8:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight * 2];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						pTemp[(((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8) * 2 + k] = a_pBuffer[(i * a_nWidth + j) * 2 + k];
					}
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					for (n32 k = 0; k < 2; k++)
					{
						a_pBuffer[(i * 64 + s_nDecodeTransByte[j]) * 2 + 1 - k] = pTemp[(i * 64 + j) * 2 + k];
					}
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRA8:
	case kFontSheetFormat_CTRLA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j++)
				{
					pTemp[((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8] = a_pBuffer[i * a_nWidth + j];
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j++)
				{
					a_pBuffer[i * 64 + s_nDecodeTransByte[j]] = pTemp[i * 64 + j];
				}
			}
			delete[] pTemp;
		}
		break;
	case kFontSheetFormat_CTRA4:
		{
			u8* pTemp = new u8[a_nWidth * a_nHeight];
			for (n32 i = 0; i < a_nHeight; i++)
			{
				for (n32 j = 0; j < a_nWidth; j += 2)
				{
					pTemp[((i / 8) * (a_nWidth / 8) + j / 8) * 64 + i % 8 * 8 + j % 8] = (a_pBuffer[(i * a_nWidth + j) / 2] & 0xF) * 0x11;
					pTemp[((i / 8) * (a_nWidth / 8) + (j + 1) / 8) * 64 + i % 8 * 8 + (j + 1) % 8] = (a_pBuffer[(i * a_nWidth + j) / 2] >> 4 & 0xF) * 0x11;
				}
			}
			for (n32 i = 0; i < a_nWidth * a_nHeight / 64; i++)
			{
				for (n32 j = 0; j < 64; j += 2)
				{
					a_pBuffer[i * 32 + s_nDecodeTransByte[j] / 2] = ((pTemp[i * 64 + j] / 0x11) & 0x0F) | ((pTemp[i * 64 + j + 1] / 0x11) << 4 & 0xF0);
				}
			}
			delete[] pTemp;
		}
		break;
	default:
		return 1;
	}
	return 0;
}

int deSwizzleBffnt(const UChar* a_pEnSwizzledBffntFileName, const UChar* a_pDeSwizzledBffntFileName)
{
	FILE* fp = UFopen(a_pEnSwizzledBffntFileName, USTR("rb"), false);
	if (fp == nullptr)
	{
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	u32 uFontSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	u8* pFont = new u8[uFontSize];
	fread(pFont, 1, uFontSize, fp);
	fclose(fp);
	SBinaryFileHeader* pBinaryFileHeader = reinterpret_cast<SBinaryFileHeader*>(pFont);
	if (pBinaryFileHeader->Signature != kConstSignatureFONT)
	{
		delete[] pFont;
		return 1;
	}
	if (pBinaryFileHeader->ByteOrder != 0xFEFF)
	{
		delete[] pFont;
		return 1;
	}
	SFontTextureGlyph* pFontTextureGlyph = nullptr;
	u32 uOffset = pBinaryFileHeader->HeaderSize;
	while (uOffset < uFontSize)
	{
		SBinaryBlockHeader* pBinaryBlockHeader = reinterpret_cast<SBinaryBlockHeader*>(pFont + uOffset);
		switch (pBinaryBlockHeader->Kind)
		{
		case kConstSignatureFINF:
			{
				SFontInformation* pFontInformation = reinterpret_cast<SFontInformation*>(pBinaryBlockHeader + 1);
				u32 uFontTextureGlyphOffset = pFontInformation->PGlyph;
				pFontTextureGlyph = reinterpret_cast<SFontTextureGlyph*>(pFont + uFontTextureGlyphOffset);
			}
			break;
		case kConstSignatureTGLP:
			{
				if (pFontTextureGlyph == nullptr)
				{
					pFontTextureGlyph = reinterpret_cast<SFontTextureGlyph*>(pBinaryBlockHeader + 1);
				}
				else if (pFontTextureGlyph != reinterpret_cast<SFontTextureGlyph*>(pBinaryBlockHeader + 1))
				{
					delete[] pFont;
					return 1;
				}
				if (decode(pFont + pFontTextureGlyph->SheetImage, pFontTextureGlyph->SheetWidth, pFontTextureGlyph->SheetHeight * pFontTextureGlyph->SheetNum, pFontTextureGlyph->SheetFormat) != 0)
				{
					delete[] pFont;
					return 1;
				}
			}
			break;
		case kConstSignatureCGLP:
		case kConstSignatureCWDH:
		case kConstSignatureCMAP:
		case kConstSignatureGLGR:
		case kConstSignatureHTGL:
			break;
		default:
			delete[] pFont;
			return 1;
		}
		uOffset += pBinaryBlockHeader->Size;
	}
	if (pFontTextureGlyph == nullptr)
	{
		delete[] pFont;
		return 1;
	}
	fp = UFopen(a_pDeSwizzledBffntFileName, USTR("wb"), false);
	if (fp == nullptr)
	{
		delete[] pFont;
		return 1;
	}
	fwrite(pFont, 1, uFontSize, fp);
	fclose(fp);
	delete[] pFont;
	return 0;
}

int enSwizzleBffnt(const UChar* a_pEnSwizzledBffntFileName, const UChar* a_pDeSwizzledBffntFileName)
{
	FILE* fp = UFopen(a_pDeSwizzledBffntFileName, USTR("rb"), false);
	if (fp == nullptr)
	{
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	u32 uFontSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	u8* pFont = new u8[uFontSize];
	fread(pFont, 1, uFontSize, fp);
	fclose(fp);
	SBinaryFileHeader* pBinaryFileHeader = reinterpret_cast<SBinaryFileHeader*>(pFont);
	if (pBinaryFileHeader->Signature != kConstSignatureFONT)
	{
		delete[] pFont;
		return 1;
	}
	if (pBinaryFileHeader->ByteOrder != 0xFEFF)
	{
		delete[] pFont;
		return 1;
	}
	SFontTextureGlyph* pFontTextureGlyph = nullptr;
	u32 uOffset = pBinaryFileHeader->HeaderSize;
	while (uOffset < uFontSize)
	{
		SBinaryBlockHeader* pBinaryBlockHeader = reinterpret_cast<SBinaryBlockHeader*>(pFont + uOffset);
		switch (pBinaryBlockHeader->Kind)
		{
		case kConstSignatureFINF:
			{
				SFontInformation* pFontInformation = reinterpret_cast<SFontInformation*>(pBinaryBlockHeader + 1);
				u32 uFontTextureGlyphOffset = pFontInformation->PGlyph;
				pFontTextureGlyph = reinterpret_cast<SFontTextureGlyph*>(pFont + uFontTextureGlyphOffset);
			}
			break;
		case kConstSignatureTGLP:
			{
				if (pFontTextureGlyph == nullptr)
				{
					pFontTextureGlyph = reinterpret_cast<SFontTextureGlyph*>(pBinaryBlockHeader + 1);
				}
				else if (pFontTextureGlyph != reinterpret_cast<SFontTextureGlyph*>(pBinaryBlockHeader + 1))
				{
					delete[] pFont;
					return 1;
				}
				if (encode(pFont + pFontTextureGlyph->SheetImage, pFontTextureGlyph->SheetWidth, pFontTextureGlyph->SheetHeight * pFontTextureGlyph->SheetNum, pFontTextureGlyph->SheetFormat) != 0)
				{
					delete[] pFont;
					return 1;
				}
			}
			break;
		case kConstSignatureCGLP:
		case kConstSignatureCWDH:
		case kConstSignatureCMAP:
		case kConstSignatureGLGR:
		case kConstSignatureHTGL:
			break;
		default:
			delete[] pFont;
			return 1;
		}
		uOffset += pBinaryBlockHeader->Size;
	}
	if (pFontTextureGlyph == nullptr)
	{
		delete[] pFont;
		return 1;
	}
	fp = UFopen(a_pEnSwizzledBffntFileName, USTR("wb"), false);
	if (fp == nullptr)
	{
		delete[] pFont;
		return 1;
	}
	fwrite(pFont, 1, uFontSize, fp);
	fclose(fp);
	delete[] pFont;
	return 0;
}

int UMain(int argc, UChar* argv[])
{
	if (argc != 4)
	{
		return 1;
	}
	if (UCslen(argv[1]) == 1)
	{
		switch (*argv[1])
		{
		case USTR('D'):
		case USTR('d'):
			return deSwizzleBffnt(argv[2], argv[3]);
		case USTR('E'):
		case USTR('e'):
			return enSwizzleBffnt(argv[2], argv[3]);
		default:
			break;
		}
	}
	return 1;
}
