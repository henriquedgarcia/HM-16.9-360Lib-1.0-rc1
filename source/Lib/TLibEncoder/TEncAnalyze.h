/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2016, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     TEncAnalyze.h
    \brief    encoder analyzer class (header)
*/

#ifndef __TENCANALYZE__
#define __TENCANALYZE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include "TLibCommon/CommonDef.h"
#include "TLibCommon/TComChromaFormat.h"
#include "math.h"

//! \ingroup TLibEncoder
//! \{

// ====================================================================================================================
// Class definition
// ====================================================================================================================

/// encoder analyzer class
class TEncAnalyze
{
private:
  Double    m_dPSNRSum[MAX_NUM_COMPONENT];
  Double    m_dAddBits;
  UInt      m_uiNumPic;
  Double    m_dFrmRate; //--CFG_KDY
  Double    m_MSEyuvframe[MAX_NUM_COMPONENT]; // sum of MSEs

#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
  Bool      m_bSPSNREnabled;
  Double    m_dSPSNRSum[MAX_NUM_COMPONENT];
#endif
#if SVIDEO_WSPSNR
  Bool      m_bWSPSNREnabled;
  Double    m_dWSPSNRSum[MAX_NUM_COMPONENT];
#if SVIDEO_WSPSNR_E2E
  Bool      m_bE2EWSPSNREnabled;
  Double    m_dE2EWSPSNRSum[MAX_NUM_COMPONENT];
#endif
#endif
#if SVIDEO_SPSNR_I
  Bool      m_bSPSNRIEnabled;
  Double    m_dSPSNRISum[MAX_NUM_COMPONENT];
#endif
#if SVIDEO_CPPPSNR
  Bool      m_bCPPPSNREnabled;
  Double    m_dCPPPSNRSum[MAX_NUM_COMPONENT];
#endif
#endif
public:
  virtual ~TEncAnalyze()  {}
  TEncAnalyze() { clear(); }

  Void  addResult( Double psnr[MAX_NUM_COMPONENT], Double bits, const Double MSEyuvframe[MAX_NUM_COMPONENT])
  {
    m_dAddBits  += bits;
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dPSNRSum[i] += psnr[i];
      m_MSEyuvframe[i] += MSEyuvframe[i];
    }

    m_uiNumPic++;
  }
#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
  Void  setSPSNREnabled(Bool b)   { m_bSPSNREnabled = b; }
  Void  addSPSNR( Double spsnr[MAX_NUM_COMPONENT])
  {
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dSPSNRSum[i] += spsnr[i];
    }
  }
#endif
#if SVIDEO_WSPSNR
  Void  setWSPSNREnabled(Bool b)   { m_bWSPSNREnabled = b; }
  Void  addWSPSNR( Double wspsnr[MAX_NUM_COMPONENT])
  {
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dWSPSNRSum[i] += wspsnr[i];
    }
  }
#if SVIDEO_WSPSNR_E2E
  Void  setE2EWSPSNREnabled(Bool b)   { m_bE2EWSPSNREnabled = b; }
  Void  addE2EWSPSNR( Double wspsnr[MAX_NUM_COMPONENT])
  {
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dE2EWSPSNRSum[i] += wspsnr[i];
    }
  }
#endif
#endif
#if SVIDEO_SPSNR_I
  Void  setSPSNRIEnabled(Bool b)   { m_bSPSNRIEnabled = b; }
  Void  addSPSNRI( Double spsnri[MAX_NUM_COMPONENT])
  {
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dSPSNRISum[i] += spsnri[i];
    }
  }
#endif
#if SVIDEO_CPPPSNR
  Void  setCPPPSNREnabled(Bool b)   { m_bCPPPSNREnabled = b; }
  Void  addCPPPSNR( Double cpppsnr[MAX_NUM_COMPONENT])
  {
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dCPPPSNRSum[i] += cpppsnr[i];
    }
  }
#endif

#if SVIDEO_SPSNR_NN
  Double  getSpsnr(ComponentID compID) const { return m_dSPSNRSum[compID]; }
#endif
#if SVIDEO_WSPSNR
  Double  getWSpsnr(ComponentID compID) const { return m_dWSPSNRSum[compID]; }
