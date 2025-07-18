#include "type.h"

//����   ����:ԭ�����ݣ�ԭ�ĳ��ȣ�key,iv,�����ģ���ǩ
int aes_gcm_encrypt(const unsigned char* plain_text,unsigned int plain_len,const unsigned char *key,const unsigned char *iv,unsigned char *cipher_text,unsigned char *tag) {
    //1.����������ѡ����
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    //2. ���ܳ�ʼ������
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);

    //3.����IV���� 12B
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL);

    //4.������Կ��IV
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    
    //5.ִ�м���
    int len;
    EVP_EncryptUpdate(ctx, cipher_text, &len, plain_text, plain_len);
    int cipher_len = len;
    
    //6.��ɼ���
    EVP_EncryptFinal_ex(ctx, cipher_text + len, &len);
    cipher_len += len;
    
    //7.�����֤��ǩ
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag); // ��ȡ��֤��ǩ
    
    //8.������Դ
    EVP_CIPHER_CTX_free(ctx);

    //���ؼ����ĳ���
    return cipher_len;
}

//����
int aes_gcm_decrypt(
    const unsigned char* cipher_text, int cipher_len,
    const unsigned char* key, const unsigned char* iv,
    const unsigned char* tag, unsigned char* plain_text
) {
    // 1. ����������
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    // 2. ��ʼ�����ܲ���
    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);

    // 3. ����IV���� 12B
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL);

    // 4. ������Կ��IV
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);

    // 5. ִ�н���
    int len;
    EVP_DecryptUpdate(ctx, plain_text, &len, cipher_text, cipher_len);

    // 6. ������֤��ǩ
    int plain_len = len;
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, (void*)tag);

    // 7. ��֤��ǩ���ؼ�����!��
    int ret = EVP_DecryptFinal_ex(ctx, plain_text + len, &len);

    // 8. ������֤���
    EVP_CIPHER_CTX_free(ctx);
    return (ret > 0) ? (len + plain_len) : -1;
}