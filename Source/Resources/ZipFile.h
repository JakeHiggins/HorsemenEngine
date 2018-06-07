#ifndef ZIPFILE_H
#define ZIPFILE_H

class ZipFile {
	int m_Entries;
	FILE* m_pFile;
	char* m_pDirData;

public:
	ZipFile() { m_Entries = 0; m_pFile = NULL; m_pDirData = NULL; }
	virtual ~ZipFile() { End(); fclose(m_pFile); }

	bool Init(const char* resourceFile);
	void End();

	int GetNumFiles() const { return m_Entries; }
	char* GetFilename(int i) const;
	int GetFileLen(int i) const;
	bool ReadFile(int i, void *pBuf);

	bool ReadLargeFile(int i, void *pBuf, void(*progressCallback)(int, bool &));
	// std::optional<int> Find(const std::string &path) const;

	ZipContentsMap m_ZipContentsMap;

	READONLY_PROPERTY(int, Entries);
	GET(Entries) { return m_Entries; }

private:
	struct TZipDirHeader;
	struct TZipDirFileHeader;
	struct TZipLocalHeader;

	const TZipDirFileHeader **m_papDir;
};

#pragma pack(1)
struct ZipFile::TZipLocalHeader {
	enum { SIGNATURE = 0x04034b50 };

	dword	sig;
	word	version;
	word	flag;
	word	compression;
	word	modType;
	word	modDate;
	dword	crc32;
	dword	cSize;
	dword	ucSize;
	word	fnameLen;
	word	xtraLen;
};

struct ZipFile::TZipDirHeader {
	enum { SIGNATURE = 0x06054b50 };

	dword	sig;
	word	nDisk;
	word	nStartDisk;
	word	nDirEntries;
	word	totalDirEntries;
	dword	dirSize;
	dword	dirOffset;
	word	cmntLen;
};

struct ZipFile::TZipDirFileHeader {
	enum { SIGNATURE = 0x02014b50 };

	dword	sig;
	word	verMade;
	word	verNeeded;
	word	flag;
	word	compression;
	word	modTime;
	word	modDate;
	dword	crc32;
	dword	cSize;
	dword	ucSize;
	word	fnameLen;
	word	xtraLen;
	word	cmntLen;
	word	diskStart;
	word	intAttr;
	dword	extAttr;
	dword	hdrOffset;

	char* GetName() const { return (char*)(this + 1); }
	char* GetExtra() const { return GetName() + fnameLen; }
	char* GetComment() const { return GetExtra() + xtraLen; }
};
#pragma pack()

#endif