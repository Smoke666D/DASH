/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode V4

    This file was automatically generated by CANopenEditor v4.0-51-g2d9b1ad

    https://github.com/CANopenNode/CANopenNode
    https://github.com/CANopenNode/CANopenEditor

    DON'T EDIT THIS FILE MANUALLY !!!!
********************************************************************************

    File info:
        File Names:   OD.h; OD.c
        Project File: DASH.xdd
        File Version: 3

        Created:      31.01.2017 17:13:00
        Created By:   Smoke666
        Modified:     19.03.2024 22:09:56
        Modified By:  rOBIN 2

    Device Info:
        Vendor Name:  SIDER
        Vendor ID:    2
        Product Name: DashBoard 
        Product ID:   1

        Description:  sdfsdsdf
*******************************************************************************/

#ifndef OD_H
#define OD_H
/*******************************************************************************
    Counters of OD objects
*******************************************************************************/
#define OD_CNT_NMT 1
#define OD_CNT_EM 1
#define OD_CNT_EM_PROD 1
#define OD_CNT_HB_PROD 1
#define OD_CNT_RPDO 4
#define OD_CNT_TPDO 3

/*******************************************************************************
    Sizes of OD arrays
*******************************************************************************/
#define OD_CNT_ARR_1003 16
#define OD_CNT_ARR_2000 7
#define OD_CNT_ARR_2001 7
#define OD_CNT_ARR_2002 3
#define OD_CNT_ARR_2004 3
#define OD_CNT_ARR_2005 6
#define OD_CNT_ARR_2006 2
#define OD_CNT_ARR_2007 10
#define OD_CNT_ARR_2008 15
#define OD_CNT_ARR_2009 6
#define OD_CNT_ARR_200A 6
#define OD_CNT_ARR_200B 6
#define OD_CNT_ARR_200C 6
#define OD_CNT_ARR_200D 6
#define OD_CNT_ARR_200E 6
#define OD_CNT_ARR_200F 6
#define OD_CNT_ARR_2010 6
#define OD_CNT_ARR_2011 6
#define OD_CNT_ARR_2012 6
#define OD_CNT_ARR_2013 6
#define OD_CNT_ARR_2014 6
#define OD_CNT_ARR_2015 6
#define OD_CNT_ARR_2016 6
#define OD_CNT_ARR_2019 6
#define OD_CNT_ARR_201A 10
#define OD_CNT_ARR_201B 3
#define OD_CNT_ARR_202F 2
#define OD_CNT_ARR_2030 30
#define OD_CNT_ARR_2031 30
#define OD_CNT_ARR_2032 30
#define OD_CNT_ARR_2033 2


