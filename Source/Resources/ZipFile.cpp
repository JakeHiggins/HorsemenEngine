#include "HorsemanStd.h"
#include "ZipFile.h"

bool ZipFile::Init(const char* resourceFile) {

	End();
	printf("Reading %s\n", resourceFile);
	fopen_s(&m_pFile, resourceFile, "r");
	
	if (!m_pFile) {
		printf("%s could not be read\n", resourceFile);
		return false;
	}

	TZipDirHeader dh;

	fseek(m_pFile, -(int)sizeof(dh), SEEK_END);
	long dhOffset = ftell(m_pFile);
	memset(&dh, 0, sizeof(dh));
	fread(&dh, sizeof(dh), 1, m_pFile);

	if (dh.sig != TZipDirHeader::SIGNATURE) {
		return false;
	}

	return true;
}

void ZipFile::End() {
	delete[] m_pDirData;
	m_Entries = 0;
}

string ZipFile::GetFilename(int i) const
{
	return string();
}

int ZipFile::GetFileLen(int i) const
{
	return 0;
}

bool ZipFile::ReadFile(int i, void * pBuf)
{
	return false;
}

bool ZipFile::ReadLargeFile(int i, void * pBuf, void(*progressCallback)(int, bool &))
{
	return false;
}
