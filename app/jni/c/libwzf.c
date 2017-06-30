#include <jni.h>
#include<stdio.h>
#include<stdlib.h>
#include "../header/android_log.h"

char pwd[] = "wangzhenfei";

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_encodeFile(JNIEnv *env, jobject instance, jstring src_,
                                                     jstring des_) {
    const char *src = (*env)->GetStringUTFChars(env, src_, 0);
    const char *des = (*env)->GetStringUTFChars(env, des_, 0);
    LOG_I_DEBUG("encodeFilePath: %s", src);

    // TODO

    FILE *src_fp = fopen(src, "rb");
    if(src_fp == NULL){
        printf("src error!\n");
        return;
    }
    FILE *des_fp = fopen(des, "wb");

    int ch;
    int i = 0;//循环使用密码中的字符进行异或
    int pwd_len = strlen(pwd);
    printf("++++++++++++++++++++++++++++++++++\n");
    while((ch = fgetc(src_fp)) != EOF){
        printf("%c", pwd[i % pwd_len]);
        fputc(ch ^ pwd[i % pwd_len], des_fp);
        i++;
    }

    fclose(src_fp);
    fclose(des_fp);

    (*env)->ReleaseStringUTFChars(env, src_, src);
    (*env)->ReleaseStringUTFChars(env, des_, des);
}

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_decodeFile(JNIEnv *env, jobject instance, jstring src_,
                                                     jstring des_) {
    const char *src = (*env)->GetStringUTFChars(env, src_, 0);
    const char *des = (*env)->GetStringUTFChars(env, des_, 0);
    LOG_I_DEBUG("encodeFilePath: %s", src);
    // TODO
    FILE *src_fp = fopen(src, "rb");
    if(src_fp == NULL){
        printf("src error!\n");
        return;
    }
    FILE *des_fp = fopen(des, "wb");
    printf("++++++++++++++++++++++++++++++++++\n");
    int ch;
    int i = 0;//循环使用密码中的字符进行异或
    int pwd_len = strlen(pwd);
    while((ch = fgetc(src_fp)) != EOF){
        fputc(ch ^ pwd[i % pwd_len], des_fp);
        i++;
    }

    fclose(src_fp);
    fclose(des_fp);

    (*env)->ReleaseStringUTFChars(env, src_, src);
    (*env)->ReleaseStringUTFChars(env, des_, des);
}



JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_spliceFile(JNIEnv *env, jobject instance, jstring src_,
                                                     jstring desStartName_, jint count) {
    const char *src = (*env)->GetStringUTFChars(env, src_, 0);
    const char *desStartName = (*env)->GetStringUTFChars(env, desStartName_, 0);
    LOG_I_DEBUG("encodeFilePath: %s", src);
    // TODO
    FILE *src_fp = fopen(src, "rb");
    fseek(src_fp, 0, SEEK_END);
    int totalSize =  ftell(src_fp);
    fseek(src_fp, 0 , SEEK_SET);
    int partSize = totalSize / count;
    int remind = totalSize % count;
    int i = 0;
    int ch = '0';
    int index = 0;
    char desName[100];
    for(; i < count; i++){
        sprintf(desName, "%s%d", desStartName,i);//写字符串到s
        LOG_I_DEBUG("spliceDesFilePath%d: %s", i,src);
        FILE *des_fp = fopen(desName, "wb");
        while((ch = fgetc(src_fp)) != EOF){
            fputc(ch, des_fp);
            index ++;
            if((i!= count -1 ) && index == partSize * (i+1)){
                break;
            }
        }
        fclose(des_fp);
    }
    fclose(src_fp);
    (*env)->ReleaseStringUTFChars(env, src_, src);
    (*env)->ReleaseStringUTFChars(env, desStartName_, desStartName);
}

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_mergeFile(JNIEnv *env, jobject instance,
                                                    jstring srcStartName_, jint count,
                                                    jstring des_) {
    const char *srcStartName = (*env)->GetStringUTFChars(env, srcStartName_, 0);
    const char *des = (*env)->GetStringUTFChars(env, des_, 0);

    // TODO
    FILE *des_fp = fopen(des, "wb");
    int i = 0;
    int ch = '0';
    char srcName[100];
    for(; i < count; i++){
        sprintf(srcName, "%s%d", srcStartName,i);//写字符串到s
        LOG_I_DEBUG("mergeSrcFilePath%d: %s", i,srcName);
        FILE *src_fp = fopen(srcName, "rb");
        while((ch = fgetc(src_fp)) != EOF){
            fputc(ch, des_fp);
        }
        fclose(src_fp);
    }
    fclose(des_fp);

    (*env)->ReleaseStringUTFChars(env, srcStartName_, srcStartName);
    (*env)->ReleaseStringUTFChars(env, des_, des);
}