/* ESP32
EN                                9   16       15   36  GPIO23  MOSI    V_SPI_D
        SensVP    ADC1_0  GPIO36  5   17       14   39  GPIO22  SCL     V_SPI_WP      UO_RTS
        SensVN    ADC1_3  GPIO39  8   18       13   41  GPIO1   CLK3                  U0_TXD
                  ADC1_6  GPIO34  10  18       12   40  GPIO3   CLK2                  U0_RXD
                  ADC1_7  GPIO35  11  20       11   42  GPIO21  SDA     V_SPI_HD
Touch9  XTAL32    ADC1_4  GPIO32  12  21       10   38  GPIO19  MISO    V_SPI_Q       UO_CTS
Touch8  XTAL32    ADC1_5  GPIO33  13  22       09   35  GPIO18  SCK     V_SPI_CLK
        DAC1      ADC2_8  GPIO25  14  23       08   34  GPIO5           V_SPI_O
        DAC2      ADC2_9  GPIO26  15  24       07   27  GPIO17                        U2_TXD
Touch7            ADC2_7  GPIO26  16  25       06   25  GPIO16                        U2_RXD
Touch6  HSPL_CLK  ADC2_6  GPIO32  17  26       05   24  GPIO4   ADC2_0  HSPI_HD               Touch0
Touch5  HSPL_Q    ADC2_5  GPIO32  18  27       04   22  GPIO2   ADC2_2  HSPI_WP   CS          Touch2
Touch4  HSPL_ID   ADC2_4  GPIO32  20  28       03   21  GPIO15  ADC2_3  HSPI_CS0              Touch3
                                 GND  29       02   GND
                                 VIN  30       01   3,3V


*/       

/* NODEMCU
EN                          ADC0  16       15   GPIO16  USER  WAKE  [LED INF]
                        Reserved  17       14   GPIO5  
                        Reserved  18       13   GPIO4   ~ 
                    SDD3  GPIO10  18       12   GPIO0   FLASH
                    SDD2  GPIO09  20       11   GPIO2   TXD1  ~     [LED SUP]  
                      SDD1  MOSI  21       10   3,3V  
                       SDCMD  CS  22       09   GND  
                      SDD0  MISO  23       08   GPIO14        HSCLK  ~
                     SDCLK  SCLK  24       07   GPIO12        HMISO  ~
                             GND  25       06   GPIO13  RXD2  HMOSI
                            3,3V  26       05   GPIO15  TXD2  HCS    ~   
                              EN  27       04   GPIO3   RXD0
                             RST  28       03   GPIO1   TXD0       
                             GND  29       02   GND
                             VIN  30       01   3,3V


*/       
