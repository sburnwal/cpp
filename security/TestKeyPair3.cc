		#include <stdio.h>
		#include <iostream>
		#include <openssl/rsa.h>
		#include <openssl/pem.h>
		#include <openssl/err.h>
		#include <exception>

		bool generate_key() {
			size_t pri_len;            // Length of private key
			size_t pub_len;            // Length of public key
			char *pri_key;           // Private key in PEM
			char *pub_key;           // Public key in PEM

			int ret = 0;
			RSA *r = NULL;
			BIGNUM *bne = NULL;
			BIO *bp_public = NULL, *bp_private = NULL;
			int bits = 2048;
			unsigned long e = RSA_F4;

			EVP_PKEY *evp_pbkey = NULL;
			EVP_PKEY *evp_pkey = NULL;

			BIO *pbkeybio = NULL;
			BIO *pkeybio = NULL;

			// 1. generate rsa key
			bne = BN_new();
			ret = BN_set_word(bne, e);
			if (ret != 1) {
				return -1;
			}

			r = RSA_new();
			ret = RSA_generate_key_ex(r, bits, bne, NULL);
			if (ret != 1) {
				return -1;
			}

			// 2. save public key
			//bp_public = BIO_new_file("public.pem", "w+");
			bp_public = BIO_new(BIO_s_mem());
			ret = PEM_write_bio_RSAPublicKey(bp_public, r);
			if (ret != 1) {
				return -1;
			}

			// 3. save private key
			//bp_private = BIO_new_file("private.pem", "w+");
			bp_private = BIO_new(BIO_s_mem());
			ret = PEM_write_bio_RSAPrivateKey(bp_private, r, NULL, NULL, 0, NULL, NULL);

			//4. Get the keys are PEM formatted strings
			pri_len = BIO_pending(bp_private);
			pub_len = BIO_pending(bp_public);

			pri_key = (char*) malloc(pri_len + 1);
			pub_key = (char*) malloc(pub_len + 1);

			BIO_read(bp_private, pri_key, pri_len);
			BIO_read(bp_public, pub_key, pub_len);

			pri_key[pri_len] = '\0';
			pub_key[pub_len] = '\0';

			printf("\n%s\n%s\n", pri_key, pub_key);

			//verify if you are able to re-construct the keys
			pbkeybio = BIO_new_mem_buf((void*) pub_key, -1);
			if (pbkeybio == NULL) {
				return -1;
			}
			RSA* pubkey = NULL;
			PEM_read_bio_RSAPublicKey(pbkeybio, &pubkey, NULL, NULL);
			if (pubkey == NULL) {
				char buffer[120];
				ERR_error_string(ERR_get_error(), buffer);
				printf("Error reading public key:%s\n", buffer);
			}

			//read the private key
			pkeybio = BIO_new_mem_buf((void*) pri_key, -1);
			if (pkeybio == NULL) {
				return -1;
			}
			RSA* prikey = NULL;
			PEM_read_bio_RSAPrivateKey(pkeybio, &prikey, NULL, NULL);
			if (prikey == NULL) {
				char buffer[120];
				ERR_error_string(ERR_get_error(), buffer);
				printf("Error reading private key:%s\n", buffer);
			}

			BIO_free(pbkeybio);
			BIO_free(pkeybio);

			// 4. free
			free_all:

			BIO_free_all(bp_public);
			BIO_free_all(bp_private);
			RSA_free(r);
			BN_free(bne);

			return (ret == 1);
		}

		int main(int argc, char* argv[]) {
			generate_key();
			return 0;
		}
