#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/pkcs12.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

int main() {
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();

	SSL_CTX* ctx = ctx = SSL_CTX_new(SSLv23_method());
	if (!ctx) {
		ERR_print_errors_fp(stderr);
		std::cout << "cannot allocate SSL_CTX" << std::endl;
		return false;
	}

	SSL_CTX_set_mode(ctx,
			SSL_MODE_ENABLE_PARTIAL_WRITE|SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
	SSL_CTX_set_options(ctx,
			SSL_OP_SINGLE_DH_USE|SSL_OP_NO_SSLv2|SSL_OP_NO_SSLv3);

	char* cacertFile = "cacert.crt";
	char* certFile = "server.crt";
	char* keyFile = "server.key";

	if (!SSL_CTX_load_verify_locations(ctx, cacertFile, NULL)) {
		std::cout << "cannot load cacerts" << std::endl;
	} else {
		std::cout << "cacert loaded" << std::endl;
	}

	if (!SSL_CTX_use_certificate_file(ctx, certFile, SSL_FILETYPE_PEM)) {
		std::cout << "cannot load certfile" << std::endl;
	} else {
		std::cout << "certfile loaded" << std::endl;
	}

	if (!SSL_CTX_use_PrivateKey_file(ctx, keyFile, SSL_FILETYPE_PEM)) {
		std::cout << "cannot load private key" << std::endl;
	} else {
		std::cout << "private key loaded" << std::endl;
	}

	//verify
	X509_STORE *store = SSL_CTX_get_cert_store(ctx);
	X509_STORE_CTX* vrfy_ctx = X509_STORE_CTX_new();
	if(!vrfy_ctx) {
		ERR_print_errors_fp(stderr);
	} else {
		std::cout << "store ctx created" << std::endl;
	}

	if(X509_STORE_CTX_init(vrfy_ctx, store, NULL, NULL)) {
		std::cout << "store ctx verify init done" << std::endl;
	} else {
		ERR_print_errors_fp(stderr);
	}

	X509* cert = X509_STORE_CTX_get_current_cert(vrfy_ctx);
	if(cert) {
		std::cout << "get_current_cert good" << std::endl;
	} else {
		ERR_print_errors_fp(stderr);
	}
	char *lSubj = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
	char* lIssuer = X509_NAME_oneline(X509_get_issuer_name(cert), NULL, 0);
	std::cout << "Cert sub = " << lSubj << " issuer = " << lIssuer;


	X509* x509 = X509_STORE_CTX_get_current_cert(vrfy_ctx);
	lSubj = X509_NAME_oneline(X509_get_subject_name(cert), NULL, 0);
	lIssuer = X509_NAME_oneline(X509_get_issuer_name(cert), NULL, 0);
	std::cout << "Cert sub = " << lSubj << " issuer = " << lIssuer;

	X509_INFO *itmp;
	int i, count = 0, type = X509_FILETYPE_PEM;
	STACK_OF(X509_INFO) *inf = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

	if (!inf) {
		BIO_free(cbio); //cleanup
		return false;
	}
	//itterate over all entries from the pem file, add them to the x509_store one by one
	for (i = 0; i < sk_X509_INFO_num(inf); i++) {
		itmp = sk_X509_INFO_value(inf, i);
		if (itmp->x509) {
			char *lSubj = X509_NAME_oneline(X509_get_subject_name(itmp->x509), NULL, 0);
			char* lIssuer = X509_NAME_oneline(X509_get_issuer_name(itmp->x509), NULL, 0);
			std::cout << "Cert sub = " << lSubj << " issuer = " << lIssuer;
			X509_STORE_add_cert(cts, itmp->x509);
			count++;
		}
		if (itmp->crl) {
			X509_STORE_add_crl(cts, itmp->crl);
			count++;
		}
	}
	sk_X509_INFO_pop_free(inf, X509_INFO_free); //cleanup
	BIO_free(cbio); //cleanup
	*/
}
