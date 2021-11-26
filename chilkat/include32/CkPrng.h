// CkPrng.h: interface for the CkPrng class.
//
//////////////////////////////////////////////////////////////////////

// This header is generated for Chilkat v9.5.0

#ifndef _CkPrng_H
#define _CkPrng_H
	
#include "chilkatDefs.h"

#include "CkString.h"
#include "CkMultiByteBase.h"

class CkByteData;



#if !defined(__sun__) && !defined(__sun)
#pragma pack (push, 8)
#endif
 

// CLASS: CkPrng
class CK_VISIBLE_PUBLIC CkPrng  : public CkMultiByteBase
{
    private:

	// Don't allow assignment or copying these objects.
	CkPrng(const CkPrng &);
	CkPrng &operator=(const CkPrng &);

    public:
	CkPrng(void);
	virtual ~CkPrng(void);

	static CkPrng *createNew(void);
	void CK_VISIBLE_PRIVATE inject(void *impl);

	// May be called when finished with the object to free/dispose of any
	// internal resources held by the object. 
	void dispose(void);

	

	// BEGIN PUBLIC INTERFACE

	// ----------------------
	// Properties
	// ----------------------
	// The name of the PRNG selected. Currently, the default and only possible value is
	// "fortuna". See the links below for information about the Fortuna PRNG.
	// 
	// Note: Because "fortuna" is the only valid choice, assigning this property to a
	// different value will always be ignored (until alternative PRNG algorithms are
	// added in the future).
	// 
	void get_PrngName(CkString &str);
	// The name of the PRNG selected. Currently, the default and only possible value is
	// "fortuna". See the links below for information about the Fortuna PRNG.
	// 
	// Note: Because "fortuna" is the only valid choice, assigning this property to a
	// different value will always be ignored (until alternative PRNG algorithms are
	// added in the future).
	// 
	const char *prngName(void);
	// The name of the PRNG selected. Currently, the default and only possible value is
	// "fortuna". See the links below for information about the Fortuna PRNG.
	// 
	// Note: Because "fortuna" is the only valid choice, assigning this property to a
	// different value will always be ignored (until alternative PRNG algorithms are
	// added in the future).
	// 
	void put_PrngName(const char *newVal);



	// ----------------------
	// Methods
	// ----------------------
	// Adds entropy to the PRNG (i.e. adds more seed material to the PRNG). Entropy can
	// be obtained by calling GetEntropy, or the application might have its own sources
	// for obtaining entropy. An application may continue to add entropy at desired
	// intervals. How the entropy is used depends on the PRNG algorithm. For Fortuna,
	// the entropy is added to the internal entropy pools and used when internal
	// automatic reseeding occurs.
	// 
	// An application may add non-random entropy for testing purposes. This allows for
	// the reproduction of the same pseudo-random number sequence for testing and
	// debugging purposes.
	// 
	// The entropy bytes are passed in ARG1 using the binary encoding specified in
	// ARG2. Binary encodings can be "hex", "base64", etc. See the link below for
	// supported binary encodings.
	// 
	bool AddEntropy(const char *entropy, const char *encoding);


	// Adds entropy to the PRNG (i.e. adds more seed material to the PRNG). Entropy can
	// be obtained by calling GetEntropy, or the application might have its own sources
	// for obtaining entropy. An application may continue to add entropy at desired
	// intervals. How the entropy is used depends on the PRNG algorithm. For Fortuna,
	// the entropy is added to the internal entropy pools and used when internal
	// automatic reseeding occurs.
	// 
	// An application may add non-random entropy for testing purposes. This allows for
	// the reproduction of the same pseudo-random number sequence for testing and
	// debugging purposes.
	// 
	bool AddEntropyBytes(CkByteData &entropy);


