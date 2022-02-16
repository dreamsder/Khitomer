#include "crearclavecifrada.h"

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

#include <QString>
#include <QFile>


#include <QDebug>



#include <../json/base64_nibbleandahalf.h>


///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////

//#define PADDING RSA_PKCS1_OAEP_PADDING
#define PADDING RSA_PKCS1_PADDING
//#define PADDING RSA_NO_PADDING


RSA* loadPUBLICKeyFromString( const char* publicKeyStr )
{

    BIO* bio = BIO_new_mem_buf( (void*)publicKeyStr, -1 );

    BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ;

    // Load the RSA key from the BIO
    RSA* rsaPubKey = PEM_read_bio_RSA_PUBKEY( bio, NULL, NULL, NULL ) ;
    if( !rsaPubKey )
        printf( "ERROR: No se puede cargar la PUBLIC KEY!  PEM_read_bio_RSA_PUBKEY FAILED: %s\n", ERR_error_string( ERR_get_error(), NULL ) ) ;

    BIO_free( bio ) ;
    return rsaPubKey ;
}


unsigned char* rsaEncrypt( RSA *pubKey, const unsigned char* str, int dataSize, int *resultLen )
{


    unsigned char* error=0x0;
    int rsaLen=0;

    if(pubKey!=0x0){
        try {
            rsaLen = RSA_size( pubKey ) ;
        } catch (...) {

        }

        unsigned char* ed = (unsigned char*)malloc( rsaLen ) ;

        // RSA_public_encrypt() returns the size of the encrypted data
        // (i.e., RSA_size(rsa)). RSA_private_decrypt()
        // returns the size of the recovered plaintext.
        *resultLen = RSA_public_encrypt( dataSize, (const unsigned char*)str, ed, pubKey, PADDING ) ;

        if( *resultLen == -1 )
            printf("ERROR: RSA_public_encrypt: %s\n", ERR_error_string(ERR_get_error(), NULL));

        return ed ;
    }else{
        return error;
    }



}


// You may need to encrypt several blocks of binary data (each has a maximum size
// limited by pubKey).  You shoudn't try to encrypt more than
// RSA_LEN( pubKey ) bytes into some packet.
// returns base64( rsa encrypt( <<binary data>> ) )
// base64OfRsaEncrypted()
// base64StringOfRSAEncrypted
// rsaEncryptThenBase64
char* rsaEncryptThenBase64( RSA *pubKey, unsigned char* binaryData, int binaryDataLen, int *outLen )
{
    int encryptedDataLen ;

    // RSA encryption with public key
    unsigned char* encrypted = rsaEncrypt( pubKey, binaryData, binaryDataLen, &encryptedDataLen ) ;

    if(encrypted!=0x0){
        // To base 64
        int asciiBase64EncLen ;

        char* asciiBase64Enc = base64_NIBBLEANDAHALF(encrypted, encryptedDataLen, &asciiBase64EncLen ) ;

        // Destroy the encrypted data (we are using the base64 version of it)
        free( encrypted ) ;

        // Return the base64 version of the encrypted data
        return asciiBase64Enc ;
    }else{
        return "-1" ;
    }

}
///////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////////



CrearClaveCifrada::CrearClaveCifrada()
{
}


QString CrearClaveCifrada::retornoClave(QString archivoClave, QString username, QString passowrd){


    const char* publicKey=NULL;

    QFile publicKeyFile(archivoClave);

    if(publicKeyFile.open(QIODevice::ReadOnly)){

        publicKey = publicKeyFile.readAll();
        publicKeyFile.close();

        ERR_load_crypto_strings();

        QString usuario = "{\"username\":\""+username+"\",\"password\":\""+passowrd+"\"}";

        // String to encrypt, INCLUDING NULL TERMINATOR:
        int dataSize=usuario.length() ; // 128 for NO PADDING, __ANY SIZE UNDER 128 B__ for RSA_PKCS1_PADDING

        QByteArray ba = usuario.toLocal8Bit();
        unsigned char *resultParse = (unsigned char *)strdup(ba.constData());

        // LOAD PUBLIC KEY
        RSA *pubKey = loadPUBLICKeyFromString( publicKey ) ;

        int asciiB64ELen ;
        const char* asciiB64E = rsaEncryptThenBase64( pubKey, resultParse, dataSize, &asciiB64ELen ) ;       

        //RSA_free( pubKey ) ; // free the public key when you are done all your encryption

        return asciiB64E;

    }else{
        return "-1";
    }

}
