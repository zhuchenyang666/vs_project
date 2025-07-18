#include "type.h"

//16进制打印计算过的哈希
void print_hex_hash(const unsigned char* hash, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}


// 打印十六进制数据 针对对称加密aes_gcm算法
void print_hex1(const char* label, const unsigned char* data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void testOpenssl() {
    // 打印 OpenSSL 版本
    printf("OpenSSL Version: %s\n", OpenSSL_version(SSLEAY_VERSION));


    // 初始化随机数生成器
    if (!RAND_poll()) {
        fprintf(stderr, "RAND_poll failed\n");
        return 1;
    }
    // 验证随机数生成
    unsigned char buffer[32];
    if (RAND_bytes(buffer, sizeof(buffer))) {
        printf("RAND_bytes test passed!\n");
    }
    else {
        fprintf(stderr, "RAND_bytes error!\n");
    }
}

void testSHA256() {
    // 测试用例1: 空字符串
    unsigned char hash_empty[SHA256_DIGEST_LENGTH];
    if (evp_compute_sha256("", hash_empty)) {
        printf("Empty String: ");
        print_hex_hash(hash_empty, SHA256_DIGEST_LENGTH);
        // 预期: e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    }

    // 测试用例2: 短字符串
    unsigned char hash_short[SHA256_DIGEST_LENGTH];
    if (evp_compute_sha256("abc", hash_short)) {
        printf("Short String: ");
        print_hex_hash(hash_short, SHA256_DIGEST_LENGTH);
        // 预期: ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
    }

    // 测试用例3: 长字符串
    const char* long_text = "This is a longer text to demonstrate SHA-256 hashing "
        "with multiple blocks of data. The quick brown fox jumps "
        "over the lazy dog. 1234567890!@#$%^&*()";
    unsigned char hash_long[SHA256_DIGEST_LENGTH];
    if (evp_compute_sha256(long_text, hash_long)) {
        printf("Long String: ");
        print_hex_hash(hash_long, SHA256_DIGEST_LENGTH);
    }
}

//一般测试
void testAES_GCM_NORMAL() {
    // 测试1: 基本加密解密
    printf("===== Test 1: Basic Encryption/Decryption =====\n");
    {
        const unsigned char* plain_text = "Secret AES-GCM message!";
        unsigned char key[32];     // AES-256密钥
        unsigned char iv[12];      // 初始化向量
        unsigned char tag[16];     // 认证标签
        unsigned char cipher_text[128]; //加密文
        unsigned char decrypted[128]; //对加密文解密后填充文

        // 生成随机密钥和IV
        RAND_bytes(key, sizeof(key));
        RAND_bytes(iv, sizeof(iv));

        print_hex1("Key        ", key, sizeof(key));
        print_hex1("IV         ", iv, sizeof(iv));

        // 加密过程
        int cipher_len = aes_gcm_encrypt(
            plain_text, strlen(plain_text),
            key, iv,
            cipher_text, tag
        );

        if (cipher_len <= 0) {
            fprintf(stderr, "Encryption failed!\n");
            ERR_print_errors_fp(stderr);
            return 1;
        }

        print_hex("Ciphertext ", cipher_text, cipher_len);
        print_hex("Tag        ", tag, sizeof(tag));
        printf("\n开始解密流程...\n");
        system("pause");

        //解密过程  需要知道key,iv,tag
        int decrypted_len = aes_gcm_decrypt(
            cipher_text, cipher_len,
            key, iv,
            tag, decrypted
        );

        if (decrypted_len == -1) {
            fprintf(stderr, "Decryption failed: Authentication failed!\n");
            return 1;
        }

        decrypted[decrypted_len] = '\0'; // Null-terminate

        printf("Decrypted: %s\n", decrypted);
        printf("Status: %s\n\n", strcmp(plain_text, (char*)decrypted) == 0 ? "SUCCESS" : "FAILURE");
    }
}



int main() {
    test_rsa_sign();
    return 0;
}
