#include "type.h"

// ��ӡʮ����������
void print_hex(const char* label, const unsigned char* data, size_t len) {
    printf("%s (%zu bytes):\n", label, len);
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
        if ((i + 1) % 32 == 0) printf("\n");
        else if ((i + 1) % 4 == 0) printf(" ");
    }
    printf("\n\n");
}

//����RSA��Կ��
void generate_rsa_keypair(EVP_PKEY** keypair) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
    EVP_PKEY_generate(ctx, keypair);\
    EVP_PKEY_CTX_free(ctx);
}

// RSAǩ����֧��PSS��
int rsa_sign(EVP_PKEY* private_key, const unsigned char* msg, size_t msg_len,
    unsigned char** signature, size_t* sig_len, int use_pss) {
    //��ʼ��������
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    // ѡ���ϣ�㷨
    const EVP_MD* md = EVP_sha256();

    // ��ʼ��ǩ������
    EVP_DigestSignInit(ctx, NULL, md, NULL, private_key);

    // ����PSS��䣨������ã�
    if (use_pss) {
        EVP_PKEY_CTX_set_rsa_padding(EVP_MD_CTX_get_pkey_ctx(ctx), RSA_PKCS1_PSS_PADDING);
        EVP_PKEY_CTX_set_rsa_pss_saltlen(EVP_MD_CTX_get_pkey_ctx(ctx), -1);
    }

    // ȷ��ǩ������
    EVP_DigestSign(ctx, NULL, sig_len, msg, msg_len);

    // ����ǩ��������
    *signature = (unsigned char*)malloc(*sig_len);

    // ִ��ǩ��
    EVP_DigestSign(ctx, *signature, sig_len, msg, msg_len);

    EVP_MD_CTX_free(ctx);
    return 1;
}


// RSA��ǩ��֧��PSS��
int rsa_verify(EVP_PKEY* public_key, const unsigned char* msg, size_t msg_len,
    const unsigned char* signature, size_t sig_len, int use_pss) {
    //��ʼ��������
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    // ѡ���ϣ�㷨
    const EVP_MD* md = EVP_sha256();

    // ��ʼ����ǩ����
    EVP_DigestVerifyInit(ctx, NULL, md, NULL, public_key);

    // ����PSS��䣨������ã�
    if (use_pss) {
       EVP_PKEY_CTX_set_rsa_padding(EVP_MD_CTX_get_pkey_ctx(ctx), RSA_PKCS1_PSS_PADDING);
       EVP_PKEY_CTX_set_rsa_pss_saltlen(EVP_MD_CTX_get_pkey_ctx(ctx), -1);
    }

    // ִ����ǩ
    int ret = EVP_DigestVerify(ctx, signature, sig_len, msg, msg_len);

    EVP_MD_CTX_free(ctx);

    if (ret == 1) {
        return 1; // ��ǩ�ɹ�
    }
    else if (ret == 0) {
        return 0; // ��ǩʧ��
    }
    else {
        ERR_print_errors_fp(stderr);
        return -1; // ��������
    }
}



//�ǶԳƼ���rsa // �ǶԳƼ��ܣ�ROAǩ������ǩ��
void test_rsa_sign() {
    // ===== ����1������ǩ������ǩ =====
    printf("===== Test 1: Basic Sign/Verify (PKCS#1 v1.5) =====\n");
    {
        const char* message = "HelloWorld!";

        // ������Կ��
        EVP_PKEY* keypair = NULL;
        generate_rsa_keypair(&keypair);

        // ��ȡ��Կ
        EVP_PKEY* public_key = keypair;

        // ǩ��
        unsigned char* signature = NULL;
        size_t sig_len;
        rsa_sign(keypair, (const unsigned char*)message, strlen(message),&signature, &sig_len, 0);

        print_hex("Signature", signature, sig_len);

        // ��ǩ����ͬ���ݣ�
        int result = rsa_verify(public_key, (const unsigned char*)message, strlen(message),
            signature, sig_len, 0);
        printf("Verification result: %s\n", result == 1 ? "SUCCESS" : "FAILURE");

        // ����
        free(signature);
        EVP_PKEY_free(keypair);
    }
}