/*******************************************************************************
    OD data declaration of all groups
*******************************************************************************/
typedef struct {
    uint32_t x1000_deviceType;
    char x1008_manufacturerDeviceName[12];
    char x1009_manufacturerHardwareVersion[5];
    char x100A_manufacturerSoftwareVersion[5];
    struct {
        uint8_t maxSub_index;
        uint32_t vendor_ID;
        uint32_t productCode;
        uint32_t revisionNumber;
        uint32_t serialNumber;
    } x1018_identity;
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
    } x1401_RPDOCommunicationParameter;
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
    } x1402_RPDOCommunicationParameter;
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
    } x1403_RPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
        uint32_t mappedObject_4;
        uint32_t mappedObject_5;
        uint32_t mappedObject_6;
    } x1601_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
        uint32_t mappedObject_4;
        uint32_t mappedObject_5;
        uint32_t mappedObject_6;
    } x1602_RPDOMappingParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
    } x1603_RPDOMappingParameter;
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1800_TPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
        uint32_t mappedObject_4;
        uint32_t mappedObject_5;
    } x1A00_TPDOMappingParameter;
    uint8_t x2006_DIN_DATA_sub0;
    uint8_t x2007_BIG_SEG_CONFIG_sub0;
    uint8_t x2008_RGB_MAP_REGISTER_sub0;
    uint8_t x2009_RGB1_SETUP_REGISTER_sub0;
    uint16_t x2009_RGB1_SETUP_REGISTER[OD_CNT_ARR_2009];
    uint8_t x200A_RGB2_SETUP_REGISTER_sub0;
    uint16_t x200A_RGB2_SETUP_REGISTER[OD_CNT_ARR_200A];
    uint8_t x200B_RGB3_SETUP_REGISTER_sub0;
    uint16_t x200B_RGB3_SETUP_REGISTER[OD_CNT_ARR_200B];
    uint8_t x200C_RGB4_SETUP_REGISTER_sub0;
    uint16_t x200C_RGB4_SETUP_REGISTER[OD_CNT_ARR_200C];
    uint8_t x200D_RGB5_SETUP_REGISTER_sub0;
    uint16_t x200D_RGB5_SETUP_REGISTER[OD_CNT_ARR_200D];
    uint8_t x200E_RGB6_SETUP_REGISTER_sub0;
    uint16_t x200E_RGB6_SETUP_REGISTER[OD_CNT_ARR_200E];
    uint8_t x200F_RGB7_SETUP_REGISTER_sub0;
    uint16_t x200F_RGB7_SETUP_REGISTER[OD_CNT_ARR_200F];
    uint8_t x2010_RGB8_SETUP_REGISTER_sub0;
    uint16_t x2010_RGB8_SETUP_REGISTER[OD_CNT_ARR_2010];
    uint8_t x2011_RGB9_SETUP_REGISTER_sub0;
    uint16_t x2011_RGB9_SETUP_REGISTER[OD_CNT_ARR_2011];
    uint8_t x2012_RGB10_SETUP_REGISTER_sub0;
    uint16_t x2012_RGB10_SETUP_REGISTER[OD_CNT_ARR_2012];
    uint8_t x2013_RGB11_SETUP_REGISTER_sub0;
    uint16_t x2013_RGB11_SETUP_REGISTER[OD_CNT_ARR_2013];
    uint8_t x2014_RGB12_SETUP_REGISTER_sub0;
    uint16_t x2014_RGB12_SETUP_REGISTER[OD_CNT_ARR_2014];
    uint8_t x2015_RGB13_SETUP_REGISTER_sub0;
    uint16_t x2015_RGB13_SETUP_REGISTER[OD_CNT_ARR_2015];
    uint8_t x2016_RGB14_SETUP_REGISTER_sub0;
    uint16_t x2016_RGB14_SETUP_REGISTER[OD_CNT_ARR_2016];
    uint8_t x2019_BAR_SETUP_REGISTER_sub0;
    uint16_t x2019_BAR_SETUP_REGISTER[OD_CNT_ARR_2019];
    uint8_t x201A_MENU_MAP_REGISTER_sub0;
    uint32_t x201A_MENU_MAP_REGISTER[OD_CNT_ARR_201A];
    uint8_t x201B_MENU_SETUP_REGISTER_sub0;
    uint8_t x202F_brigthRegister_sub0;
    uint8_t x2030_ADC_1_CalibraionRegister_sub0;
    uint8_t x2031_ADC_2_CalibraionRegister_sub0;
    uint8_t x2032_ADC_3_CalibraionRegister_sub0;
    uint8_t x2033_RPM_CalibrationRegister_sub0;
} OD_ROM_t;

typedef struct {
    uint8_t x1001_errorRegister;
    char x100B_object_100BhModelID[15];
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByRPDO;
        uint8_t transmissionType;
    } x1400_RPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
    } x1600_RPDOMappingParameter;
    uint8_t x2000_virtualChannelV1__V7_sub0;
    uint8_t x2001_virtualChannelV8__V14_sub0;
    uint8_t x2002_virtualChannelV15_V17_sub0;
    uint8_t x2004_DACH_PARAMETR_sub0;
    uint8_t x2005_AIN_RPM_sub0;
} OD_RAM_t;

typedef struct {
    uint32_t x1014_COB_ID_EMCY;
    uint16_t x1015_inhibitTimeEMCY;
    uint16_t x1017_producerHeartbeatTime;
} OD_PERSIST_COMM_t;

