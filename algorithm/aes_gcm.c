#include "type.h"

//加密   参数:原文内容，原文长度，key,iv,加密文，标签
int aes_gcm_encrypt(const unsigned char* plain_text,unsigned int plain_len,const unsigned char *key,const unsigned char *iv,unsigned char *cipher_text,unsigned char *tag) {
    //1.创建上下文选择器
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    //2. 加密初始化操作
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);

    //3.设置IV长度 12B
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL);

    //4.设置密钥和IV
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    
    //5.执行加密
    int len;
    EVP_EncryptUpdate(ctx, cipher_text, &len, plain_text, plain_len);
    int cipher_len = len;
    
    //6.完成加密
    EVP_EncryptFinal_ex(ctx, cipher_text + len, &len);
    cipher_len += len;
    
    //7.获得认证标签
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag); // 获取认证标签
    
    //8.清理资源
    EVP_CIPHER_CTX_free(ctx);

    //返回加密文长度
    return cipher_len;
}

//解密
int aes_gcm_decrypt(
    const unsigned char* cipher_text, int cipher_len,
    const unsigned char* key, const unsigned char* iv,
    const unsigned char* tag, unsigned char* plain_text
) {
    // 1. 创建上下文
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    // 2. 初始化解密操作
    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL);

    // 3. 设置IV长度 12B
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 12, NULL);

    // 4. 设置密钥和IV
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);

    // 5. 执行解密
    int len;
    EVP_DecryptUpdate(ctx, plain_text, &len, cipher_text, cipher_len);

    // 6. 设置认证标签
    int plain_len = len;
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, (void*)tag);

    // 7. 验证标签（关键步骤!）
    int ret = EVP_DecryptFinal_ex(ctx, plain_text + len, &len);

    // 8. 返回验证结果
    EVP_CIPHER_CTX_free(ctx);
    return (ret > 0) ? (len + plain_len) : -1;
}