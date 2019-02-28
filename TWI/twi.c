#include "stdint.h"
#include "gpio.h"

#define TWI0 ((NRF_TWI_REG *)0x40003000)

#define SCL_PIN 0
#define SDA_PIN 30


typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t RESERVED0[1];
    volatile uint32_t STARTTX;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t STOP;
    volatile uint32_t RESERVED2[1];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESUME;
    volatile uint32_t RESERVED3[56];
    volatile uint32_t STOPPED;
    volatile uint32_t RXDREADY;
    volatile uint32_t RESERVED4[4];
    volatile uint32_t TXDSENT;
    volatile uint32_t RESERVED5[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED6[4];
    volatile uint32_t BB;
    volatile uint32_t RESERVED7[49];
    volatile uint32_t SHORT;
    volatile uint32_t RESERVED8[63];
    volatile uint32_t INTEN;
    volatile uint32_t INTSET;
    volatile uint32_t INTCLR;
    volatile uint32_t RESERVED9[110];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED10[14];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED11[1];
    volatile uint32_t PSELSCL;
    volatile uint32_t PSELSDA;
    volatile uint32_t RESERVED13[2];
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED14[1];
    volatile uint32_t FREQUENCY;
    volatile uint32_t RESERVED15[24];
    volatile uint32_t ADDRESS;
} NRF_TWI_REG;