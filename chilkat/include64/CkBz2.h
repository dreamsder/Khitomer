// CkBz2.h: interface for the CkBz2 class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkBz2_H
#define _CkBz2_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkClassWithCallbacks.h"

class CkTask;
class CkByteData;
class CkBaseProgress;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkBz2
class CK_VISIBLE_PUBLIC CkBz2  : public CkClassWithCallbacks
{
    private:

	// Don't allow assignment or copying these objects.
	CkBz2(const CkBz2 &);
	CkBz2 &operator=(const CkBz2 &);

    public:
	CkBz2(void);
	virtual ~CkBz2(void);

	static CkBz2 *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	CkBaseProgress *get_EventCallbackObject(void) const;
	void put_EventCallbackObject(CkBaseProgress *progress);


	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------

	int get_HeartbeatMs(void);

	void put_HeartbeatMs(int newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Compresses a file to create a BZip2 compressed file (.bz2).
	bool CompressFile(const char *inFilename, const char *toPath);

	// Compresses a file to create a BZip2 compressed file (.bz2).
	CkTask *CompressFileAsync(const char *inFilename, const char *toPath);


	// BZip2 compresses a file to an in-memory image of a .bz2 file.
	bool CompressFileToMem(const char *inFilename, CkByteData &outBytes);

	// BZip2 compresses a file to an in-memory image of a .bz2 file.
	CkTask *CompressFileToMemAsync(const char *inFilename);


	// BZip2 compresses and creates a .bz2 file from in-memory data.
	bool CompressMemToFile(CkByteData &inData, const char *toPath);

	// BZip2 compresses and creates a .bz2 file from in-memory data.
	CkTask *CompressMemToFileAsync(CkByteData &inData, const char *toPath);


	// Compresses in-memory data to an in-memory image of a .bz2 file.
	bool CompressMemory(CkByteData &inData, CkByteData &outBytes);

	// Compresses in-memory data to an in-memory image of a .bz2 file.
	CkTask *CompressMemoryAsync(CkByteData &inData);


	// Unzips a .bz2 file.
	bool UncompressFile(const char *inFilename, const char *toPath);

	// Unzips a .bz2 file.
	CkTask *UncompressFileAsync(const char *inFilename, const char *toPath);


	// Unzips a .bz2 file directly to memory.
	bool UncompressFileToMem(const char *inFilename, CkByteData &outBytes);

	// Unzips a .bz2 file directly to memory.
	CkTask *UncompressFileToMemAsync(const char *inFilename);


	// Unzips from an in-memory image of a .bz2 file to a file.
	bool UncompressMemToFile(CkByteData &inData, const char *toPath);

	// Unzips from an in-memory image of a .bz2 file to a file.
	CkTask *UncompressMemToFileAsync(CkByteData &inData, const char *toPath);


	// Unzips from an in-memory image of a .bz2 file directly into memory.
	bool UncompressMemory(CkByteData &inData, CkByteData &outBytes);

	// Unzips from an in-memory image of a .bz2 file directly into memory.
	CkTask *UncompressMemoryAsync(CkByteData &inData);


	// Unlocks the component allowing for the full functionality to be used. If a
	// permanent (purchased) unlock code is passed, there is no expiration. Any other
	// string automatically begins a fully-functional 30-day trial the first time
	// UnlockComponent is called.
	bool UnlockComponent(const char *regCode);






	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
