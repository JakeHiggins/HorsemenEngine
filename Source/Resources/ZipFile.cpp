#include "HorsemanStd.h"
#include "ZipFile.h"

// Referenced from http://www.flipcode.com/archives/Zip_File_Loader.shtml
bool ZipFile::Init(const char* resourceFile) {

	End();
	printf("Reading %s\n", resourceFile);
	fopen_s(&m_pFile, resourceFile, "r");
	
	if (!m_pFile) {
		printf("[ZipInitError (%s)] Failed to read file.\n", resourceFile);
		return false;
	}

	TZipDirHeader dh;

	fseek(m_pFile, -(int)sizeof(dh), SEEK_END);
	long dhOffset = ftell(m_pFile);
	memset(&dh, 0, sizeof(dh));
	fread(&dh, sizeof(dh), 1, m_pFile);

	if (dh.sig != TZipDirHeader::SIGNATURE) {
		printf("[ZipInitError (%s)] TZipDirHeader signature mismatch [GOT: %s, EXPECTED: %s].\n", resourceFile, dh.sig, TZipDirHeader::SIGNATURE);
		return false;
	}

	// Go to the beginning of the directory
	fseek(m_pFile, dhOffset - dh.dirSize, SEEK_SET);

	// Allocate the data buffer and read the whole thing
	m_pDirData = new char[dh.dirSize + dh.nDirEntries * sizeof(*m_papDir)];
	if (!m_pDirData) {
		printf("[ZipInitError (%s)] Failed to allocate directory data.\n", resourceFile);
		return false;
	}
	memset(m_pDirData, 0, dh.dirSize + dh.nDirEntries * sizeof(*m_papDir));
	fread(m_pDirData, dh.dirSize, 1, m_pFile);

	// Process each entry
	char* pfh = m_pDirData;
	m_papDir = (const TZipDirFileHeader**)(m_pDirData + dh.dirSize);

	bool ok = true;
	for (int i = 0; i < dh.nDirEntries && ok; i++) {
		TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;

		// Store the address of the nth file for quick access
		m_papDir[i] = &fh;

		// Check directory entry for integrity
		if (fh.sig != TZipDirFileHeader::SIGNATURE) {
			printf("[ZipInitError (%s)] TZipDirFileHeader signature mismatch [GOT: %s, EXPECTED: %s].\n", resourceFile, fh.sig, TZipDirFileHeader::SIGNATURE);
			ok = false;
		}
		else {
			pfh += sizeof(fh);

			// Convert UNIX slashes to DOS backslashes.
			for (int j = 0; j < fh.fnameLen; j++)
				if (pfh[j] == '/')
					pfh[j] = '\\';

			pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
		}
	}

	if (!ok) {
		delete[] m_pDirData;
	}
	else {
		m_Entries = dh.nDirEntries;
	}

	return ok;
}

void ZipFile::End() {
	delete[] m_pDirData;
	m_Entries = 0;
}

char* ZipFile::GetFilename(int i) const {
	if (i < 0 || i >= m_Entries) {
		return '\0';
	}

	char name[1000];
	memcpy(name, m_papDir[i]->GetName(), m_papDir[i]->fnameLen);
	name[m_papDir[i]->fnameLen] = '\0';

	return name;
}

int ZipFile::GetFileLen(int i) const {
	if (i < 0 || i >= m_Entries) {
		return -1;
	}

	return m_papDir[i]->ucSize;
}

bool ZipFile::ReadFile(int i, void * pBuf)
{
	return false;
}

bool ZipFile::ReadLargeFile(int i, void * pBuf, void(*progressCallback)(int, bool &))
{
	return false;
}
