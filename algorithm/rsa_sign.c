#include "type.h"

// 打印十六进制数据
void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s (%zu bytes):\n", label, len);
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
        if ((i + 1) % 32 == 0) printf("\n");
        else if ((i + 1) % 4 == 0) printf(" ");
    }
    printf("\n\n");
}

//生成RSA密钥对
void generate_rsa_keypair(EVP_PKEY** keypair) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
    EVP_PKEY_generate(ctx, keypair);\
    EVP_PKEY_CTX_free(ctx);
}

// RSA签名（支持PSS）
int rsa_sign(EVP_PKEY* private_key, const unsigned char* msg, size_t msg_len,
    unsigned char** signature, size_t* sig_len, int use_pss) {
    //初始化上下文
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    // 选择哈希算法
    const EVP_MD* md = EVP_sha256();

    // 初始化签名操作
    EVP_DigestSignInit(ctx, NULL, md, NULL, private_key);

    // 设置PSS填充（如果启用）
    if (use_pss) {
        EVP_PKEY_CTX_set_rsa_padding(EVP_MD_CTX_get_pkey_ctx(ctx), RSA_PKCS1_PSS_PADDING);
        EVP_PKEY_CTX_set_rsa_pss_saltlen(EVP_MD_CTX_get_pkey_ctx(ctx), -1);
    }

    // 确定签名长度
    EVP_DigestSign(ctx, NULL, sig_len, msg, msg_len);

    // 分配签名缓冲区
    *signature = (unsigned char*)malloc(*sig_len);

    // 执行签名
    EVP_DigestSign(ctx, *signature, sig_len, msg, msg_len);

    EVP_MD_CTX_free(ctx);
    return 1;
}


// RSA验签（支持PSS）
int rsa_verify(EVP_PKEY* public_key, const unsigned char* msg, size_t msg_len,
    const unsigned char* signature, size_t sig_len, int use_pss) {
    //初始化上下文
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    // 选择哈希算法
    const EVP_MD* md = EVP_sha256();

    // 初始化验签操作
    EVP_DigestVerifyInit(ctx, NULL, md, NULL, public_key);

    // 设置PSS填充（如果启用）
    if (use_pss) {
       EVP_PKEY_CTX_set_rsa_padding(EVP_MD_CTX_get_pkey_ctx(ctx), RSA_PKCS1_PSS_PADDING);
       EVP_PKEY_CTX_set_rsa_pss_saltlen(EVP_MD_CTX_get_pkey_ctx(ctx), -1);
    }

    // 执行验签
    int ret = EVP_DigestVerify(ctx, signature, sig_len, msg, msg_len);

    EVP_MD_CTX_free(ctx);

    if (ret == 1) {
        return 1; // 验签成功
    }
    else if (ret == 0) {
        return 0; // 验签失败
    }
    else {
        ERR_print_errors_fp(stderr);
        return -1; // 发生错误
    }
}



//非对称加密rsa // 非对称加密（ROA签名与验签）
void test_rsa_sign() {
    // ===== 测试1：基本签名与验签 =====
    printf("===== Test 1: Basic Sign/Verify (PKCS#1 v1.5) =====\n");
    {
        const char* message = "HelloWorld!";

        // 生成密钥对
        EVP_PKEY* keypair = NULL;
        generate_rsa_keypair(&keypair);

        // 提取公钥
        EVP_PKEY* public_key = keypair;

        // 签名
        unsigned char* signature = NULL;
        size_t sig_len;
        rsa_sign(keypair, (const unsigned char*)message, strlen(message),&signature, &sig_len, 0);

        print_hex("Signature", signature, sig_len);

        // 验签（相同数据）
        int result = rsa_verify(public_key, (const unsigned char*)message, strlen(message),
            signature, sig_len, 0);
        printf("Verification result: %s\n", result == 1 ? "SUCCESS" : "FAILURE");

        // 清理
        free(signature);
        EVP_PKEY_free(keypair);
    }
}