/*
 * base64 encode/decode library
 */
#include <stdint.h>

#include <iostream>
#include <fstream>
#include <Base64.h>
#include <string.h>

namespace webtoken {

#define BASE64_SAFEREAD(aInPtr, aInOffset, aInMax) (((aInOffset) < aInMax) ? aInPtr[aInOffset]:0)

    Base64::Base64(const uint8_t* aInByteStream, const uint32_t aInLength)
    {
        initializeLookupTables();

        encodedLength = estimateEncodedLength(aInLength);
        encodedData = new uint8_t[encodedLength + 1];
        encode(aInByteStream, aInLength);
    }

    Base64::Base64(const Base64* aInBase64)
    {
        initializeLookupTables();

        encodedLength = aInBase64->getLength();
        encodedData = new uint8_t[encodedLength+1];
        memcpy(encodedData, aInBase64->encodedData, encodedLength+1);
    }

    Base64::Base64(void) : encodedLength(0), encodedData(NULL)
    {
       initializeLookupTables();
    }

    const uint32_t Base64::encode (const uint8_t *aInByteStream,
                                   const uint32_t aInLength)
    {
        uint8_t *lPtr;
        uint32_t lSrcIter;
        int32_t lDstIter;
        uint64_t lBuf64;

        lPtr = encodedData;

        for (lSrcIter = 0; lSrcIter < aInLength; lSrcIter += 3) {
            if ((lSrcIter+1) > aInLength) {
                lBuf64 = aInByteStream[lSrcIter]<<16 | BASE64_SAFEREAD(aInByteStream, lSrcIter+1, aInLength)<<8;
            } else if ((lSrcIter+2) > aInLength) {
                lBuf64 = aInByteStream[lSrcIter]<<16;
            } else {
                lBuf64 = aInByteStream[lSrcIter]<<16 | BASE64_SAFEREAD(aInByteStream, lSrcIter+1, aInLength)<<8 |
                    BASE64_SAFEREAD(aInByteStream, lSrcIter+2, aInLength);
            }
            for (lDstIter = 3; lDstIter >= 0; lDstIter--) {
                lPtr[lDstIter] = encodeLookupTable[lBuf64 & 0x3f];
                lBuf64 = lBuf64 >> 6;
            }

            lPtr += 4;
        }

        switch(aInLength % 3) {

        case 0:
            encodedLength = (aInLength/3) * 4;
            break;
        case 1:
            encodedLength = 4 + (aInLength/3) * 4;
            encodedData[encodedLength-1] = '=';
            encodedData[encodedLength-2] = '=';
            break;
        case 2:
            encodedLength = 4 + (aInLength/3) * 4;
            encodedData[encodedLength-1] = '=';
            break;
        }

        encodedData[encodedLength] = 0;
        return 1;
    }

    /*
     * Caller must delete[] the buffer passed back
     */
    void Base64::decode (uint8_t **aOutBuf,
                         uint32_t& aOutLength) const
    {
        uint32_t lSrcIter;
        uint32_t lDstIter;
        uint8_t *lBuf = new uint8_t[encodedLength];
        for (lSrcIter = 0, lDstIter = 0; lSrcIter < encodedLength; lSrcIter += 4, lDstIter += 3) {
            decodeBlock(encodedData + lSrcIter, lBuf + lDstIter);
        }

        aOutLength = lDstIter;
        *aOutBuf = lBuf;
    }
    void Base64::initializeLookupTables (void)
    {
        uint8_t iter;

        if (lookupTablesInitialized)
            return;

        for (iter = 0; iter < 64; iter++) {
            encodeLookupTable[iter] = encodeChar(iter);
        }

        for (iter = 'A'; iter <= 'Z'; iter++) {
            decodeLookupTable[iter] = decodeChar(iter);
        }
        for (iter = 'a'; iter <= 'z'; iter++) {
            decodeLookupTable[iter] = decodeChar(iter);
        }
        for (iter = '0'; iter <= '9'; iter++) {
            decodeLookupTable[iter] = decodeChar(iter);
        }
        decodeLookupTable['+'] = decodeChar('+');
        decodeLookupTable['/'] = decodeChar('/');
        lookupTablesInitialized = 1;
    }

    void Base64::decodeBlock (const uint8_t *aInBlock,
                              uint8_t *aOutTriBlock) const {

        unsigned long long int lBuf64;

        lBuf64 = decodeChar(aInBlock[0]) << 18;
        lBuf64 |= decodeChar(aInBlock[1]) << 12;
        lBuf64 |= decodeChar(aInBlock[2]) << 6;
        lBuf64 |= decodeChar(aInBlock[3]);

        aOutTriBlock[0] = lBuf64 >> 16;
        aOutTriBlock[1] = (lBuf64 >> 8) & 0xff;
        aOutTriBlock[2] = lBuf64 & 0xff;
    }

    uint8_t Base64::encodeChar(const uint8_t aInX) const {
        /* Slow conditional checks, but this is only for initial generation */
        uint8_t lRetVal;
        lRetVal = ((aInX<26) ? (aInX + 'A'):
                   ((aInX < 52) ? (aInX + 'a' - 26):
                    ((aInX < 62)? ( aInX + '0' - 52):
                     ((aInX == 62) ? '+':'/'))));
        return lRetVal;
    }

    uint8_t Base64::decodeChar (const uint8_t aInX) const {
        /* Slow conditional checks, but this is only for initial generation */
        if (aInX >= 'A' && aInX <= 'Z')
            return aInX - 'A';
        if (aInX >= 'a' && aInX <= 'z')
            return 26 + aInX - 'a';
        if (aInX >= '0' && aInX <= '9')
            return 52 + aInX - '0';
        if (aInX == '+')
            return 62;
        return 63;
    }

    const uint32_t Base64::estimateEncodedLength (const uint32_t aInLength) const {

        uint32_t lLen = aInLength/3;
        if (aInLength%3) {
            lLen++;
        }
        return (lLen*4);
    }

    const uint32_t Base64::estimateDecodedLength (const uint32_t aInLength) const {
        uint32_t lLen = aInLength/4;
        if (aInLength%4) {
            lLen++;
        }
        return (lLen*3);
    }

    Base64::~Base64()
    {
        if ( encodedData )
        {
            delete[] encodedData;
        }
    }

    uint8_t Base64::encodeLookupTable[64] = { 0 };
    uint8_t Base64::decodeLookupTable[256] = { 0 };
    int Base64::lookupTablesInitialized = 0;
}
