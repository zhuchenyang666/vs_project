#pragma once
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <openssl/err.h> //������
#include <openssl/evp.h>   // ʹ�� EVP API
#include <openssl/pem.h>
#include <windows.h>
//���õļ����㷨
void test_sha256(const char* data); //SHA-256 ��ϣ�㷨
//void compute_sha256(const char* data, unsigned char* output_hash);//������SHA-256�㷨
int evp_compute_sha256(const char* data, unsigned char* output_hash);//EVP�汾��SHA-256�㷨

int aes_gcm_encrypt(
    const unsigned char* plain_text, unsigned int plain_len, 
    const unsigned char* key, const unsigned char* iv, 
    unsigned char* cipher_text, unsigned char* tag);//�ԳƼ��ܣ�AES-256-GCM��
int aes_gcm_decrypt(
    const unsigned char* ciphertext, int ciphertext_len,
    const unsigned char* key, const unsigned char* iv,
    const unsigned char* tag, unsigned char* plaintext
);//����

//rsa�ǶԳƼ����㷨
void test_rsa_sign();

