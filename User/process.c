/*
 * process.c
 *
 *  Created on: Nov 12, 2021
 *      Author: igor.dymov
 */

#include "process.h"


static ODR_t OD_writeADC1(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeADC2(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeADC3(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeBrigth(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeBAR(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
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
static ODR_t OD_writeRGBMAP(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeSEG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeV1_7(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeV8_14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeV15_17(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readDashParam (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeDashParam(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_writeRPMConfig(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readAIN_RPM (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t OD_writeERROR_REG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readDIN (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);
static ODR_t  OD_writeMenuMap(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t  OD_writeBitrate(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t  OD_writeMenuSetup(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten);
static ODR_t OD_readMenuSetup (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);

/* Variables used for triggering TPDO, see simulation in app_programRt(). */


const OD_extension_t OD_V1_7_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeV1_7
};
const  OD_extension_t OD_V8_14_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeV8_14
};
const  OD_extension_t OD_V15_17_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeV15_17
};

const OD_extension_t  OD_DASH_PARAM_extension = {
       .read =  OD_readDashParam,
        .write = OD_writeDashParam,
    };

const OD_extension_t OD_ADC1_CAL_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeADC1
};

const OD_extension_t OD_ADC2_CAL_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeADC2
};

const OD_extension_t OD_ADC3_CAL_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeADC3
};


const OD_extension_t OD_BRIGTH_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeBrigth
};

const OD_extension_t OD_BAR_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeBAR
};

const OD_extension_t OD_RGB1_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB1
};

const OD_extension_t OD_RGB2_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB2
};

const OD_extension_t OD_RGB3_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB3
};

const OD_extension_t OD_RGB4_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB4
};

const OD_extension_t OD_RGB5_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB5
};

const OD_extension_t OD_RGB6_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB6
};

const OD_extension_t OD_RGB7_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB7
};

const OD_extension_t OD_RGB8_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB8
};

const OD_extension_t OD_RGB9_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB9
};

const OD_extension_t OD_RGB10_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB10
};

const OD_extension_t OD_RGB11_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB11
};

const OD_extension_t OD_RGB12_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB12
};

const OD_extension_t OD_RGB13_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB13
};

const OD_extension_t OD_RGB14_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGB14
};

const OD_extension_t OD_RGBMAP_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeRGBMAP
};
const OD_extension_t OD_SEG_extension = {
    .object = NULL,
    .read =  OD_readOriginal,
    .write = OD_writeSEG
};

const OD_extension_t  OD_RPMCONFIG_extension = {
        .object = NULL,
        .read =  OD_readOriginal,
        .write = OD_writeRPMConfig
    };

const OD_extension_t  OD_AIN_RPM_extension = {
        .object = NULL,
        .read =  OD_readAIN_RPM,
        .write = OD_writeOriginal
    };
const OD_extension_t  OD_ERROR_REG_extension = {
        .object = NULL,
        .read =  NULL,
        .write = OD_writeERROR_REG
    };


const OD_extension_t  OD_DIN_extension= {
        .object = NULL,
        .read =  OD_readDIN,
        .write = NULL
    };

const OD_extension_t  OD_MENU_MAP_extension= {
        .object = NULL,
        .read =  OD_readOriginal,
        .write = OD_writeMenuMap
    };
const OD_extension_t  OD_BITRATE_extension= {
        .object = NULL,
        .read =  NULL,
        .write = OD_writeBitrate
    };

const OD_extension_t  OD_MENU_SETUP_extension= {
        .object = NULL,
        .read =  OD_readMenuSetup,
        .write = OD_writeMenuSetup
    };

void vProceesInit( void)
{
    OD_extension_init(OD_ENTRY_H2000, &OD_V1_7_extension);
    OD_extension_init(OD_ENTRY_H2001, &OD_V8_14_extension);
    OD_extension_init(OD_ENTRY_H2002, &OD_V15_17_extension);
    OD_extension_init(OD_ENTRY_H2003, &OD_ERROR_REG_extension);
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
    OD_extension_init(OD_ENTRY_H2024, &OD_BITRATE_extension);
    OD_extension_init(OD_ENTRY_H202F, &OD_BRIGTH_extension);
    OD_extension_init(OD_ENTRY_H2030, &OD_ADC1_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2031, &OD_ADC2_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2032, &OD_ADC3_CAL_extension) ;
    OD_extension_init(OD_ENTRY_H2033, &OD_RPMCONFIG_extension);

}


