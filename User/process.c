/*
 * process.c
 *
 *  Created on: Nov 12, 2021
 *      Author: igor.dymov
 */

#include "process.h"



static ODR_t OD_writeBAR(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);


static ODR_t OD_writeSEG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeV1_14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readDashParam (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeDashParam(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readAIN_RPM (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readDIN (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t  OD_writeMenuMap(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readMenuMap (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t  OD_writeMenuSetup(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readMenuSetup (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readSEG (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGBMAP (uint16_t addr, OD_stream_t *stream, void *buf, OD_size_t *countRead);
static ODR_t OD_writeRGBMAP(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readRGB1 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB2 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB3 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB4 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB5 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB6 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB7 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB8 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB9 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB10 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB11 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB12 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB13 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readRGB14 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeRGB1(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB2(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB3(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB4(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB5(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB6(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB7(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB8(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB9(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB10(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB11(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB12(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB13(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRGB14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readBar (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeADC1(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeADC2(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeADC3(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readADC1 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readADC2 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_readADC3 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeBoardSettings(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readBoardSettings(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeRPMConfig(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readRPMConfig (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
/* Variables used for triggering TPDO, see simulation in app_programRt(). */


const OD_extension_t OD_VRegiters_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeV1_14
};



const OD_extension_t  OD_DASH_PARAM_extension = {
       .read =  OD_readDashParam,
        .write = OD_writeDashParam,
    };


const OD_extension_t OD_SEG_extension = {
    .object = NULL,
    .read =  OD_readSEG ,
    .write = OD_writeSEG
};

const OD_extension_t OD_RGBMAP_extension = {
    .object = NULL,
    .read =  OD_readRGBMAP,
    .write = OD_writeRGBMAP
};


const OD_extension_t OD_RGB1_extension = {
    .object = NULL,
    .read =  OD_readRGB1,
    .write = OD_writeRGB1
};

const OD_extension_t OD_RGB2_extension = {
    .object = NULL,
    .read =  OD_readRGB2,
    .write = OD_writeRGB2
};

const OD_extension_t OD_RGB3_extension = {
    .object = NULL,
    .read =  OD_readRGB3,
    .write = OD_writeRGB3
};

const OD_extension_t OD_RGB4_extension = {
    .object = NULL,
    .read =  OD_readRGB4,
    .write = OD_writeRGB4
};

const OD_extension_t OD_RGB5_extension = {
    .object = NULL,
    .read =  OD_readRGB5,
    .write = OD_writeRGB5
};

const OD_extension_t OD_RGB6_extension = {
    .object = NULL,
    .read =  OD_readRGB6,
    .write = OD_writeRGB6
};

const OD_extension_t OD_RGB7_extension = {
    .object = NULL,
    .read =  OD_readRGB7,
    .write = OD_writeRGB7
};

const OD_extension_t OD_RGB8_extension = {
    .object = NULL,
    .read =  OD_readRGB8,
    .write = OD_writeRGB8
};

const OD_extension_t OD_RGB9_extension = {
    .object = NULL,
    .read =  OD_readRGB9,
    .write = OD_writeRGB9
};

const OD_extension_t OD_RGB10_extension = {
    .object = NULL,
    .read =  OD_readRGB10,
    .write = OD_writeRGB10
};

const OD_extension_t OD_RGB11_extension = {
    .object = NULL,
    .read =  OD_readRGB11,
    .write = OD_writeRGB11
};

const OD_extension_t OD_RGB12_extension = {
    .object = NULL,
    .read =  OD_readRGB12,
    .write = OD_writeRGB12
};

const OD_extension_t OD_RGB13_extension = {
    .object = NULL,
    .read =  OD_readRGB13,
    .write = OD_writeRGB13
};

const OD_extension_t OD_RGB14_extension = {
    .object = NULL,
    .read =  OD_readRGB14,
    .write = OD_writeRGB14
};





const OD_extension_t OD_BAR_extension = {
    .object = NULL,
    .read =  OD_readBar,
    .write = OD_writeBAR
};

const OD_extension_t  OD_AIN_RPM_extension = {
        .object = NULL,
        .read =  OD_readAIN_RPM,
        .write = OD_writeOriginal
    };



const OD_extension_t  OD_DIN_extension= {
        .object = NULL,
        .read =  OD_readDIN,
        .write = NULL
    };

const OD_extension_t  OD_MENU_MAP_extension= {
        .object = NULL,
        .read =  OD_readMenuMap ,
        .write = OD_writeMenuMap
    };

const OD_extension_t  OD_MENU_SETUP_extension= {
        .object = NULL,
        .read =  OD_readMenuSetup,
        .write = OD_writeMenuSetup
    };

const OD_extension_t  OD_BOARD_SETTINGS_extension= {
        .object = NULL,
        .read =  OD_readBoardSettings,
        .write = OD_writeBoardSettings
    };

const OD_extension_t OD_ADC1_CAL_extension = {
    .object = NULL,
    .read =  OD_readADC1,
    .write = OD_writeADC1
};

const OD_extension_t OD_ADC2_CAL_extension = {
    .object = NULL,
    .read =  OD_readADC2,
    .write = OD_writeADC2
};

const OD_extension_t OD_ADC3_CAL_extension = {
    .object = NULL,
    .read =  OD_readADC3,
    .write = OD_writeADC3
};

const OD_extension_t  OD_RPMCONFIG_extension = {
        .object = NULL,
        .read =  OD_readRPMConfig,
        .write = OD_writeRPMConfig
    };

void vProceesInit( void)
{
    OD_extension_init(OD_ENTRY_H2001, &OD_VRegiters_extension);
    OD_extension_init(OD_ENTRY_H2004, &OD_DASH_PARAM_extension);
    OD_extension_init(OD_ENTRY_H2005, &OD_AIN_RPM_extension);
    OD_extension_init(OD_ENTRY_H2006, &OD_DIN_extension);
    OD_extension_init(OD_ENTRY_H2007, &OD_SEG_extension);
    OD_extension_init(OD_ENTRY_H2008, &OD_RGBMAP_extension);
    OD_extension_init(OD_ENTRY_H2009, &OD_RGB1_extension);
	OD_extension_init(OD_ENTRY_H200A, &OD_RGB2_extension);
	OD_extension_init(OD_ENTRY_H200B, &OD_RGB3_extension);
	OD_extension_init(OD_ENTRY_H200C, &OD_RGB4_extension);
	OD_extension_init(OD_ENTRY_H200D, &OD_RGB5_extension);
    OD_extension_init(OD_ENTRY_H200E, &OD_RGB6_extension);
    OD_extension_init(OD_ENTRY_H200F, &OD_RGB7_extension);
    OD_extension_init(OD_ENTRY_H2010, &OD_RGB8_extension);
    OD_extension_init(OD_ENTRY_H2011, &OD_RGB9_extension);
    OD_extension_init(OD_ENTRY_H2012, &OD_RGB10_extension);
    OD_extension_init(OD_ENTRY_H2013, &OD_RGB11_extension);
    OD_extension_init(OD_ENTRY_H2014, &OD_RGB12_extension);
    OD_extension_init(OD_ENTRY_H2015, &OD_RGB13_extension);
    OD_extension_init(OD_ENTRY_H2019, &OD_BAR_extension);
    OD_extension_init(OD_ENTRY_H201A, &OD_MENU_MAP_extension);
    OD_extension_init(OD_ENTRY_H201B, &OD_MENU_SETUP_extension);
    OD_extension_init(OD_ENTRY_H2025, &OD_BOARD_SETTINGS_extension);
    OD_extension_init(OD_ENTRY_H2032, &OD_ADC1_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2033, &OD_ADC2_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2034, &OD_ADC3_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2035, &OD_RPMCONFIG_extension);

}


static ODR_t OD_writeV1_14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    if ( stream->subIndex <= 15 )
    {
        uint8_t data = CO_getUint8(buf);
        *countWritten = sizeof(data);
        setReg8( V1 + (stream->subIndex-1 ) * sizeof(data) ,data);
    }
    else if (stream->subIndex <=17 )
    {
        uint16_t data = CO_getUint16(buf);
        *countWritten = sizeof(data);
        setReg16( V15 + (stream->subIndex -1) * sizeof(data) ,data);
    }
    else
    {
        uint32_t data = CO_getUint32(buf);
        *countWritten = sizeof(data);
        vSetErrorReg( data);
    }
    return (ODR_OK);
}



static ODR_t OD_readDashParam (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
     u32 temp;
     *countRead = sizeof(temp);
       switch (stream->subIndex)
       {
               case 1:
                   temp =  getOdometr();
                   break;
               case 2:
                   temp =  getReg32(HOUR_COUNTER_ADR);
                   break;
               case 3:
                   temp =  (u32)getReg8( ODOMETR_MAP);
                   break;
               default:
                   temp =  getReg32(VERSION_REG);
                   break;
       }
       CO_setUint32((void *)buf,temp );
       return (ODR_OK);
}

static ODR_t OD_writeDashParam(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
      *countWritten = sizeof(u32);
      if (stream->subIndex == 3)
      {
             uint8_t data =(uint8_t)CO_getUint32(buf);
             WriteRegAfterDelay( ODOMETR_MAP ,&data, sizeof(data));
             return (ODR_OK);
      }
      else
      if (stream->subIndex == 4)
      {
          uint32_t data =CO_getUint32(buf);
          WriteRegAfterDelay(VERSION_REG ,&data, sizeof(data));
          return (ODR_OK);
      }
      else
            return (ODR_READONLY);
}


static ODR_t OD_readRGBMAP (uint16_t addr, OD_stream_t *stream, void *buf, OD_size_t *countRead)
{
    *countRead = sizeof(u8);
     CO_setUint8( buf, getReg8( RGBMAP1  + (stream->subIndex -1)));
    return (ODR_OK);
}


static ODR_t OD_writeRGBMAP(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
     uint8_t data = CO_getUint8(buf);
     if ( data < chKEY )
     {
         *countWritten = sizeof(data);
         WriteRegAfterDelay( RGBMAP1  + (stream->subIndex -1),&data, sizeof(data) );
         return (ODR_OK);
     }
     return (ODR_VALUE_HIGH);
}

static ODR_t OD_readRGB (uint16_t addr, OD_stream_t *stream, void *buf, OD_size_t *countRead)
{
     *countRead = sizeof(u16);
     CO_setUint16( buf,getReg16(addr));
     return (ODR_OK);
}

static ODR_t OD_readRGB1 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB1_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB2 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB2_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB3 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB3_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB4 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB4_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB5 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB5_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB6 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB6_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB7 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB7_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB8 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB8_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB9 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB9_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB10 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB10_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB11 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB11_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB12 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB12_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB13 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB13_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}
static ODR_t OD_readRGB14 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (OD_readRGB(RGB14_VALUE_GREEN_HIGH,  stream, buf,  countRead));
}

static ODR_t WriteRGB(uint16_t addr, OD_stream_t *stream, const  void *buf, OD_size_t *countWritten)
{
      uint16_t data = CO_getUint16(buf);
      *countWritten = sizeof(data);
      WriteRegAfterDelay( addr  + (stream->subIndex -1)*sizeof(data) ,&data,sizeof(data));
      return (ODR_OK);
}

static ODR_t OD_writeRGB1(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB1_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB2(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB2_VALUE_GREEN_HIGH,  stream, buf, countWritten) );
}

static ODR_t OD_writeRGB3(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB3_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB4(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB4_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}
static ODR_t OD_writeRGB5(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB5_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB6(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB6_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB7(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB7_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB8(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB8_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB9(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB9_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}
static ODR_t OD_writeRGB10(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB10_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB11(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB11_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB12(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB12_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB13(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB13_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}

static ODR_t OD_writeRGB14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB14_VALUE_GREEN_HIGH,  stream, buf,  countWritten) );
}


static ODR_t OD_readSEG (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{

    *countRead = sizeof(u16);
    if (stream->subIndex == 1)
    {
        CO_setUint16(buf, getReg16( BIG_SEG ));
    }
    else
    {
        CO_setUint16(buf, getReg16( BIG_SEGVAL1 + (stream->subIndex-2)* sizeof(u16) ));
    }
    return (ODR_OK);

}

static ODR_t OD_writeSEG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{

     uint16_t data = CO_getUint16(buf);
     *countWritten= sizeof(data);
     if (stream->subIndex == 1)
     {
         setReg16(BIG_SEG, data);
     }
     else
     {
         WriteRegAfterDelay( BIG_SEGVAL1 + (stream->subIndex-2)* sizeof(data) ,&data, sizeof(data));
    }
     return (ODR_OK);
}


static ODR_t OD_readBar (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    *countRead = sizeof(u16);
    CO_setUint16( (void *) buf, getReg16( BAR_VALUE_RED_HIGH + (stream->subIndex-1)*sizeof(u16) ));
    return (ODR_OK);
}


static ODR_t OD_writeBAR(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      uint16_t data = CO_getUint16(buf);
      *countWritten = sizeof(u16);
      WriteRegAfterDelay( (BAR_VALUE_RED_HIGH + (stream->subIndex-1)*sizeof(u16)),&data,sizeof(u16));
      return (ODR_OK);
}




static ODR_t OD_readMenuMap (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
     *countRead = sizeof(u32);
     CO_setUint32(buf, getReg32( MENU1_MAP - 1 + stream->subIndex*sizeof(u32) ));
     return (ODR_OK);
}



static ODR_t  OD_writeMenuMap(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
         uint32_t data = CO_getUint32(buf);
         *countWritten = 4;
         WriteRegAfterDelay(  MENU1_MAP - 1 + stream->subIndex*4 ,&data,4);
         return (ODR_OK);
}

static ODR_t  OD_writeMenuSetup(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
        u8 data = CO_getUint8(buf);
        *countWritten = sizeof(data);
        switch (stream->subIndex)
        {
            case 1:
                if (SetCurrentMenu( data)) return (ODR_VALUE_HIGH);
                break;
            case 2:
                if (SetDefault(data)) return (ODR_VALUE_HIGH);
                break;
           default:
                WriteRegAfterDelay( MENU_HOME_BACK_TIME ,&data,sizeof(data));
                break;
        }
        return (ODR_OK);
}

static ODR_t OD_readMenuSetup (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
#ifdef  DEBUF_OD_READ_WRITE
    if (stream == NULL || buf == NULL || countRead == NULL) {
            return ODR_DEV_INCOMPAT;
        }
#endif
        *countRead = sizeof(u8);
        switch (stream->subIndex)
         {
              case 1:
                  CO_setUint8(buf,GetCurMenuHome());
                   break;
              case 2:
                  CO_setUint8(buf,  getReg8(MENU_DEF_POS));
                  break;
              default:
                  CO_setUint8(buf,getReg8( MENU_HOME_BACK_TIME ));
               break;
         }
        return (ODR_OK);
}


static ODR_t OD_readBoardSettings(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
            *countRead = sizeof(u8);
            if (stream->subIndex == 4)
                CO_setUint8(buf,  getReg8(DIN_ACTIVE_STATE));
            else
                CO_setUint8(buf,  getReg8(BITRATE_ADR - stream->subIndex -1 ) );
            return (ODR_OK);
}



static ODR_t OD_writeBoardSettings(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      ODR_t res = ODR_INVALID_VALUE;
      u8 temp = CO_getUint8(buf);
      *countWritten =0;
      switch( stream->subIndex )
        {
            case 2:
            case 3:
                if (temp <= MAX_BRIGTH)
                {
                    vSetBrigth(stream->subIndex  - 2 , sizeof(temp));
                    WriteRegAfterDelay(RGB_BRIGTH_ADR + (stream->subIndex -2 ), &temp, sizeof(temp));
                    res =  ODR_OK;
                    *countWritten =sizeof(temp);
                }
                break;
           case 1:
                 if (temp <= 7)
                 {
                    WriteRegAfterDelay(  BITRATE_ADR,&temp,sizeof(temp));
                    res =  ODR_OK;
                    *countWritten =sizeof(temp);
                }
                break;
           default:
               if (temp <= 1)
               {
                  WriteRegAfterDelay(  DIN_ACTIVE_STATE,&temp,sizeof(temp));
                  res =  ODR_OK;
                  *countWritten =sizeof(temp);
               }
               break;
   }
   return ( res );
}


static ODR_t OD_readAIN_RPM (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
#ifdef  DEBUF_OD_READ_WRITE
    if (stream == NULL || buf == NULL || countRead == NULL) {
            return ODR_DEV_INCOMPAT;
        }
#endif
        *countRead = sizeof(u16);
        CO_setUint16( (void *) buf,(u16)getODValue( chAIN1 -1 + stream->subIndex,1) );
        return (ODR_OK);
}


static ODR_t OD_readDIN (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
#ifdef  DEBUF_OD_READ_WRITE
    if (stream == NULL || buf == NULL || countRead == NULL) {
                return ODR_DEV_INCOMPAT;
     }
#endif
     *countRead = 1;
     CO_setUint8(buf, (u8)getODValue( chKEY  -1 + stream->subIndex,0));
     return (ODR_OK);
}

static ODR_t writeADC(OD_stream_t *stream, const void *buf,AIN_NAME_t name,OD_size_t *countWritten )
{
    if ( stream->subIndex == 1 )
    {
        if  (eAinCalDataConfig(name,CO_getUint8(buf))!=CAL_SUCCESS)
            return ( ODR_INVALID_VALUE );
        else {
            u8 temp = CO_getUint8(buf);
            *countWritten = sizeof(temp);
            WriteRegAfterDelay(AIN1_CAL_POINT_COUNT + name*3  ,&temp,sizeof(temp) );
        }
    }
    else if ( stream->subIndex == 2 )
    {
        u16 temp = CO_getUint16(buf);
        *countWritten = sizeof(temp);
        WriteRegAfterDelay(AIN1_OFFSET + name*3  ,&temp,  sizeof(temp) ) ;
    }
    else
    {
        u32 temp = CO_getUint32(buf);
        *countWritten = sizeof(temp);
        WriteRegAfterDelay(AIN1_CAL_POINT_BEGIN + (stream->subIndex -3)* sizeof(temp) + name * MAX_CAL_POINT *  sizeof(temp)  ,&temp,  sizeof(temp));
        POINT_t cal_point;
        cal_point.X = (float)(temp & 0xFFFF);
        cal_point.Y = ((float)(temp >>16))/10;
        if ( eSetAinCalPoint(name, &cal_point, (stream->subIndex -1) ) != CAL_SUCCESS )
            return ( ODR_INVALID_VALUE );
    }
    return (ODR_OK );
}

static ODR_t OD_writeADC1(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return (writeADC(stream,buf,AIN1,countWritten));
}

static ODR_t OD_writeADC2(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( writeADC(stream,buf,AIN2,countWritten));
}

static ODR_t OD_writeADC3(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t * countWritten)
{
    return ( writeADC(stream,buf,AIN3,countWritten));
}


static ODR_t readADC(OD_stream_t *stream, const void *buf,AIN_NAME_t name,OD_size_t *countRead )
{
    if ( stream->subIndex == 1 )
    {
       *countRead = sizeof(u8);
       CO_setUint8((void *)buf, getReg8( AIN1_CAL_POINT_COUNT + name*3 ) );
    }
    else if ( stream->subIndex == 2 )
    {
        *countRead =  sizeof(u16);
        CO_setUint16((void*)buf, getReg16( AIN1_OFFSET + name*3  ) );
    }
    else
    {
        *countRead =  sizeof(u32);
        CO_setUint32((void*)buf, getReg32( AIN1_CAL_POINT_BEGIN + (stream->subIndex -3)*sizeof(u32) + name * MAX_CAL_POINT * sizeof(u32) ) );
    }
    return (ODR_OK );
}


static ODR_t OD_readADC1 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (readADC(stream,buf,AIN1,countRead));
}

static ODR_t OD_readADC2 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (readADC(stream,buf,AIN2,countRead));
}

static ODR_t OD_readADC3 (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    return (readADC(stream,buf,AIN3,countRead));
}

/*
 * Функции для работы с объектом 2035
 */
static ODR_t OD_writeRPMConfig(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
   uint16_t data =(uint8_t)CO_getUint16(buf);
   *countWritten = sizeof(data);
   WriteRegAfterDelay( RPM1_COOF + (stream->subIndex -1)*sizeof(data)  ,&data, sizeof(data));
   return (ODR_OK);
}

static ODR_t OD_readRPMConfig (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
     *countRead = sizeof(u16);
     CO_setUint16( buf, getReg16( RPM1_COOF + ( stream->subIndex -1 ) * sizeof(u16) )  );
     return (ODR_OK);
}