typedef struct {
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1801_TPDOCommunicationParameter;
    struct {
        uint8_t maxSub_index;
        uint32_t COB_IDUsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNCStartValue;
    } x1802_TPDOCommunicationParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
        uint32_t mappedObject_3;
    } x1A01_TPDOMappingParameter;
    struct {
        uint8_t numberOfMappedObjects;
        uint32_t mappedObject_1;
        uint32_t mappedObject_2;
    } x1A02_TPDOMappingParameter;
} OD__t;

#ifndef OD_ATTR_ROM
#define OD_ATTR_ROM
#endif
extern OD_ATTR_ROM OD_ROM_t OD_ROM;

#ifndef OD_ATTR_RAM
#define OD_ATTR_RAM
#endif
extern OD_ATTR_RAM OD_RAM_t OD_RAM;

#ifndef OD_ATTR_PERSIST_COMM
#define OD_ATTR_PERSIST_COMM
#endif
extern OD_ATTR_PERSIST_COMM OD_PERSIST_COMM_t OD_PERSIST_COMM;

#ifndef OD_ATTR_
#define OD_ATTR_
#endif
extern OD_ATTR_ OD__t OD_;

#ifndef OD_ATTR_OD
#define OD_ATTR_OD
#endif
extern OD_ATTR_OD OD_t *OD;


/*******************************************************************************
    Object dictionary entries - shortcuts
*******************************************************************************/
#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1003 &OD->list[2]
#define OD_ENTRY_H1008 &OD->list[3]
#define OD_ENTRY_H1009 &OD->list[4]
#define OD_ENTRY_H100A &OD->list[5]
#define OD_ENTRY_H100B &OD->list[6]
#define OD_ENTRY_H1014 &OD->list[7]
#define OD_ENTRY_H1015 &OD->list[8]
#define OD_ENTRY_H1017 &OD->list[9]
#define OD_ENTRY_H1018 &OD->list[10]
#define OD_ENTRY_H1400 &OD->list[11]
#define OD_ENTRY_H1401 &OD->list[12]
#define OD_ENTRY_H1402 &OD->list[13]
#define OD_ENTRY_H1403 &OD->list[14]
#define OD_ENTRY_H1600 &OD->list[15]
#define OD_ENTRY_H1601 &OD->list[16]
#define OD_ENTRY_H1602 &OD->list[17]
#define OD_ENTRY_H1603 &OD->list[18]
#define OD_ENTRY_H1800 &OD->list[19]
#define OD_ENTRY_H1801 &OD->list[20]
#define OD_ENTRY_H1802 &OD->list[21]
#define OD_ENTRY_H1A00 &OD->list[22]
#define OD_ENTRY_H1A01 &OD->list[23]
#define OD_ENTRY_H1A02 &OD->list[24]
#define OD_ENTRY_H2000 &OD->list[25]
#define OD_ENTRY_H2001 &OD->list[26]
#define OD_ENTRY_H2002 &OD->list[27]
#define OD_ENTRY_H2003 &OD->list[28]
#define OD_ENTRY_H2004 &OD->list[29]
#define OD_ENTRY_H2005 &OD->list[30]
#define OD_ENTRY_H2006 &OD->list[31]
#define OD_ENTRY_H2007 &OD->list[32]
#define OD_ENTRY_H2008 &OD->list[33]
#define OD_ENTRY_H2009 &OD->list[34]
#define OD_ENTRY_H200A &OD->list[35]
#define OD_ENTRY_H200B &OD->list[36]
#define OD_ENTRY_H200C &OD->list[37]
#define OD_ENTRY_H200D &OD->list[38]
#define OD_ENTRY_H200E &OD->list[39]
#define OD_ENTRY_H200F &OD->list[40]
#define OD_ENTRY_H2010 &OD->list[41]
#define OD_ENTRY_H2011 &OD->list[42]
#define OD_ENTRY_H2012 &OD->list[43]
#define OD_ENTRY_H2013 &OD->list[44]
#define OD_ENTRY_H2014 &OD->list[45]
#define OD_ENTRY_H2015 &OD->list[46]
#define OD_ENTRY_H2016 &OD->list[47]
#define OD_ENTRY_H2019 &OD->list[48]
#define OD_ENTRY_H201A &OD->list[49]
#define OD_ENTRY_H201B &OD->list[50]
#define OD_ENTRY_H2024 &OD->list[51]
#define OD_ENTRY_H202F &OD->list[52]
#define OD_ENTRY_H2030 &OD->list[53]
#define OD_ENTRY_H2031 &OD->list[54]
#define OD_ENTRY_H2032 &OD->list[55]
#define OD_ENTRY_H2033 &OD->list[56]