static ODR_t OD_writeV1_7(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{

#ifdef  DEBUF_OD_READ_WRITE
    if ((stream == NULL) || (buf == NULL) || (countWritten == NULL))
        return (ODR_DEV_INCOMPAT);
#endif
    uint16_t data = CO_getUint8(buf);
   WriteReg( V1 + (stream->subIndex -1),&data,1);
    return ( OD_writeOriginal(stream, buf, count, countWritten) );


}
static ODR_t OD_writeV8_14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
    if ((stream == NULL) || (buf == NULL) || (countWritten == NULL))
        return (ODR_DEV_INCOMPAT);
#endif
    uint16_t data = CO_getUint8(buf);
    WriteReg( V8 + (stream->subIndex -1),&data,1);
    return ( OD_writeOriginal(stream, buf, count, countWritten));


}
static ODR_t OD_writeV15_17(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
    if ((stream == NULL) || (buf == NULL) || (countWritten == NULL))
        return (ODR_DEV_INCOMPAT);
#endif
    uint16_t data = CO_getUint16(buf);
    WriteReg( V15 + (stream->subIndex -1),&data,2);
    return ( OD_writeOriginal(stream, buf, count, countWritten) );

}


static ODR_t OD_readDashParam (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
       *countRead = 4;
       switch (stream->subIndex)
       {
               case 1:
                   *((uint32_t *)buf) =  getOdometr();
                   break;
               case 2:
                   *((uint32_t *)buf) =  getReg32(HOUR_COUNTER_ADR);
                   break;
               case 3:
                   *((uint32_t *)buf) =  (u32)getReg8( ODOMETR_MAP);
                   break;
       }
       return (ODR_OK);
}

static ODR_t OD_writeDashParam(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif

      if (stream->subIndex == 3)
      {
             uint8_t data =(uint8_t)CO_getUint32(buf);
             WriteReg( ODOMETR_MAP ,&data, 1);
             *countWritten = 4;
             return (ODR_OK);
      }
      else
            return (ODR_READONLY);
}


static ODR_t OD_writeRPMConfig(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      uint8_t data =(uint8_t)CO_getUint32(buf);
      WriteReg( RPM1_COOF + (stream->subIndex -1)  ,&data, 1);
      return ( OD_writeOriginal(stream, buf, count, countWritten) );
}


static ODR_t WriteRGB(uint16_t addr, OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      uint8_t data = CO_getUint8(buf);
      WriteReg( addr  + (stream->subIndex -1),&data,1);
      return (OD_writeOriginal(stream, buf, count, countWritten));
}


static ODR_t OD_writeRGBMAP(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
     uint8_t data = CO_getUint8(buf);
     if ( data < chKEY )
     {
         WriteReg( RGBMAP1  + (stream->subIndex -1),&data,1);
         return ( OD_writeOriginal(stream, buf, count, countWritten));
     }
     return (ODR_VALUE_HIGH);
}