	// Exports all accumulated entropy and returns it in a base64 encoded string.
	// (Internally the entropy pools are re-hashed so that a hacker cannot determine
	// the state of the PRNG even if the exported entropy was obtained.) When a system
	// restarts it can import what was previously exported by calling ImportEntropy.
	// This ensures an adequate amount of entropy is immediately available when first
	// generating random bytes.
	// 
	// For example, an application could persist the exported entropy to a database or
	// file. When the application starts again, it could import the persisted entropy,
	// add some entropy from a system source (via the GetEntropy/AddEntropy methods),
	// and then begin generating random data.
	// 
	bool ExportEntropy(CkString &outStr);

	// Exports all accumulated entropy and returns it in a base64 encoded string.
	// (Internally the entropy pools are re-hashed so that a hacker cannot determine
	// the state of the PRNG even if the exported entropy was obtained.) When a system
	// restarts it can import what was previously exported by calling ImportEntropy.
	// This ensures an adequate amount of entropy is immediately available when first
	// generating random bytes.
	// 
	// For example, an application could persist the exported entropy to a database or
	// file. When the application starts again, it could import the persisted entropy,
	// add some entropy from a system source (via the GetEntropy/AddEntropy methods),
	// and then begin generating random data.
	// 
	const char *exportEntropy(void);

	// Generates and returns ARG1 random bytes in encoded string form. The binary
	// encoding is specified by ARG2, and can be "hex", "base64", etc. (See the link
	// below for supported binary encodings.)
	// 
	// Important: If no entropy was explicitly added prior to first call to generate
	// random bytes, then 32 bytes of entropy (from the system source, such as
	// /dev/random) are automatically added to seed the PRNG.
	// 
	bool GenRandom(int numBytes, const char *encoding, CkString &outStr);

	// Generates and returns ARG1 random bytes in encoded string form. The binary
	// encoding is specified by ARG2, and can be "hex", "base64", etc. (See the link
	// below for supported binary encodings.)
	// 
	// Important: If no entropy was explicitly added prior to first call to generate
	// random bytes, then 32 bytes of entropy (from the system source, such as
	// /dev/random) are automatically added to seed the PRNG.
	// 
	const char *genRandom(int numBytes, const char *encoding);

	// Generates and returns ARG1 random bytes.
	// 
	// Important: If no entropy was explicitly added prior to first call to generate
	// random bytes, then 32 bytes of entropy (from the system source, such as
	// /dev/random) are automatically added to seed the PRNG.
	// 
	bool GenRandomBytes(int numBytes, CkByteData &outBytes);


	// Reads real entropy bytes from a system entropy source and returns as an encoded
	// string. On Linux/Unix based systems, including MAC OS X, this is accomplished by
	// reading /dev/random. On Windows systems, it uses the Microsoft Cryptographic
	// Service Provider's CryptGenRandom method.
	// 
	// It is recommended that no more than 32 bytes of entropy should be retrieved to
	// initially seed a PRNG. Larger amounts of entropy are fairly useless. However, an
	// app is free to periodically add bits of entropy to a long-running PRNG as it
	// sees fit.
	// 
	// The ARG2 specifies the encoding to be used. It can be "hex", "base64", or many
	// other possibilities. See the link below.
	// 
	bool GetEntropy(int numBytes, const char *encoding, CkString &outStr);

	// Reads real entropy bytes from a system entropy source and returns as an encoded
	// string. On Linux/Unix based systems, including MAC OS X, this is accomplished by
	// reading /dev/random. On Windows systems, it uses the Microsoft Cryptographic
	// Service Provider's CryptGenRandom method.
	// 
	// It is recommended that no more than 32 bytes of entropy should be retrieved to
	// initially seed a PRNG. Larger amounts of entropy are fairly useless. However, an
	// app is free to periodically add bits of entropy to a long-running PRNG as it
	// sees fit.
	// 
	// The ARG2 specifies the encoding to be used. It can be "hex", "base64", or many
	// other possibilities. See the link below.
	// 
	const char *getEntropy(int numBytes, const char *encoding);
	// Reads real entropy bytes from a system entropy source and returns as an encoded
	// string. On Linux/Unix based systems, including MAC OS X, this is accomplished by
	// reading /dev/random. On Windows systems, it uses the Microsoft Cryptographic
	// Service Provider's CryptGenRandom method.
	// 
	// It is recommended that no more than 32 bytes of entropy should be retrieved to
	// initially seed a PRNG. Larger amounts of entropy are fairly useless. However, an
	// app is free to periodically add bits of entropy to a long-running PRNG as it
	// sees fit.
	// 
	// The ARG2 specifies the encoding to be used. It can be "hex", "base64", or many
	// other possibilities. See the link below.
	// 
	const char *entropy(int numBytes, const char *encoding);


