#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <constants.h>


/*
registers:
0x0000 .. 0x0003 - merchantId в ascii
0x0010 - status
0x0011 - terminal state
0x0012 - command from controller
0x0017 .. 0x0018 - credit
*/

struct Data {
    unsigned char merchantNdx = 1;
    union {
        unsigned short int status;
        struct {
            struct {
                unsigned char h :8;
            } byteHi;
            struct {
                unsigned char l :8;
            } byteLo;
        } reg10;
    };

    union {
        unsigned short int command;
        struct {
            struct {
                unsigned char h :8;
            } byteHi;
            struct {
                unsigned char l :8;
            } byteLo;
        } reg12;
    };

    union {
        unsigned int amount;
        struct {
            struct {
                unsigned char h :8;
            } byteHi;
            struct {
                unsigned char l :8;
            } byteLo;
        } reg17;

        struct {
            struct {
                unsigned char h :8;
            } byteHi;
            struct {
                unsigned char l :8;
            } byteLo;
        } reg18;
    };
};

struct BPOsParameters {
    std::string sIP             = DefaultSettings::defaultIp;
    std::string sPort           = DefaultSettings::defaultPort;
    std::string sRRN;
    unsigned int nTrnType       = Purchase;
    unsigned int nBaudRate      = 0;
    unsigned int nAmount        = DefaultSettings::defaultAmount;
    unsigned int nInvoiceNum    = 0;
    unsigned char bMerchIdx     = DefaultSettings::defaultMerchant;
    unsigned char bErrorLang    = 0;
    bool bIsAutoConfirm         = false;
    bool bIsConsoleOn           = false;
};

#endif // REGISTER_H