static ODR_t OD_writeRGB1(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB1_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB2(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB2_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB3(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB3_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB4(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB4_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}
static ODR_t OD_writeRGB5(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB5_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB6(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB6_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB7(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB7_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB8(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB8_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB9(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB9_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}
static ODR_t OD_writeRGB10(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB10_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB11(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB11_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB12(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB12_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB13(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB13_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeRGB14(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
    return ( WriteRGB( RGB14_VALUE_GREEN_HIGH,  stream, buf, count, countWritten) );
}

static ODR_t OD_writeSEG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif

     uint16_t data = CO_getUint8(buf);
     uint16_t addr = ( stream->subIndex == 1)? BIG_SEG : (BIG_SEGVAL1 -2 + stream->subIndex);
     WriteReg( addr ,&data,2);
     return ( OD_writeOriginal(stream, buf, count, countWritten) );
}


static ODR_t OD_writeBAR(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      uint16_t data = CO_getUint16(buf);
      WriteReg( (BAR_VALUE_RED_HIGH - 1 + stream->subIndex),&data,2);
      return (OD_writeOriginal(stream, buf, count, countWritten));
}


static ODR_t writeADC(OD_stream_t *stream, const void *buf,AIN_NAME_t name )
{
    if ( stream->subIndex == ADC_CAL_POINT_COUNT_SUBINDEX )
    {
        if  (eAinCalDataConfig(name,CO_getUint16(buf))!=CAL_SUCCESS)
            return ( ODR_INVALID_VALUE );
    }
    else {
        u32 temp = CO_getUint32(buf);
        WriteReg(AIN1_CAL_POINT_BEGIN + stream->subIndex -2  ,&temp,4);
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
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
    ODR_t  res = writeADC(stream,buf,AIN1);
    if ( res == ODR_OK)
    {
        res = OD_writeOriginal(stream, buf, count, countWritten);
    }
	return ( res );
}

static ODR_t OD_writeADC2(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
    ODR_t  res = writeADC(stream,buf,AIN2);
    if ( res == ODR_OK)
    {
        res = OD_writeOriginal(stream, buf, count, countWritten);
    }
    return ( res );
}

static ODR_t OD_writeADC3(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
    ODR_t  res = writeADC(stream,buf,AIN3);
    if ( res == ODR_OK)
    {
        res = OD_writeOriginal(stream, buf, count, countWritten);
    }
    return ( res );
}

static ODR_t OD_writeERROR_REG(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
    if (stream == NULL || buf == NULL || countRead == NULL) {
            return ODR_DEV_INCOMPAT;
        }
#endif
    vSetErrorReg( CO_getUint32(buf));
    return ( OD_writeOriginal(stream, buf, count, countWritten));
}


static ODR_t  OD_writeMenuMap(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
         uint32_t data = CO_getUint32(buf);
         WriteReg(  MENU1_MAP - 1 + stream->subIndex ,&data,4);
         return ( OD_writeOriginal(stream, buf, count, countWritten) );
}

static ODR_t  OD_writeMenuSetup(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
        u8 data = CO_getUint8(buf);
        switch (stream->subIndex)
        {
            case 1:
                if (SetCurrentMenu( data)) return (ODR_VALUE_HIGH);
                break;
            case 2:
                if (SetDefault(data)) return (ODR_VALUE_HIGH);
                break;
            case 3:
                WriteReg( MENU_HOME_BACK_TIME ,&data,1);
                break;
        }
        return ( OD_writeOriginal(stream, buf, count, countWritten) );
}

static ODR_t OD_readMenuSetup (OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
#ifdef  DEBUF_OD_READ_WRITE
    if (stream == NULL || buf == NULL || countRead == NULL) {
            return ODR_DEV_INCOMPAT;
        }
#endif
        *countRead = 1;
        switch (stream->subIndex)
         {
              case 1:
                  *((u8 *)buf) = GetCurMenuHome();
                   break;
              case 2:
                  *((u8 *)buf) =  getReg8(MENU_DEF_POS);
                  break;
              case 3:
                *((u8 *)buf) =  getReg8( MENU_HOME_BACK_TIME );
               break;
         }
        return (ODR_OK);
}


static ODR_t  OD_writeBitrate(OD_stream_t *stream,const  void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
      u8 data = CO_getUint8(buf);
     WriteReg(  BITRATE_ADR  ,&data,1);
     return ( OD_writeOriginal(stream, buf, count, countWritten) );

}

static ODR_t OD_writeBrigth(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
#ifdef  DEBUF_OD_READ_WRITE
       if (stream == NULL || buf == NULL || countRead == NULL) {
           return ODR_DEV_INCOMPAT;
       }
#endif
    ODR_t res = ODR_DEV_INCOMPAT;
    if ((stream != NULL) && (buf != NULL) && (countWritten != NULL))
    {
        u8 temp = CO_getUint8(buf);
        if (temp > MAX_BRIGTH)
        {
            res =  ODR_INVALID_VALUE;
        }
        else
        {
            switch (stream->subIndex )
            {
                 case 1:
                       vSetBrigth(RGB_CHANNEL, temp);
                       WriteReg( RGB_BRIGTH_ADR, &temp, sizeof(temp));
                       break;
                 case 2:
                       vSetBrigth(WHITE_CHANNEL, temp);
                       WriteReg( WHITE_BRIGTH_ADR, &temp, sizeof(temp));
                       break;
                 default:
                     return ( ODR_SUB_NOT_EXIST );
                     break;
            }
            res = OD_writeOriginal(stream, buf, count, countWritten);
        }
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
        *countRead = 2;
        u16 temp = (u16)getODValue( chAIN1 -1 + stream->subIndex,0);
        u8 *ptemp = (u8 * )buf;
        ptemp[0] =  (u8)( temp & 0xFF);
        ptemp[1] =  (u8)((temp >>8) & 0xFF);

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
     u8 *ptemp = (u8 * )buf;
     ptemp[0] = (u8)getODValue( chKEY  -1 + stream->subIndex,0);
     return (ODR_OK);
}



