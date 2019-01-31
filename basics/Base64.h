#ifndef __INS_BASE64_H__
#define __INS_BASE64_H__

#include <stdint.h>
#include <string.h>

/*
 * base64 encode/decode library
 */

namespace webtoken {

    class Base64 {
        /*
         * Instances of this class always represent an encoded Base64 string.
         *
         * Use the constructor to encode raw data into a base64 encoded string.
         * Use the factory method to create a Base64 object and store an already
         * encoded base64 string inside.
         */
    public:

        const uint32_t getLength(void) const {
            return encodedLength;
        }

        const uint8_t *getData(void) const {
            return encodedData;
        };

        void encodeByteStream (const uint8_t* aInByteStream,
                               const uint32_t aInLength,
                               Base64** aOutData) {

            Base64* lBase64 = new Base64(aInByteStream, aInLength);
            *aOutData = lBase64;
        }
        void decode (uint8_t **aOutBuf, uint32_t& aOutLength) const;

        virtual ~Base64();

        /* Constructor takes raw bytes and encodes them at initialization */
        Base64(const uint8_t* aInByteStream, const uint32_t aInLength);
        Base64(const Base64* aInBase64);

        /* Factory method takes a base64 string and stores it as-is without encoding */
        static Base64* factory(const uint8_t* aInBase64String, const uint32_t aInLength) {
            Base64 *lBase64 = new Base64();
            lBase64->encodedLength = aInLength;
            lBase64->encodedData = new uint8_t[aInLength+1];
            memcpy(lBase64->encodedData, aInBase64String, aInLength+1);
            return lBase64;
        }

    protected:
        Base64(void);

    private:
        const uint32_t estimateEncodedLength (const uint32_t aInLength) const;
        const uint32_t estimateDecodedLength (const uint32_t aInLength) const;

        uint8_t encodeChar(const uint8_t aInX) const;
        uint8_t decodeChar (const uint8_t aInX) const;
        void initializeLookupTables (void);
        void decodeBlock (const uint8_t *aInBlock, uint8_t *aOutTriBlock) const;
        const uint32_t encode (const uint8_t *aInByteStream,
                               const uint32_t aInLength);

        uint32_t encodedLength;
        uint8_t *encodedData;

        /* High speed lookup tables generated once */
        static uint8_t encodeLookupTable[64];
        static uint8_t decodeLookupTable[256];
        static int lookupTablesInitialized;

    };
};

#endif
