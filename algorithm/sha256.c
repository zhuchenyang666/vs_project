#include "type.h"


void test_sha256(const char* data) {
    //SHA256_DIGEST_LENGTH  32
    //256b 32B 64个十六进制数
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data, strlen(data), hash);
    printf("SHA-256 Hash: ");
}

// SHA-256 哈希计算函数  完整的SHA-256过程
// 过期的算法 但是在Clion上能跑
//void compute_sha256(const char* data, unsigned char* output_hash) {
//    // 创建SHA-256上下文
//    SHA256_CTX sha_context;
//
//    // 初始化上下文
//    if (!SHA256_Init(&sha_context)) {
//        fprintf(stderr, "SHA256_Init failed\n");
//        ERR_print_errors_fp(stderr);
//        return;
//    }
//
//    // 更新哈希计算（支持大数据分块处理）
//    if (!SHA256_Update(&sha_context, data, strlen(data))) {
//        fprintf(stderr, "SHA256_Update failed\n");
//        ERR_print_errors_fp(stderr);
//        return;
//    }
//
//    // 完成计算并获取最终哈希值
//    if (!SHA256_Final(output_hash, &sha_context)) {
//        fprintf(stderr, "SHA256_Final failed\n");
//        ERR_print_errors_fp(stderr);
//    }
//    printf("完整的SHA-256 Hash: ");
//    print_hex_hash(data, sizeof(data));
//    printf("\n");
//
//
//}

//升级后的EVP版本
// 使用 EVP API 计算 SHA-256
int evp_compute_sha256(const char* data, unsigned char* output_hash) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        return 0;
    }

    // 初始化摘要上下文，使用 SHA-256
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // 添加数据到摘要计算
    if (EVP_DigestUpdate(ctx, data, strlen(data)) != 1) {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // 获取最终哈希值
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(ctx, output_hash, &hash_len) != 1) {
        fprintf(stderr, "EVP_DigestFinal_ex failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // 验证哈希长度
    if (hash_len != SHA256_DIGEST_LENGTH) {
        fprintf(stderr, "Unexpected hash length: %u (expected %d)\n",
            hash_len, SHA256_DIGEST_LENGTH);
        EVP_MD_CTX_free(ctx);
        return 0;
    }
    //清空缓存
    EVP_MD_CTX_free(ctx);
    return 1;
}