/*******************************************************************************
    Object dictionary entries - shortcuts with names
*******************************************************************************/
#define OD_ENTRY_H1000_deviceType &OD->list[0]
#define OD_ENTRY_H1001_errorRegister &OD->list[1]
#define OD_ENTRY_H1003_pre_definedErrorField &OD->list[2]
#define OD_ENTRY_H1008_manufacturerDeviceName &OD->list[3]
#define OD_ENTRY_H1009_manufacturerHardwareVersion &OD->list[4]
#define OD_ENTRY_H100A_manufacturerSoftwareVersion &OD->list[5]
#define OD_ENTRY_H100B_object_100BhModelID &OD->list[6]
#define OD_ENTRY_H1014_COB_ID_EMCY &OD->list[7]
#define OD_ENTRY_H1015_inhibitTimeEMCY &OD->list[8]
#define OD_ENTRY_H1017_producerHeartbeatTime &OD->list[9]
#define OD_ENTRY_H1018_identity &OD->list[10]
#define OD_ENTRY_H1400_RPDOCommunicationParameter &OD->list[11]
#define OD_ENTRY_H1401_RPDOCommunicationParameter &OD->list[12]
#define OD_ENTRY_H1402_RPDOCommunicationParameter &OD->list[13]
#define OD_ENTRY_H1403_RPDOCommunicationParameter &OD->list[14]
#define OD_ENTRY_H1600_RPDOMappingParameter &OD->list[15]
#define OD_ENTRY_H1601_RPDOMappingParameter &OD->list[16]
#define OD_ENTRY_H1602_RPDOMappingParameter &OD->list[17]
#define OD_ENTRY_H1603_RPDOMappingParameter &OD->list[18]
#define OD_ENTRY_H1800_TPDOCommunicationParameter &OD->list[19]
#define OD_ENTRY_H1801_TPDOCommunicationParameter &OD->list[20]
#define OD_ENTRY_H1802_TPDOCommunicationParameter &OD->list[21]
#define OD_ENTRY_H1A00_TPDOMappingParameter &OD->list[22]
#define OD_ENTRY_H1A01_TPDOMappingParameter &OD->list[23]
#define OD_ENTRY_H1A02_TPDOMappingParameter &OD->list[24]
#define OD_ENTRY_H2000_virtualChannelV1__V7 &OD->list[25]
#define OD_ENTRY_H2001_virtualChannelV8__V14 &OD->list[26]
#define OD_ENTRY_H2002_virtualChannelV15_V17 &OD->list[27]
#define OD_ENTRY_H2003_errorRegisterCH28 &OD->list[28]
#define OD_ENTRY_H2004_DACH_PARAMETR &OD->list[29]
#define OD_ENTRY_H2005_AIN_RPM &OD->list[30]
#define OD_ENTRY_H2006_DIN_DATA &OD->list[31]
#define OD_ENTRY_H2007_BIG_SEG_CONFIG &OD->list[32]
#define OD_ENTRY_H2008_RGB_MAP_REGISTER &OD->list[33]
#define OD_ENTRY_H2009_RGB1_SETUP_REGISTER &OD->list[34]
#define OD_ENTRY_H200A_RGB2_SETUP_REGISTER &OD->list[35]
#define OD_ENTRY_H200B_RGB3_SETUP_REGISTER &OD->list[36]
#define OD_ENTRY_H200C_RGB4_SETUP_REGISTER &OD->list[37]
#define OD_ENTRY_H200D_RGB5_SETUP_REGISTER &OD->list[38]
#define OD_ENTRY_H200E_RGB6_SETUP_REGISTER &OD->list[39]
#define OD_ENTRY_H200F_RGB7_SETUP_REGISTER &OD->list[40]
#define OD_ENTRY_H2010_RGB8_SETUP_REGISTER &OD->list[41]
#define OD_ENTRY_H2011_RGB9_SETUP_REGISTER &OD->list[42]
#define OD_ENTRY_H2012_RGB10_SETUP_REGISTER &OD->list[43]
#define OD_ENTRY_H2013_RGB11_SETUP_REGISTER &OD->list[44]
#define OD_ENTRY_H2014_RGB12_SETUP_REGISTER &OD->list[45]
#define OD_ENTRY_H2015_RGB13_SETUP_REGISTER &OD->list[46]
#define OD_ENTRY_H2016_RGB14_SETUP_REGISTER &OD->list[47]
#define OD_ENTRY_H2019_BAR_SETUP_REGISTER &OD->list[48]
#define OD_ENTRY_H201A_MENU_MAP_REGISTER &OD->list[49]
#define OD_ENTRY_H201B_MENU_SETUP_REGISTER &OD->list[50]
#define OD_ENTRY_H2024_baudRateSetting &OD->list[51]
#define OD_ENTRY_H202F_brigthRegister &OD->list[52]
#define OD_ENTRY_H2030_ADC_1_CalibraionRegister &OD->list[53]
#define OD_ENTRY_H2031_ADC_2_CalibraionRegister &OD->list[54]
#define OD_ENTRY_H2032_ADC_3_CalibraionRegister &OD->list[55]
#define OD_ENTRY_H2033_RPM_CalibrationRegister &OD->list[56]


