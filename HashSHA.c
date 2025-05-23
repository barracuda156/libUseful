#include "HashSHA.h"

#ifdef USE_SHA1

#include "sha1.h"
#define SHA1LEN 20

void HashUpdateSHA1(HASH *Hash, const char *Data, int Len)
{
    sha1_process_bytes(Data,Len,(struct sha1_ctx *) Hash->Ctx);
}


HASH *HashCloneSHA1(HASH *Hash)
{
    HASH *NewHash;

    NewHash=(HASH *) calloc(1,sizeof(HASH));
    NewHash->Type=CopyStr(NewHash->Type,Hash->Type);
    NewHash->Ctx=(void *) calloc(1,sizeof(struct sha1_ctx));
    memcpy(NewHash->Ctx, Hash->Ctx, sizeof(struct sha1_ctx));

    return(NewHash);
}


int HashFinishSHA1(HASH *Hash, char **HashStr)
{
    int len;
    char *DigestBuff=NULL;

    DigestBuff=(char *) calloc(1,SHA1LEN+1);
    sha1_finish_ctx((struct sha1_ctx *) Hash->Ctx, DigestBuff);

    len=SHA1LEN;
    *HashStr=SetStrLen(*HashStr,len);
    memcpy(*HashStr,DigestBuff,len);

    DestroyString(DigestBuff);

    return(len);
}

#endif

#ifdef USE_SHA2

#include "sha2.h"

int HashFinishSHA256(HASH *Hash, char **HashStr)
{
    int len;
    char *DigestBuff=NULL;

    DigestBuff=(char *) calloc(1,SHA2_SHA256_DIGEST_LENGTH+1);
    SHA2_SHA256_Final((unsigned char *) DigestBuff, (SHA2_SHA256_CTX *) Hash->Ctx);

    len=SHA2_SHA256_DIGEST_LENGTH;
    *HashStr=SetStrLen(*HashStr,len);
    memcpy(*HashStr,DigestBuff,len);

    DestroyString(DigestBuff);

    return(len);
}


HASH *HashCloneSHA256(HASH *Hash)
{
    HASH *NewHash;

    NewHash=(HASH *) calloc(1,sizeof(HASH));
    NewHash->Type=CopyStr(NewHash->Type,Hash->Type);
    NewHash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA256_CTX));
    memcpy(NewHash->Ctx, Hash->Ctx, sizeof(SHA2_SHA256_CTX));

    return(NewHash);
}


void HashUpdateSHA256(HASH *Hash, const char *Data, int Len)
{
    SHA2_SHA256_Update((SHA2_SHA256_CTX *) Hash->Ctx, (unsigned char *) Data, Len);
}

int HashFinishSHA384(HASH *Hash, char **HashStr)
{
    int len;
    char *DigestBuff=NULL;

    DigestBuff=(char *) calloc(1,SHA2_SHA384_DIGEST_LENGTH+1);
    SHA2_SHA384_Final((unsigned char *) DigestBuff, (SHA2_SHA384_CTX *) Hash->Ctx);

    len=SHA2_SHA384_DIGEST_LENGTH;
    *HashStr=SetStrLen(*HashStr,len);
    memcpy(*HashStr,DigestBuff,len);

    DestroyString(DigestBuff);

    return(len);
}


void HashUpdateSHA384(HASH *Hash, const char *Data, int Len)
{
    SHA2_SHA384_Update((SHA2_SHA384_CTX *) Hash->Ctx, (unsigned char *) Data, Len);
}


HASH *HashCloneSHA384(HASH *Hash)
{
    HASH *NewHash;

    NewHash=(HASH *) calloc(1,sizeof(HASH));
    NewHash->Type=CopyStr(NewHash->Type,Hash->Type);
    NewHash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA384_CTX));
    memcpy(NewHash->Ctx, Hash->Ctx, sizeof(SHA2_SHA384_CTX));

    return(NewHash);
}



int HashFinishSHA512(HASH *Hash, char **HashStr)
{
    int len;
    char *DigestBuff=NULL;

    DigestBuff=(char *) calloc(1,SHA2_SHA512_DIGEST_LENGTH+1);
    SHA2_SHA512_Final((unsigned char *) DigestBuff, (SHA2_SHA512_CTX *) Hash->Ctx);

    len=SHA2_SHA512_DIGEST_LENGTH;
    *HashStr=SetStrLen(*HashStr,len);
    memcpy(*HashStr,DigestBuff,len);

    DestroyString(DigestBuff);

    return(len);
}


void HashUpdateSHA512(HASH *Hash, const char *Data, int Len)
{
    SHA2_SHA512_Update((SHA2_SHA512_CTX *) Hash->Ctx, (unsigned char *) Data, Len);
}


HASH *HashCloneSHA512(HASH *Hash)
{
    HASH *NewHash;

    NewHash=(HASH *) calloc(1,sizeof(HASH));
    NewHash->Type=CopyStr(NewHash->Type,Hash->Type);
    NewHash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA512_CTX));
    memcpy(NewHash->Ctx, Hash->Ctx, sizeof(SHA2_SHA512_CTX));

    return(NewHash);
}

#endif



int HashInitSHA(HASH *Hash, const char *Name, int Len)
{
    int RetVal=FALSE;

    switch (Len)
    {
    case 512:
#ifdef USE_SHA2
        Hash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA512_CTX));
        SHA2_SHA512_Init((SHA2_SHA512_CTX *) Hash->Ctx);
        Hash->Update=HashUpdateSHA512;
        Hash->Finish=HashFinishSHA512;
        Hash->Clone=HashCloneSHA512;
        RetVal=TRUE;
#endif
        break;

    case 384:
#ifdef USE_SHA2
        Hash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA384_CTX));
        SHA2_SHA384_Init((SHA2_SHA384_CTX *) Hash->Ctx);
        Hash->Update=HashUpdateSHA384;
        Hash->Finish=HashFinishSHA384;
        Hash->Clone=HashCloneSHA384;
        RetVal=TRUE;
#endif
        break;


    case 256:
#ifdef USE_SHA2
        Hash->Ctx=(void *) calloc(1,sizeof(SHA2_SHA256_CTX));
        SHA2_SHA256_Init((SHA2_SHA256_CTX *) Hash->Ctx);
        Hash->Update=HashUpdateSHA256;
        Hash->Finish=HashFinishSHA256;
        Hash->Clone=HashCloneSHA256;
        RetVal=TRUE;
#endif
        break;

    default:
#ifdef USE_SHA1
        Hash->Ctx=(void *) calloc(1,sizeof(struct sha1_ctx));
        sha1_init_ctx((struct sha1_ctx *) Hash->Ctx);
        Hash->Update=HashUpdateSHA1;
        Hash->Finish=HashFinishSHA1;
        Hash->Clone=HashCloneSHA1;
        RetVal=TRUE;
#endif
        break;
    }

    return(RetVal);
}


void HashRegisterSHA()
{
#ifdef USE_SHA1
    HashRegister("sha", 1, HashInitSHA);
    HashRegister("sha1", 1, HashInitSHA);
#endif


#ifdef USE_SHA2
    HashRegister("sha256", 256, HashInitSHA);
    HashRegister("sha384", 384, HashInitSHA);
    HashRegister("sha512", 512, HashInitSHA);
    HashRegister("sha-256", 256, HashInitSHA);
    HashRegister("sha-384", 384, HashInitSHA);
    HashRegister("sha-512", 512, HashInitSHA);
#endif
}