#if SVIDEO_WSPSNR_E2E
  Double  getE2EWSpsnr(ComponentID compID) const { return m_dE2EWSPSNRSum[compID]; }
#endif
#endif
#if SVIDEO_SPSNR_I
  Double  getSpsnrI(ComponentID compID) const { return m_dSPSNRISum[compID]; }
#endif
#if SVIDEO_CPPPSNR
  Double  getCPPpsnr(ComponentID compID) const { return m_dCPPPSNRSum[compID]; }
#endif
#endif
  Double  getPsnr(ComponentID compID) const { return  m_dPSNRSum[compID];  }
  Double  getBits()                   const { return  m_dAddBits;   }
  Void    setBits(Double numBits)     { m_dAddBits=numBits; }
  UInt    getNumPic()                 const { return  m_uiNumPic;   }

  Void    setFrmRate  (Double dFrameRate) { m_dFrmRate = dFrameRate; } //--CFG_KDY
  Void    clear()
  {
#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
    m_bSPSNREnabled = false;
#endif
#if SVIDEO_WSPSNR
    m_bWSPSNREnabled = false;
#if SVIDEO_WSPSNR_E2E
    m_bE2EWSPSNREnabled = false;
#endif
#endif
#if SVIDEO_SPSNR_I
    m_bSPSNRIEnabled = false;
#endif
#if SVIDEO_CPPPSNR
    m_bCPPPSNREnabled = false;
#endif
#endif
    m_dAddBits = 0;
    for(UInt i=0; i<MAX_NUM_COMPONENT; i++)
    {
      m_dPSNRSum[i] = 0;
#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
      m_dSPSNRSum[i] = 0;
#endif
#if SVIDEO_WSPSNR
      m_dWSPSNRSum[i] = 0;
#if SVIDEO_WSPSNR_E2E
      m_dE2EWSPSNRSum[i] = 0;
#endif
#endif
#if SVIDEO_SPSNR_I
      m_dSPSNRISum[i] = 0;
#endif
#if SVIDEO_CPPPSNR
      m_dCPPPSNRSum[i] = 0;
#endif
#endif
      m_MSEyuvframe[i] = 0;
    }
    m_uiNumPic = 0;
  }


  Void calculateCombinedValues(const ChromaFormat chFmt, Double &PSNRyuv, Double &MSEyuv, const BitDepths &bitDepths)
  {
    MSEyuv    = 0;
    Int scale = 0;

    Int maximumBitDepth = bitDepths.recon[CHANNEL_TYPE_LUMA];
    for (UInt channelTypeIndex = 1; channelTypeIndex < MAX_NUM_CHANNEL_TYPE; channelTypeIndex++)
    {
      if (bitDepths.recon[channelTypeIndex] > maximumBitDepth)
      {
        maximumBitDepth = bitDepths.recon[channelTypeIndex];
      }
    }

    const UInt maxval                = 255 << (maximumBitDepth - 8);
    const UInt numberValidComponents = getNumberValidComponents(chFmt);

    for (UInt comp=0; comp<numberValidComponents; comp++)
    {
      const ComponentID compID        = ComponentID(comp);
      const UInt        csx           = getComponentScaleX(compID, chFmt);
      const UInt        csy           = getComponentScaleY(compID, chFmt);
      const Int         scaleChan     = (4>>(csx+csy));
      const UInt        bitDepthShift = 2 * (maximumBitDepth - bitDepths.recon[toChannelType(compID)]); //*2 because this is a squared number

      const Double      channelMSE    = (m_MSEyuvframe[compID] * Double(1 << bitDepthShift)) / Double(getNumPic());

      scale  += scaleChan;
      MSEyuv += scaleChan * channelMSE;
    }

    MSEyuv /= Double(scale);  // i.e. divide by 6 for 4:2:0, 8 for 4:2:2 etc.
    PSNRyuv = (MSEyuv==0 ? 999.99 : 10*log10((maxval*maxval)/MSEyuv));
  }


  Void    printOut ( TChar cDelim, const ChromaFormat chFmt, const Bool printMSEBasedSNR, const Bool printSequenceMSE, const BitDepths &bitDepths )
  {
    Double dFps     =   m_dFrmRate; //--CFG_KDY
    Double dScale   = dFps / 1000 / (Double)m_uiNumPic;

    Double MSEBasedSNR[MAX_NUM_COMPONENT];
    if (printMSEBasedSNR)
    {
      for (UInt componentIndex = 0; componentIndex < MAX_NUM_COMPONENT; componentIndex++)
      {
        const ComponentID compID = ComponentID(componentIndex);

        if (getNumPic() == 0)
        {
          MSEBasedSNR[compID] = 0 * dScale; // this is the same calculation that will be evaluated for any other statistic when there are no frames (it should result in NaN). We use it here so all the output is consistent.
        }
        else
        {
          //NOTE: this is not the true maximum value for any bitDepth other than 8. It comes from the original HM PSNR calculation
          const UInt maxval = 255 << (bitDepths.recon[toChannelType(compID)] - 8);
          const Double MSE = m_MSEyuvframe[compID];

          MSEBasedSNR[compID] = (MSE == 0) ? 999.99 : (10 * log10((maxval * maxval) / (MSE / (Double)getNumPic())));
        }
      }
    }

    switch (chFmt)
    {
      case CHROMA_400:
        if (printMSEBasedSNR)
        {
          printf( "         \tTotal Frames |   "   "Bitrate     "  "Y-PSNR" );

          if (printSequenceMSE)
          {
            printf( "    Y-MSE\n" );
          }
          else
          {
            printf("\n");
          }

          //printf( "\t------------ "  " ----------"   " -------- "  " -------- "  " --------\n" );
          printf( "Average: \t %8d    %c "          "%12.4lf  "    "%8.4lf",
                 getNumPic(), cDelim,
                 getBits() * dScale,
                 getPsnr(COMPONENT_Y) / (Double)getNumPic() );

          if (printSequenceMSE)
          {
            printf( "  %8.4lf\n", m_MSEyuvframe[COMPONENT_Y ] / (Double)getNumPic() );
          }
          else
          {
            printf("\n");
          }

          printf( "From MSE:\t %8d    %c "          "%12.4lf  "    "%8.4lf\n",
                 getNumPic(), cDelim,
                 getBits() * dScale,
                 MSEBasedSNR[COMPONENT_Y] );
        }
        else
        {
          printf( "\tTotal Frames |   "   "Bitrate     "  "Y-PSNR" );

          if (printSequenceMSE)
          {
            printf( "    Y-MSE\n" );
          }
          else
          {
            printf("\n");
          }

          //printf( "\t------------ "  " ----------"   " -------- "  " -------- "  " --------\n" );
          printf( "\t %8d    %c "          "%12.4lf  "    "%8.4lf",
                 getNumPic(), cDelim,
                 getBits() * dScale,
                 getPsnr(COMPONENT_Y) / (Double)getNumPic() );

          if (printSequenceMSE)
          {
            printf( "  %8.4lf\n", m_MSEyuvframe[COMPONENT_Y ] / (Double)getNumPic() );
          }
          else
          {
            printf("\n");
          }
        }
        break;
      case CHROMA_420:
      case CHROMA_422:
      case CHROMA_444:
        {
          Double PSNRyuv = MAX_DOUBLE;
          Double MSEyuv  = MAX_DOUBLE;
          
          calculateCombinedValues(chFmt, PSNRyuv, MSEyuv, bitDepths);

          if (printMSEBasedSNR)
          {
            printf( "         \tTotal Frames |   "   "Bitrate     "  "Y-PSNR    "  "U-PSNR    "  "V-PSNR    "  "YUV-PSNR " );

            if (printSequenceMSE)
            {
              printf( " Y-MSE     "  "U-MSE     "  "V-MSE    "  "YUV-MSE \n" );
            }
            else
            {
              printf("\n");
            }

            //printf( "\t------------ "  " ----------"   " -------- "  " -------- "  " --------\n" );
            printf( "Average: \t %8d    %c "          "%12.4lf  "    "%8.4lf  "   "%8.4lf  "    "%8.4lf  "   "%8.4lf",
                   getNumPic(), cDelim,
                   getBits() * dScale,
                   getPsnr(COMPONENT_Y) / (Double)getNumPic(),
                   getPsnr(COMPONENT_Cb) / (Double)getNumPic(),
                   getPsnr(COMPONENT_Cr) / (Double)getNumPic(),
                   PSNRyuv );

            if (printSequenceMSE)
            {
              printf( "  %8.4lf  "   "%8.4lf  "    "%8.4lf  "   "%8.4lf\n",
                     m_MSEyuvframe[COMPONENT_Y ] / (Double)getNumPic(),
                     m_MSEyuvframe[COMPONENT_Cb] / (Double)getNumPic(),
                     m_MSEyuvframe[COMPONENT_Cr] / (Double)getNumPic(),
                     MSEyuv );
            }
            else
            {
              printf("\n");
            }

            printf( "From MSE:\t %8d    %c "          "%12.4lf  "    "%8.4lf  "   "%8.4lf  "    "%8.4lf  "   "%8.4lf\n",
                   getNumPic(), cDelim,
                   getBits() * dScale,
                   MSEBasedSNR[COMPONENT_Y],
                   MSEBasedSNR[COMPONENT_Cb],
                   MSEBasedSNR[COMPONENT_Cr],
                   PSNRyuv );
          }
          else
          {
            printf( "\tTotal Frames |   "   "Bitrate     "  "Y-PSNR    "  "U-PSNR    "  "V-PSNR    "  "YUV-PSNR " );
#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
            if(m_bSPSNREnabled)
            {
              printf( " Y-SPSNR_NN "  "U-SPSNR_NN "  "V-SPSNR_NN " );
            }
#endif
#if SVIDEO_WSPSNR
            if(m_bWSPSNREnabled)
            {
              printf( " Y-WSPSNR  "  "U-WSPSNR  "  "V-WSPSNR   " );
            }
#endif
#if SVIDEO_SPSNR_I
            if(m_bSPSNRIEnabled)
            {
              printf( " Y-SPSNR_I  "  "U-SPSNR_I  "  "V-SPSNR_I  " );
            }
#endif
#if SVIDEO_CPPPSNR
            if(m_bCPPPSNREnabled)
            {
              printf( " Y-CPPPSNR  "  "U-CPPPSNR  "  "V-CPPPSNR  " );
            }
#endif
#if SVIDEO_WSPSNR_E2E
            if(m_bE2EWSPSNREnabled)
            {
              printf( " Y-E2EWSPSNR "  "U-E2EWSPSNR "  "V-E2EWSPSNR " );
            }
#endif
#endif
            if (printSequenceMSE)
            {
              printf( " Y-MSE     "  "U-MSE     "  "V-MSE    "  "YUV-MSE \n" );
            }
            else
            {
              printf("\n");
            }

            //printf( "\t------------ "  " ----------"   " -------- "  " -------- "  " --------\n" );
            printf( "\t %8d    %c "          "%12.4lf  "    "%8.4lf  "   "%8.4lf  "    "%8.4lf  "   "%8.4lf",
                   getNumPic(), cDelim,
                   getBits() * dScale,
                   getPsnr(COMPONENT_Y) / (Double)getNumPic(),
                   getPsnr(COMPONENT_Cb) / (Double)getNumPic(),
                   getPsnr(COMPONENT_Cr) / (Double)getNumPic(),
                   PSNRyuv );
#if SVIDEO_EXT
#if SVIDEO_SPSNR_NN
            if(m_bSPSNREnabled)
            {
              printf( " %8.4lf   "   "%8.4lf   "    "%8.4lf  ",
                      getSpsnr(COMPONENT_Y ) / (Double)getNumPic(),
                      getSpsnr(COMPONENT_Cb ) / (Double)getNumPic(),
                      getSpsnr(COMPONENT_Cr )  / (Double)getNumPic()
                    );
            } 
#endif
#if SVIDEO_WSPSNR
            if(m_bWSPSNREnabled)
            {
              printf( "  %8.4lf  "   "%8.4lf  "    "%8.4lf  ",
                      getWSpsnr(COMPONENT_Y ) / (Double)getNumPic(),
                      getWSpsnr(COMPONENT_Cb ) / (Double)getNumPic(),
                      getWSpsnr(COMPONENT_Cr )  / (Double)getNumPic()
                    );
            } 
#endif
#if SVIDEO_SPSNR_I
            if(m_bSPSNRIEnabled)
            {
              printf( "  %8.4lf   "   "%8.4lf   "    "%8.4lf  ",
                      getSpsnrI(COMPONENT_Y )  / (Double)getNumPic(),
                      getSpsnrI(COMPONENT_Cb ) / (Double)getNumPic(),
                      getSpsnrI(COMPONENT_Cr ) / (Double)getNumPic()
                    );
            } 
#endif
#if SVIDEO_CPPPSNR
            if(m_bCPPPSNREnabled)
            {
              printf( "  %8.4lf   "   "%8.4lf   "    "%8.4lf  ",
                      getCPPpsnr(COMPONENT_Y )  / (Double)getNumPic(),
                      getCPPpsnr(COMPONENT_Cb ) / (Double)getNumPic(),
                      getCPPpsnr(COMPONENT_Cr ) / (Double)getNumPic()
                    );
            } 
#endif
#if SVIDEO_WSPSNR_E2E
            if(m_bE2EWSPSNREnabled)
            {
              printf( "  %8.4lf "   "   %8.4lf "    "   %8.4lf ",
                      getE2EWSpsnr(COMPONENT_Y ) / (Double)getNumPic(),
                      getE2EWSpsnr(COMPONENT_Cb ) / (Double)getNumPic(),
                      getE2EWSpsnr(COMPONENT_Cr )  / (Double)getNumPic()
                    );
            } 
#endif
#endif
            if (printSequenceMSE)
            {
              printf( "  %8.4lf  "   "%8.4lf  "    "%8.4lf  "   "%8.4lf\n",
                     m_MSEyuvframe[COMPONENT_Y ] / (Double)getNumPic(),
                     m_MSEyuvframe[COMPONENT_Cb] / (Double)getNumPic(),
                     m_MSEyuvframe[COMPONENT_Cr] / (Double)getNumPic(),
                     MSEyuv );
            }
            else
            {
              printf("\n");
            }
          }
        }
        break;
      default:
        fprintf(stderr, "Unknown format during print out\n");
        exit(1);
        break;
    }
  }


  Void    printSummary(const ChromaFormat chFmt, const Bool printSequenceMSE, const BitDepths &bitDepths, const std::string &sFilename)
  {
    FILE* pFile = fopen (sFilename.c_str(), "at");

    Double dFps     =   m_dFrmRate; //--CFG_KDY
    Double dScale   = dFps / 1000 / (Double)m_uiNumPic;
    switch (chFmt)
    {
      case CHROMA_400:
        fprintf(pFile, "%f\t %f\n",
            getBits() * dScale,
            getPsnr(COMPONENT_Y) / (Double)getNumPic() );
        break;
      case CHROMA_420:
      case CHROMA_422:
      case CHROMA_444:
        {
          Double PSNRyuv = MAX_DOUBLE;
          Double MSEyuv  = MAX_DOUBLE;
          
          calculateCombinedValues(chFmt, PSNRyuv, MSEyuv, bitDepths);

          fprintf(pFile, "%f\t %f\t %f\t %f\t %f",
              getBits() * dScale,
              getPsnr(COMPONENT_Y) / (Double)getNumPic(),
              getPsnr(COMPONENT_Cb) / (Double)getNumPic(),
              getPsnr(COMPONENT_Cr) / (Double)getNumPic(),
              PSNRyuv );

          if (printSequenceMSE)
          {
            fprintf(pFile, "\t %f\t %f\t %f\t %f\n",
                m_MSEyuvframe[COMPONENT_Y ] / (Double)getNumPic(),
                m_MSEyuvframe[COMPONENT_Cb] / (Double)getNumPic(),
                m_MSEyuvframe[COMPONENT_Cr] / (Double)getNumPic(),
                MSEyuv );
          }
          else
          {
            fprintf(pFile, "\n");
          }

          break;
        }

      default:
          fprintf(stderr, "Unknown format during print out\n");
          exit(1);
          break;
    }

    fclose(pFile);
  }
};

extern TEncAnalyze             m_gcAnalyzeAll;
extern TEncAnalyze             m_gcAnalyzeI;
extern TEncAnalyze             m_gcAnalyzeP;
extern TEncAnalyze             m_gcAnalyzeB;

extern TEncAnalyze             m_gcAnalyzeAll_in;

//! \}

#endif // !defined(AFX_TENCANALYZE_H__C79BCAA2_6AC8_4175_A0FE_CF02F5829233__INCLUDED_)