/*******************************************************************************
    OD config structure
*******************************************************************************/
#ifdef CO_MULTIPLE_OD
#define OD_INIT_CONFIG(config) {\
    (config).CNT_NMT = OD_CNT_NMT;\
    (config).ENTRY_H1017 = OD_ENTRY_H1017;\
    (config).CNT_HB_CONS = 0;\
    (config).CNT_ARR_1016 = OD_CNT_ARR_1016;\
    (config).ENTRY_H1016 = OD_ENTRY_H1016;\
    (config).CNT_EM = OD_CNT_EM;\
    (config).ENTRY_H1001 = OD_ENTRY_H1001;\
    (config).ENTRY_H1014 = OD_ENTRY_H1014;\
    (config).ENTRY_H1015 = OD_ENTRY_H1015;\
    (config).CNT_ARR_1003 = OD_CNT_ARR_1003;\
    (config).ENTRY_H1003 = OD_ENTRY_H1003;\
    (config).CNT_SDO_SRV = 0;\
    (config).ENTRY_H1200 = OD_ENTRY_H1200;\
    (config).CNT_SDO_CLI = 0;\
    (config).ENTRY_H1280 = OD_ENTRY_H1280;\
    (config).CNT_TIME = 0;\
    (config).ENTRY_H1012 = OD_ENTRY_H1012;\
    (config).CNT_SYNC = 0;\
    (config).ENTRY_H1005 = OD_ENTRY_H1005;\
    (config).ENTRY_H1006 = OD_ENTRY_H1006;\
    (config).ENTRY_H1007 = OD_ENTRY_H1007;\
    (config).ENTRY_H1019 = OD_ENTRY_H1019;\
    (config).CNT_RPDO = 0;\
    (config).ENTRY_H1400 = OD_ENTRY_H1400;\
    (config).ENTRY_H1600 = OD_ENTRY_H1600;\
    (config).CNT_TPDO = 0;\
    (config).ENTRY_H1800 = OD_ENTRY_H1800;\
    (config).ENTRY_H1A00 = OD_ENTRY_H1A00;\
    (config).CNT_LEDS = 0;\
    (config).CNT_GFC = 0;\
    (config).ENTRY_H1300 = NULL;\
    (config).CNT_SRDO = 0;\
    (config).ENTRY_H1301 = NULL;\
    (config).ENTRY_H1381 = NULL;\
    (config).ENTRY_H13FE = NULL;\
    (config).ENTRY_H13FF = NULL;\
    (config).CNT_LSS_SLV = 0;\
    (config).CNT_LSS_MST = 0;\
    (config).CNT_GTWA = 0;\
    (config).CNT_TRACE = 0;\
}
#endif

#endif /* OD_H */