	// Reads and returns real entropy bytes from a system entropy source. On Linux/Unix
	// based systems, including MAC OS X, this is accomplished by reading /dev/random.
	// On Windows systems, it uses the Microsoft Cryptographic Service Provider's
	// CryptGenRandom method.
	// 
	// It is recommended that no more than 32 bytes of entropy should be retrieved to
	// initially seed a PRNG. Larger amounts of entropy are fairly useless. However, an
	// app is free to periodically add bits of entropy to a long-running PRNG as it
	// sees fit.
	// 
	bool GetEntropyBytes(int numBytes, CkByteData &outBytes);


	// Imports entropy from previously exported entropy. See the ExportEntropy method
	// for more information.
	bool ImportEntropy(const char *entropy);


	// Generates and returns a random integer between ARG1 and ARG2 (inclusive). For
	// example, if ARG1 is 4 and ARG2 is 8, then random integers in the range 4, 5, 6,
	// 7, 8 are returned.
	int RandomInt(int low, int high);


	// Generates and returns a random password of a specified length. If ARG2 is
	// true, the generated password will contain at least one digit (0-9). If ARG3 is
	// true, then generated password will contain both lowercase and uppercase
	// USASCII chars (a-z and A-Z). If ARG4 is a non-empty string, it contains the set
	// of non-alphanumeric characters, one of which must be included in the password.
	// For example, ARG4 might be the string "!@#$%". If ARG5 is a non-empty string, it
	// contains chars that should be excluded from the password. A typical need would
	// be to exclude chars that appear similar to others, such as i, l, 1, L, o, 0, O.
	bool RandomPassword(int length, bool mustIncludeDigit, bool upperAndLowercase, const char *mustHaveOneOf, const char *excludeChars, CkString &outStr);

	// Generates and returns a random password of a specified length. If ARG2 is
	// true, the generated password will contain at least one digit (0-9). If ARG3 is
	// true, then generated password will contain both lowercase and uppercase
	// USASCII chars (a-z and A-Z). If ARG4 is a non-empty string, it contains the set
	// of non-alphanumeric characters, one of which must be included in the password.
	// For example, ARG4 might be the string "!@#$%". If ARG5 is a non-empty string, it
	// contains chars that should be excluded from the password. A typical need would
	// be to exclude chars that appear similar to others, such as i, l, 1, L, o, 0, O.
	const char *randomPassword(int length, bool mustIncludeDigit, bool upperAndLowercase, const char *mustHaveOneOf, const char *excludeChars);

	// Generates and returns a random string that may contain digits (0-9), lowercase
	// ASCII (a-z) , and uppercase ASCII (A-Z). To include numeric digits, set ARG2
	// equal to true. To include lowercase ASCII, set ARG3 equal to true. To
	// include uppercase ASCII, set ARG4 equal to true. The length of the string to
	// be generated is specified by ARG1.
	bool RandomString(int length, bool bDigits, bool bLower, bool bUpper, CkString &outStr);

	// Generates and returns a random string that may contain digits (0-9), lowercase
	// ASCII (a-z) , and uppercase ASCII (A-Z). To include numeric digits, set ARG2
	// equal to true. To include lowercase ASCII, set ARG3 equal to true. To
	// include uppercase ASCII, set ARG4 equal to true. The length of the string to
	// be generated is specified by ARG1.
	const char *randomString(int length, bool bDigits, bool bLower, bool bUpper);





	// END PUBLIC INTERFACE


};
#if !defined(__sun__) && !defined(__sun)
#pragma pack (pop)
#endif


	
#endif
