
#ifndef NDKSTUDY_LOG_H
#define NDKSTUDY_LOG_H
#define LOG_I(FORMAT,...) printf("FROM_C_INFO  : "); printf(FORMAT, __VA_ARGS__)
#define LOG_E(FORMAT,...) printf("FROM_C_ERROR : "); printf(FORMAT, __VA_ARGS__)
#define LOG_W(FORMAT,...) printf("FROM_C_WARN  : "); printf(FORMAT, __VA_ARGS__)
#define LOG_D(FORMAT,...) printf("FROM_C_DEBUG : "); printf(FORMAT, __VA_ARGS__)
#endif //NDKSTUDY_LOG_H
