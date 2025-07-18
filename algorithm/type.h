#pragma once
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <openssl/err.h> //错误处理
#include <openssl/evp.h>   // 使用 EVP API
#include <openssl/pem.h>
#include <windows.h>
//常用的加密算法
void test_sha256(const char* data); //SHA-256 哈希算法
//void compute_sha256(const char* data, unsigned char* output_hash);//完整的SHA-256算法
int evp_compute_sha256(const char* data, unsigned char* output_hash);//EVP版本的SHA-256算法

int aes_gcm_encrypt(
    const unsigned char* plain_text, unsigned int plain_len, 
    const unsigned char* key, const unsigned char* iv, 
    unsigned char* cipher_text, unsigned char* tag);//对称加密（AES-256-GCM）
int aes_gcm_decrypt(
    const unsigned char* ciphertext, int ciphertext_len,
    const unsigned char* key, const unsigned char* iv,
    const unsigned char* tag, unsigned char* plaintext
);//解密

//rsa非对称加密算法
void test_rsa_sign();

