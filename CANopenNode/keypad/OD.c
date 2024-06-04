/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode V4

    This file was automatically generated by CANopenEditor v4.0-51-g2d9b1ad

    https://github.com/CANopenNode/CANopenNode
    https://github.com/CANopenNode/CANopenEditor

    DON'T EDIT THIS FILE MANUALLY, UNLESS YOU KNOW WHAT YOU ARE DOING !!!!
*******************************************************************************/

#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This Object dictionary is compatible with CANopenNode V4.0 and above!
#endif

/*******************************************************************************
    OD data initialization of all groups
*******************************************************************************/
OD_ATTR_ROM OD_ROM_t OD_ROM = {
    .x1000_deviceType = 0x00000000,
    .x1008_manufacturerDeviceName = {'C', 'A', 'N', 'o', 'p', 'e', 'n', 'N', 'o', 'd', 'e', 0},
    .x1009_manufacturerHardwareVersion = {'3', '.', '0', '0', 0},
    .x100A_manufacturerSoftwareVersion = {'3', '.', '0', '0', 0},
    .x1018_identity = {
        .maxSub_index = 0x04,
        .vendor_ID = 0x00000000,
        .productCode = 0x00000000,
        .revisionNumber = 0x00000000,
        .serialNumber = 0x00000000
    },
    .x1401_RPDOCommunicationParameter = {
        .maxSub_index = 0x06,
        .COB_IDUsedByRPDO = 0x00000300,
        .transmissionType = 0xFE
    },
    .x1402_RPDOCommunicationParameter = {
        .maxSub_index = 0x06,
        .COB_IDUsedByRPDO = 0x00000400,
        .transmissionType = 0xFE
    },
    .x1403_RPDOCommunicationParameter = {
        .maxSub_index = 0x06,
        .COB_IDUsedByRPDO = 0x00000500,
        .transmissionType = 0xFE
    },
    .x1601_RPDOMappingParameter = {
        .numberOfMappedObjects = 0x06,
        .mappedObject_1 = 0x20000308,
        .mappedObject_2 = 0x20000408,
        .mappedObject_3 = 0x20000508,
        .mappedObject_4 = 0x20000608,
        .mappedObject_5 = 0x20000708,
        .mappedObject_6 = 0x20010108
    },
    .x1602_RPDOMappingParameter = {
        .numberOfMappedObjects = 0x06,
        .mappedObject_1 = 0x20010208,
        .mappedObject_2 = 0x20010308,
        .mappedObject_3 = 0x20010408,
        .mappedObject_4 = 0x20010508,
        .mappedObject_5 = 0x20010608,
        .mappedObject_6 = 0x20010708
    },
    .x1603_RPDOMappingParameter = {
        .numberOfMappedObjects = 0x03,
        .mappedObject_1 = 0x20020110,
        .mappedObject_2 = 0x20020210,
        .mappedObject_3 = 0x20020310
    },
    .x1800_TPDOCommunicationParameter = {
        .maxSub_index = 0x05,
        .COB_IDUsedByTPDO = 0x00000180,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1A00_TPDOMappingParameter = {
        .numberOfMappedObjects = 0x05,
        .mappedObject_1 = 0x20050110,
        .mappedObject_2 = 0x20050210,
        .mappedObject_3 = 0x20050310,
        .mappedObject_4 = 0x00020008,
        .mappedObject_5 = 0x00020008
    },
    .x2006_DIN_DATA_sub0 = 0x02,
    .x2007_BIG_SEG_CONFIG_sub0 = 0x0A,
    .x2008_RGB_MAP_REGISTER_sub0 = 0x0F,
    .x2009_RGB1_SETUP_REGISTER_sub0 = 0x06,
    .x2009_RGB1_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200A_RGB2_SETUP_REGISTER_sub0 = 0x06,
    .x200A_RGB2_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200B_RGB3_SETUP_REGISTER_sub0 = 0x06,
    .x200B_RGB3_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200C_RGB4_SETUP_REGISTER_sub0 = 0x06,
    .x200C_RGB4_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200D_RGB5_SETUP_REGISTER_sub0 = 0x06,
    .x200D_RGB5_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200E_RGB6_SETUP_REGISTER_sub0 = 0x06,
    .x200E_RGB6_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x200F_RGB7_SETUP_REGISTER_sub0 = 0x06,
    .x200F_RGB7_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2010_RGB8_SETUP_REGISTER_sub0 = 0x06,
    .x2010_RGB8_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2011_RGB9_SETUP_REGISTER_sub0 = 0x06,
    .x2011_RGB9_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2012_RGB10_SETUP_REGISTER_sub0 = 0x06,
    .x2012_RGB10_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2013_RGB11_SETUP_REGISTER_sub0 = 0x06,
    .x2013_RGB11_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2014_RGB12_SETUP_REGISTER_sub0 = 0x06,
    .x2014_RGB12_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2015_RGB13_SETUP_REGISTER_sub0 = 0x06,
    .x2015_RGB13_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2016_RGB14_SETUP_REGISTER_sub0 = 0x06,
    .x2016_RGB14_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x2019_BAR_SETUP_REGISTER_sub0 = 0x07,
    .x2019_BAR_SETUP_REGISTER = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    .x201A_MENU_MAP_REGISTER_sub0 = 0x0A,
    .x201A_MENU_MAP_REGISTER = {0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF},
    .x201B_MENU_SETUP_REGISTER_sub0 = 0x03,
    .x202F_brigthRegister_sub0 = 0x02,
    .x2030_ADC_1_CalibraionRegister_sub0 = 0x1F,
    .x2031_ADC_2_CalibraionRegister_sub0 = 0x1F,
    .x2032_ADC_3_CalibraionRegister_sub0 = 0x1F,
    .x2033_RPM_CalibrationRegister_sub0 = 0x02
};

OD_ATTR_RAM OD_RAM_t OD_RAM = {
    .x1001_errorRegister = 0x00,
    .x100B_object_100BhModelID = {'s', 'i', 'd', 'e', 'r', ' ', 'k', 'e', 'y', 'p', 'a', 'd', ' ', '8', 0},
    .x1400_RPDOCommunicationParameter = {
        .maxSub_index = 0x06,
        .COB_IDUsedByRPDO = 0x00000200,
        .transmissionType = 0xFE
    },
    .x1600_RPDOMappingParameter = {
        .numberOfMappedObjects = 0x03,
        .mappedObject_1 = 0x20030020,
        .mappedObject_2 = 0x20000108,
        .mappedObject_3 = 0x20000208
    },
    .x2000_virtualChannelV1__V7_sub0 = 0x07,
    .x2001_virtualChannelV8__V14_sub0 = 0x07,
    .x2002_virtualChannelV15_V17_sub0 = 0x03,
    .x2004_DACH_PARAMETR_sub0 = 0x03,
    .x2005_AIN_RPM_sub0 = 0x06
};

OD_ATTR_PERSIST_COMM OD_PERSIST_COMM_t OD_PERSIST_COMM = {
    .x1014_COB_ID_EMCY = 0x00000080,
    .x1015_inhibitTimeEMCY = 0x0000,
    .x1017_producerHeartbeatTime = 0x0000
};

OD_ATTR_ OD__t OD_ = {
    .x1801_TPDOCommunicationParameter = {
        .maxSub_index = 0x05,
        .COB_IDUsedByTPDO = 0x00000280,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1802_TPDOCommunicationParameter = {
        .maxSub_index = 0x05,
        .COB_IDUsedByTPDO = 0x00000380,
        .transmissionType = 0xFE,
        .eventTimer = 0x0000
    },
    .x1A01_TPDOMappingParameter = {
        .numberOfMappedObjects = 0x03,
        .mappedObject_1 = 0x20050410,
        .mappedObject_2 = 0x20050510,
        .mappedObject_3 = 0x20050610
    },
    .x1A02_TPDOMappingParameter = {
        .numberOfMappedObjects = 0x02,
        .mappedObject_1 = 0x20060208,
        .mappedObject_2 = 0x20060108
    }
};



/*******************************************************************************
    All OD objects (constant definitions)
*******************************************************************************/
typedef struct {
    OD_obj_var_t o_1000_deviceType;
    OD_obj_var_t o_1001_errorRegister;
    OD_obj_array_t o_1003_pre_definedErrorField;
    OD_obj_var_t o_1008_manufacturerDeviceName;
    OD_obj_var_t o_1009_manufacturerHardwareVersion;
    OD_obj_var_t o_100A_manufacturerSoftwareVersion;
    OD_obj_var_t o_100B_object_100BhModelID;
    OD_obj_var_t o_1014_COB_ID_EMCY;
    OD_obj_var_t o_1015_inhibitTimeEMCY;
    OD_obj_var_t o_1017_producerHeartbeatTime;
    OD_obj_record_t o_1018_identity[5];
    OD_obj_record_t o_1400_RPDOCommunicationParameter[3];
    OD_obj_record_t o_1401_RPDOCommunicationParameter[3];
    OD_obj_record_t o_1402_RPDOCommunicationParameter[3];
    OD_obj_record_t o_1403_RPDOCommunicationParameter[3];
    OD_obj_record_t o_1600_RPDOMappingParameter[4];
    OD_obj_record_t o_1601_RPDOMappingParameter[7];
    OD_obj_record_t o_1602_RPDOMappingParameter[7];
    OD_obj_record_t o_1603_RPDOMappingParameter[4];
    OD_obj_record_t o_1800_TPDOCommunicationParameter[4];
    OD_obj_record_t o_1801_TPDOCommunicationParameter[4];
    OD_obj_record_t o_1802_TPDOCommunicationParameter[4];
    OD_obj_record_t o_1A00_TPDOMappingParameter[6];
    OD_obj_record_t o_1A01_TPDOMappingParameter[4];
    OD_obj_record_t o_1A02_TPDOMappingParameter[3];
    OD_obj_array_t o_2000_virtualChannelV1__V7;
    OD_obj_array_t o_2001_virtualChannelV8__V14;
    OD_obj_array_t o_2002_virtualChannelV15_V17;
    OD_obj_var_t o_2003_errorRegisterCH28;
    OD_obj_array_t o_2004_DACH_PARAMETR;
    OD_obj_array_t o_2005_AIN_RPM;
    OD_obj_array_t o_2006_DIN_DATA;
    OD_obj_array_t o_2007_BIG_SEG_CONFIG;
    OD_obj_array_t o_2008_RGB_MAP_REGISTER;
    OD_obj_array_t o_2009_RGB1_SETUP_REGISTER;
    OD_obj_array_t o_200A_RGB2_SETUP_REGISTER;
    OD_obj_array_t o_200B_RGB3_SETUP_REGISTER;
    OD_obj_array_t o_200C_RGB4_SETUP_REGISTER;
    OD_obj_array_t o_200D_RGB5_SETUP_REGISTER;
    OD_obj_array_t o_200E_RGB6_SETUP_REGISTER;
    OD_obj_array_t o_200F_RGB7_SETUP_REGISTER;
    OD_obj_array_t o_2010_RGB8_SETUP_REGISTER;
    OD_obj_array_t o_2011_RGB9_SETUP_REGISTER;
    OD_obj_array_t o_2012_RGB10_SETUP_REGISTER;
    OD_obj_array_t o_2013_RGB11_SETUP_REGISTER;
    OD_obj_array_t o_2014_RGB12_SETUP_REGISTER;
    OD_obj_array_t o_2015_RGB13_SETUP_REGISTER;
    OD_obj_array_t o_2016_RGB14_SETUP_REGISTER;
    OD_obj_array_t o_2019_BAR_SETUP_REGISTER;
    OD_obj_array_t o_201A_MENU_MAP_REGISTER;
    OD_obj_array_t o_201B_MENU_SETUP_REGISTER;
    OD_obj_var_t o_2024_baudRateSetting;
    OD_obj_array_t o_202F_brigthRegister;
    OD_obj_array_t o_2030_ADC_1_CalibraionRegister;
    OD_obj_array_t o_2031_ADC_2_CalibraionRegister;
    OD_obj_array_t o_2032_ADC_3_CalibraionRegister;
    OD_obj_array_t o_2033_RPM_CalibrationRegister;
} ODObjs_t;

static CO_PROGMEM ODObjs_t ODObjs = {
    .o_1000_deviceType = {
        .dataOrig = &OD_ROM.x1000_deviceType,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataLength = 4
    },
    .o_1001_errorRegister = {
        .dataOrig = &OD_RAM.x1001_errorRegister,
        .attribute = ODA_SDO_R,
        .dataLength = 1
    },
    .o_1003_pre_definedErrorField = {
        .dataOrig0 = NULL,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_RW,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1008_manufacturerDeviceName = {
        .dataOrig = &OD_ROM.x1008_manufacturerDeviceName[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 11
    },
    .o_1009_manufacturerHardwareVersion = {
        .dataOrig = &OD_ROM.x1009_manufacturerHardwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 4
    },
    .o_100A_manufacturerSoftwareVersion = {
        .dataOrig = &OD_ROM.x100A_manufacturerSoftwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 4
    },
    .o_100B_object_100BhModelID = {
        .dataOrig = &OD_RAM.x100B_object_100BhModelID[0],
        .attribute = ODA_SDO_RW | ODA_STR,
        .dataLength = 14
    },
    .o_1014_COB_ID_EMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1014_COB_ID_EMCY,
        .attribute = ODA_MB,
        .dataLength = 4
    },
    .o_1015_inhibitTimeEMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1015_inhibitTimeEMCY,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1017_producerHeartbeatTime = {
        .dataOrig = &OD_PERSIST_COMM.x1017_producerHeartbeatTime,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1018_identity = {
        {
            .dataOrig = &OD_ROM.x1018_identity.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.vendor_ID,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.productCode,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.revisionNumber,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.serialNumber,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1400_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_RAM.x1400_RPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1400_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1400_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        }
    },
    .o_1401_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_ROM.x1401_RPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1401_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1401_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        }
    },
    .o_1402_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_ROM.x1402_RPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1402_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1402_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        }
    },
    .o_1403_RPDOCommunicationParameter = {
        {
            .dataOrig = &OD_ROM.x1403_RPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1403_RPDOCommunicationParameter.COB_IDUsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1403_RPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        }
    },
    .o_1600_RPDOMappingParameter = {
        {
            .dataOrig = &OD_RAM.x1600_RPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1600_RPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1600_RPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1600_RPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1601_RPDOMappingParameter = {
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1601_RPDOMappingParameter.mappedObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1602_RPDOMappingParameter = {
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1602_RPDOMappingParameter.mappedObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1603_RPDOMappingParameter = {
        {
            .dataOrig = &OD_ROM.x1603_RPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1603_RPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1603_RPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1603_RPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1800_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_ROM.x1800_TPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1800_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1800_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1800_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1801_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_.x1801_TPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1801_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_.x1801_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1801_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1802_TPDOCommunicationParameter = {
        {
            .dataOrig = &OD_.x1802_TPDOCommunicationParameter.maxSub_index,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1802_TPDOCommunicationParameter.COB_IDUsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_.x1802_TPDOCommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1802_TPDOCommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        }
    },
    .o_1A00_TPDOMappingParameter = {
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.mappedObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1A00_TPDOMappingParameter.mappedObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1A01_TPDOMappingParameter = {
        {
            .dataOrig = &OD_.x1A01_TPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1A01_TPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_.x1A01_TPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_.x1A01_TPDOMappingParameter.mappedObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_1A02_TPDOMappingParameter = {
        {
            .dataOrig = &OD_.x1A02_TPDOMappingParameter.numberOfMappedObjects,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_.x1A02_TPDOMappingParameter.mappedObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_.x1A02_TPDOMappingParameter.mappedObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        }
    },
    .o_2000_virtualChannelV1__V7 = {
        .dataOrig0 = &OD_RAM.x2000_virtualChannelV1__V7_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_W | ODA_RPDO,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2001_virtualChannelV8__V14 = {
        .dataOrig0 = &OD_RAM.x2001_virtualChannelV8__V14_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_W | ODA_RPDO,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2002_virtualChannelV15_V17 = {
        .dataOrig0 = &OD_RAM.x2002_virtualChannelV15_V17_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_W | ODA_RPDO | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(int16_t)
    },
    .o_2003_errorRegisterCH28 = {
        .dataOrig = NULL,
        .attribute = ODA_SDO_R | ODA_RPDO | ODA_MB,
        .dataLength = 4
    },
    .o_2004_DACH_PARAMETR = {
        .dataOrig0 = &OD_RAM.x2004_DACH_PARAMETR_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(int32_t)
    },
    .o_2005_AIN_RPM = {
        .dataOrig0 = &OD_RAM.x2005_AIN_RPM_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(int16_t)
    },
    .o_2006_DIN_DATA = {
        .dataOrig0 = &OD_ROM.x2006_DIN_DATA_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2007_BIG_SEG_CONFIG = {
        .dataOrig0 = &OD_ROM.x2007_BIG_SEG_CONFIG_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(int16_t)
    },
    .o_2008_RGB_MAP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2008_RGB_MAP_REGISTER_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2009_RGB1_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2009_RGB1_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2009_RGB1_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200A_RGB2_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200A_RGB2_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200A_RGB2_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200B_RGB3_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200B_RGB3_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200B_RGB3_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200C_RGB4_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200C_RGB4_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200C_RGB4_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200D_RGB5_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200D_RGB5_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200D_RGB5_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200E_RGB6_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200E_RGB6_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200E_RGB6_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_200F_RGB7_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x200F_RGB7_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x200F_RGB7_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2010_RGB8_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2010_RGB8_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2010_RGB8_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2011_RGB9_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2011_RGB9_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2011_RGB9_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2012_RGB10_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2012_RGB10_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2012_RGB10_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2013_RGB11_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2013_RGB11_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2013_RGB11_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2014_RGB12_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2014_RGB12_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2014_RGB12_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2015_RGB13_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2015_RGB13_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2015_RGB13_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2016_RGB14_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2016_RGB14_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2016_RGB14_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_2019_BAR_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x2019_BAR_SETUP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x2019_BAR_SETUP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    },
    .o_201A_MENU_MAP_REGISTER = {
        .dataOrig0 = &OD_ROM.x201A_MENU_MAP_REGISTER_sub0,
        .dataOrig = &OD_ROM.x201A_MENU_MAP_REGISTER[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_201B_MENU_SETUP_REGISTER = {
        .dataOrig0 = &OD_ROM.x201B_MENU_SETUP_REGISTER_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2024_baudRateSetting = {
        .dataOrig = NULL,
        .attribute = ODA_SDO_W,
        .dataLength = 1
    },
    .o_202F_brigthRegister = {
        .dataOrig0 = &OD_ROM.x202F_brigthRegister_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_2030_ADC_1_CalibraionRegister = {
        .dataOrig0 = &OD_ROM.x2030_ADC_1_CalibraionRegister_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_2031_ADC_2_CalibraionRegister = {
        .dataOrig0 = &OD_ROM.x2031_ADC_2_CalibraionRegister_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_2032_ADC_3_CalibraionRegister = {
        .dataOrig0 = &OD_ROM.x2032_ADC_3_CalibraionRegister_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_2033_RPM_CalibrationRegister = {
        .dataOrig0 = &OD_ROM.x2033_RPM_CalibrationRegister_sub0,
        .dataOrig = NULL,
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 2,
        .dataElementSizeof = sizeof(uint16_t)
    }
};


/*******************************************************************************
    Object dictionary
*******************************************************************************/
static OD_ATTR_OD OD_entry_t ODList[] = {
    {0x1000, 0x01, ODT_VAR, &ODObjs.o_1000_deviceType, NULL},
    {0x1001, 0x01, ODT_VAR, &ODObjs.o_1001_errorRegister, NULL},
    {0x1003, 0x11, ODT_ARR, &ODObjs.o_1003_pre_definedErrorField, NULL},
    {0x1008, 0x01, ODT_VAR, &ODObjs.o_1008_manufacturerDeviceName, NULL},
    {0x1009, 0x01, ODT_VAR, &ODObjs.o_1009_manufacturerHardwareVersion, NULL},
    {0x100A, 0x01, ODT_VAR, &ODObjs.o_100A_manufacturerSoftwareVersion, NULL},
    {0x100B, 0x01, ODT_VAR, &ODObjs.o_100B_object_100BhModelID, NULL},
    {0x1014, 0x01, ODT_VAR, &ODObjs.o_1014_COB_ID_EMCY, NULL},
    {0x1015, 0x01, ODT_VAR, &ODObjs.o_1015_inhibitTimeEMCY, NULL},
    {0x1017, 0x01, ODT_VAR, &ODObjs.o_1017_producerHeartbeatTime, NULL},
    {0x1018, 0x05, ODT_REC, &ODObjs.o_1018_identity, NULL},
    {0x1400, 0x03, ODT_REC, &ODObjs.o_1400_RPDOCommunicationParameter, NULL},
    {0x1401, 0x03, ODT_REC, &ODObjs.o_1401_RPDOCommunicationParameter, NULL},
    {0x1402, 0x03, ODT_REC, &ODObjs.o_1402_RPDOCommunicationParameter, NULL},
    {0x1403, 0x03, ODT_REC, &ODObjs.o_1403_RPDOCommunicationParameter, NULL},
    {0x1600, 0x04, ODT_REC, &ODObjs.o_1600_RPDOMappingParameter, NULL},
    {0x1601, 0x07, ODT_REC, &ODObjs.o_1601_RPDOMappingParameter, NULL},
    {0x1602, 0x07, ODT_REC, &ODObjs.o_1602_RPDOMappingParameter, NULL},
    {0x1603, 0x04, ODT_REC, &ODObjs.o_1603_RPDOMappingParameter, NULL},
    {0x1800, 0x04, ODT_REC, &ODObjs.o_1800_TPDOCommunicationParameter, NULL},
    {0x1801, 0x04, ODT_REC, &ODObjs.o_1801_TPDOCommunicationParameter, NULL},
    {0x1802, 0x04, ODT_REC, &ODObjs.o_1802_TPDOCommunicationParameter, NULL},
    {0x1A00, 0x06, ODT_REC, &ODObjs.o_1A00_TPDOMappingParameter, NULL},
    {0x1A01, 0x04, ODT_REC, &ODObjs.o_1A01_TPDOMappingParameter, NULL},
    {0x1A02, 0x03, ODT_REC, &ODObjs.o_1A02_TPDOMappingParameter, NULL},
    {0x2000, 0x08, ODT_ARR, &ODObjs.o_2000_virtualChannelV1__V7, NULL},
    {0x2001, 0x08, ODT_ARR, &ODObjs.o_2001_virtualChannelV8__V14, NULL},
    {0x2002, 0x04, ODT_ARR, &ODObjs.o_2002_virtualChannelV15_V17, NULL},
    {0x2003, 0x01, ODT_VAR, &ODObjs.o_2003_errorRegisterCH28, NULL},
    {0x2004, 0x04, ODT_ARR, &ODObjs.o_2004_DACH_PARAMETR, NULL},
    {0x2005, 0x07, ODT_ARR, &ODObjs.o_2005_AIN_RPM, NULL},
    {0x2006, 0x03, ODT_ARR, &ODObjs.o_2006_DIN_DATA, NULL},
    {0x2007, 0x0B, ODT_ARR, &ODObjs.o_2007_BIG_SEG_CONFIG, NULL},
    {0x2008, 0x10, ODT_ARR, &ODObjs.o_2008_RGB_MAP_REGISTER, NULL},
    {0x2009, 0x07, ODT_ARR, &ODObjs.o_2009_RGB1_SETUP_REGISTER, NULL},
    {0x200A, 0x07, ODT_ARR, &ODObjs.o_200A_RGB2_SETUP_REGISTER, NULL},
    {0x200B, 0x07, ODT_ARR, &ODObjs.o_200B_RGB3_SETUP_REGISTER, NULL},
    {0x200C, 0x07, ODT_ARR, &ODObjs.o_200C_RGB4_SETUP_REGISTER, NULL},
    {0x200D, 0x07, ODT_ARR, &ODObjs.o_200D_RGB5_SETUP_REGISTER, NULL},
    {0x200E, 0x07, ODT_ARR, &ODObjs.o_200E_RGB6_SETUP_REGISTER, NULL},
    {0x200F, 0x07, ODT_ARR, &ODObjs.o_200F_RGB7_SETUP_REGISTER, NULL},
    {0x2010, 0x07, ODT_ARR, &ODObjs.o_2010_RGB8_SETUP_REGISTER, NULL},
    {0x2011, 0x07, ODT_ARR, &ODObjs.o_2011_RGB9_SETUP_REGISTER, NULL},
    {0x2012, 0x07, ODT_ARR, &ODObjs.o_2012_RGB10_SETUP_REGISTER, NULL},
    {0x2013, 0x07, ODT_ARR, &ODObjs.o_2013_RGB11_SETUP_REGISTER, NULL},
    {0x2014, 0x07, ODT_ARR, &ODObjs.o_2014_RGB12_SETUP_REGISTER, NULL},
    {0x2015, 0x07, ODT_ARR, &ODObjs.o_2015_RGB13_SETUP_REGISTER, NULL},
    {0x2016, 0x07, ODT_ARR, &ODObjs.o_2016_RGB14_SETUP_REGISTER, NULL},
    {0x2019, 0x08, ODT_ARR, &ODObjs.o_2019_BAR_SETUP_REGISTER, NULL},
    {0x201A, 0x0B, ODT_ARR, &ODObjs.o_201A_MENU_MAP_REGISTER, NULL},
    {0x201B, 0x04, ODT_ARR, &ODObjs.o_201B_MENU_SETUP_REGISTER, NULL},
    {0x2024, 0x01, ODT_VAR, &ODObjs.o_2024_baudRateSetting, NULL},
    {0x202F, 0x03, ODT_ARR, &ODObjs.o_202F_brigthRegister, NULL},
    {0x2030, 0x20, ODT_ARR, &ODObjs.o_2030_ADC_1_CalibraionRegister, NULL},
    {0x2031, 0x20, ODT_ARR, &ODObjs.o_2031_ADC_2_CalibraionRegister, NULL},
    {0x2032, 0x20, ODT_ARR, &ODObjs.o_2032_ADC_3_CalibraionRegister, NULL},
    {0x2033, 0x03, ODT_ARR, &ODObjs.o_2033_RPM_CalibrationRegister, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;
