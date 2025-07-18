#include "type.h"


void test_sha256(const char* data) {
    //SHA256_DIGEST_LENGTH  32
    //256b 32B 64��ʮ��������
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data, strlen(data), hash);
    printf("SHA-256 Hash: ");
}

// SHA-256 ��ϣ���㺯��  ������SHA-256����
// ���ڵ��㷨 ������Clion������
//void compute_sha256(const char* data, unsigned char* output_hash) {
//    // ����SHA-256������
//    SHA256_CTX sha_context;
//
//    // ��ʼ��������
//    if (!SHA256_Init(&sha_context)) {
//        fprintf(stderr, "SHA256_Init failed\n");
//        ERR_print_errors_fp(stderr);
//        return;
//    }
//
//    // ���¹�ϣ���㣨֧�ִ����ݷֿ鴦��
//    if (!SHA256_Update(&sha_context, data, strlen(data))) {
//        fprintf(stderr, "SHA256_Update failed\n");
//        ERR_print_errors_fp(stderr);
//        return;
//    }
//
//    // ��ɼ��㲢��ȡ���չ�ϣֵ
//    if (!SHA256_Final(output_hash, &sha_context)) {
//        fprintf(stderr, "SHA256_Final failed\n");
//        ERR_print_errors_fp(stderr);
//    }
//    printf("������SHA-256 Hash: ");
//    print_hex_hash(data, sizeof(data));
//    printf("\n");
//
//
//}

//�������EVP�汾
// ʹ�� EVP API ���� SHA-256
int evp_compute_sha256(const char* data, unsigned char* output_hash) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "EVP_MD_CTX_new failed\n");
        return 0;
    }

    // ��ʼ��ժҪ�����ģ�ʹ�� SHA-256
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // ������ݵ�ժҪ����
    if (EVP_DigestUpdate(ctx, data, strlen(data)) != 1) {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // ��ȡ���չ�ϣֵ
    unsigned int hash_len;
    if (EVP_DigestFinal_ex(ctx, output_hash, &hash_len) != 1) {
        fprintf(stderr, "EVP_DigestFinal_ex failed\n");
        ERR_print_errors_fp(stderr);
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    // ��֤��ϣ����
    if (hash_len != SHA256_DIGEST_LENGTH) {
        fprintf(stderr, "Unexpected hash length: %u (expected %d)\n",
            hash_len, SHA256_DIGEST_LENGTH);
        EVP_MD_CTX_free(ctx);
        return 0;
    }
    //��ջ���
    EVP_MD_CTX_free(ctx);
    return 1;
}