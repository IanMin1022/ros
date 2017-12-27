/**
 * @file arstream2_stream_stats.c
 * @brief Parrot Streaming Library - Stream Stats
 * @date 10/04/2016
 * @author aurelien.barre@parrot.com
 */

#include <stdio.h>
#include <stdlib.h>

#include <libARSAL/ARSAL_Print.h>

#include "arstream2_stream_stats_internal.h"


#define ARSTREAM2_STREAM_STATS_TAG "ARSTREAM2_StreamStats"

#define ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_PATH "videostats"
#define ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_FILENAME "videostats"
#define ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_FILEEXT "dat"

#define ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_INTERVAL (1000000)

#define ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_PATH "rtpstats"
#define ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_FILENAME "rtpstats"
#define ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_FILEEXT "dat"

#define ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_INTERVAL (1000000)


void ARSTREAM2_StreamStats_VideoStatsFileOpen(ARSTREAM2_StreamStats_VideoStatsContext_t *context, const char *debugPath, const char *friendlyName,
                                              const char *dateAndTime, uint32_t mbStatusZoneCount, uint32_t mbStatusClassCount)
{
    char szOutputFileName[500];
    szOutputFileName[0] = '\0';

    if ((!context) || (!dateAndTime))
    {
        return;
    }

    if ((debugPath) && (strlen(debugPath)))
    {
        snprintf(szOutputFileName, 500, "%s/%s", debugPath,
                 ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_PATH);
        if ((access(szOutputFileName, F_OK) == 0) && (access(szOutputFileName, W_OK) == 0))
        {
            // directory exists and we have write permission
            snprintf(szOutputFileName, 500, "%s/%s/%s_%s.%s", debugPath,
                     ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_PATH,
                     ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_FILENAME,
                     dateAndTime,
                     ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_FILEEXT);
        }
        else
        {
            szOutputFileName[0] = '\0';
        }
    }

    if (strlen(szOutputFileName))
    {
        context->outputFile = fopen(szOutputFileName, "w");
        if (!context->outputFile)
        {
            ARSAL_PRINT(ARSAL_PRINT_WARNING, ARSTREAM2_STREAM_STATS_TAG, "Unable to open video stats output file '%s'", szOutputFileName);
        }
        else
        {
            ARSAL_PRINT(ARSAL_PRINT_INFO, ARSTREAM2_STREAM_STATS_TAG, "Opened video stats output file '%s'", szOutputFileName);
        }
    }

    if (context->outputFile)
    {
        char szTitle[200];
        int titleLen = 0;
        szTitle[0] = '\0';
        if ((friendlyName) && (strlen(friendlyName)))
        {
            titleLen += snprintf(szTitle + titleLen, 200 - titleLen, "%s ", friendlyName);
        }
        titleLen += snprintf(szTitle + titleLen, 200 - titleLen, "%s", dateAndTime);
        ARSAL_PRINT(ARSAL_PRINT_INFO, ARSTREAM2_STREAM_STATS_TAG, "Video stats output file title: '%s'", szTitle);
        fprintf(context->outputFile, "# %s\n", szTitle);
        fprintf(context->outputFile, "timestamp rssi totalFrameCount outputFrameCount erroredOutputFrameCount discardedFrameCount missedFrameCount");
        fprintf(context->outputFile, " timestampDeltaIntegral timestampDeltaIntegralSq timingErrorIntegral timingErrorIntegralSq estimatedLatencyIntegral estimatedLatencyIntegralSq erroredSecondCount");
        uint32_t i, j;
        for (i = 0; i < mbStatusZoneCount; i++)
        {
            fprintf(context->outputFile, " erroredSecondCountByZone[%d]", i);
        }
        for (j = 0; j < mbStatusClassCount; j++)
        {
            for (i = 0; i < mbStatusZoneCount; i++)
            {
                fprintf(context->outputFile, " macroblockStatus[%d][%d]", j, i);
            }
        }
        fprintf(context->outputFile, "\n");
        fflush(context->outputFile);
        context->fileOutputTimestamp = 0;
    }
}


void ARSTREAM2_StreamStats_VideoStatsFileClose(ARSTREAM2_StreamStats_VideoStatsContext_t *context)
{
    if (context->outputFile)
    {
        fclose(context->outputFile);
        context->outputFile = NULL;
    }
}


void ARSTREAM2_StreamStats_VideoStatsFileWrite(ARSTREAM2_StreamStats_VideoStatsContext_t *context, const ARSTREAM2_H264_VideoStats_t *videoStats)
{
    if ((!context) || (!videoStats))
    {
        return;
    }

    if (!context->outputFile)
    {
        return;
    }

    if (context->fileOutputTimestamp == 0)
    {
        /* init */
        context->fileOutputTimestamp = videoStats->timestamp;
    }
    if (videoStats->timestamp >= context->fileOutputTimestamp + ARSTREAM2_STREAM_STATS_VIDEO_STATS_OUTPUT_INTERVAL)
    {
        if (context->outputFile)
        {
            fprintf(context->outputFile, "%llu %i %lu %lu %lu %lu %lu", (long long unsigned int)videoStats->timestamp, videoStats->rssi,
                    (long unsigned int)videoStats->totalFrameCount, (long unsigned int)videoStats->outputFrameCount,
                    (long unsigned int)videoStats->erroredOutputFrameCount, (long unsigned int)videoStats->discardedFrameCount,
                    (long unsigned int)videoStats->missedFrameCount);
            fprintf(context->outputFile, " %llu %llu %llu %llu %llu %llu %lu",
                    (long long unsigned int)videoStats->timestampDeltaIntegral, (long long unsigned int)videoStats->timestampDeltaIntegralSq,
                    (long long unsigned int)videoStats->timingErrorIntegral,(long long unsigned int)videoStats->timingErrorIntegralSq,
                    (long long unsigned int)videoStats->estimatedLatencyIntegral, (long long unsigned int)videoStats->estimatedLatencyIntegralSq,
                    (long unsigned int)videoStats->erroredSecondCount);
            uint32_t i, j;
            for (i = 0; i < videoStats->mbStatusZoneCount; i++)
            {
                fprintf(context->outputFile, " %lu", (long unsigned int)videoStats->erroredSecondCountByZone[i]);
            }
            for (j = 0; j < videoStats->mbStatusClassCount; j++)
            {
                for (i = 0; i < videoStats->mbStatusZoneCount; i++)
                {
                    fprintf(context->outputFile, " %lu", (long unsigned int)videoStats->macroblockStatus[j][i]);
                }
            }
            fprintf(context->outputFile, "\n");
            fflush(context->outputFile);
        }
        context->fileOutputTimestamp = videoStats->timestamp;
    }
}


void ARSTREAM2_StreamStats_RtpStatsFileOpen(ARSTREAM2_StreamStats_RtpStatsContext_t *context, const char *debugPath,
                                            const char *friendlyName, const char *dateAndTime)
{
    char szOutputFileName[500];
    szOutputFileName[0] = '\0';

    if ((!context) || (!dateAndTime))
    {
        return;
    }

    if ((debugPath) && (strlen(debugPath)))
    {
        snprintf(szOutputFileName, 500, "%s/%s", debugPath,
                 ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_PATH);
        if ((access(szOutputFileName, F_OK) == 0) && (access(szOutputFileName, W_OK) == 0))
        {
            // directory exists and we have write permission
            snprintf(szOutputFileName, 500, "%s/%s/%s_%s.%s", debugPath,
                     ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_PATH,
                     ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_FILENAME,
                     dateAndTime,
                     ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_FILEEXT);
        }
        else
        {
            szOutputFileName[0] = '\0';
        }
    }

    if (strlen(szOutputFileName))
    {
        context->outputFile = fopen(szOutputFileName, "w");
        if (!context->outputFile)
        {
            ARSAL_PRINT(ARSAL_PRINT_WARNING, ARSTREAM2_STREAM_STATS_TAG, "Unable to open RTP stats output file '%s'", szOutputFileName);
        }
        else
        {
            ARSAL_PRINT(ARSAL_PRINT_INFO, ARSTREAM2_STREAM_STATS_TAG, "Opened RTP stats output file '%s'", szOutputFileName);
        }
    }

    if (context->outputFile)
    {
        char szTitle[200];
        int titleLen = 0;
        szTitle[0] = '\0';
        if ((friendlyName) && (strlen(friendlyName)))
        {
            titleLen += snprintf(szTitle + titleLen, 200 - titleLen, "%s ", friendlyName);
        }
        titleLen += snprintf(szTitle + titleLen, 200 - titleLen, "%s", dateAndTime);
        ARSAL_PRINT(ARSAL_PRINT_INFO, ARSTREAM2_STREAM_STATS_TAG, "RTP stats output file title: '%s'", szTitle);
        fprintf(context->outputFile, "# %s\n", szTitle);
        fprintf(context->outputFile, "timestamp rssi roundTripDelay interarrivalJitter receiverLostCount receiverFractionLost receiverExtHighestSeqNum");
        fprintf(context->outputFile, " lastSenderReportInterval senderReportIntervalPacketCount senderReportIntervalByteCount senderPacketCount senderByteCount peerClockDelta roundTripDelayFromClockDelta");
        fprintf(context->outputFile, "\n");
        fflush(context->outputFile);
        context->fileOutputTimestamp = 0;
    }
}


void ARSTREAM2_StreamStats_RtpStatsFileClose(ARSTREAM2_StreamStats_RtpStatsContext_t *context)
{
    if (context->outputFile)
    {
        fclose(context->outputFile);
        context->outputFile = NULL;
    }
}


void ARSTREAM2_StreamStats_RtpStatsFileWrite(ARSTREAM2_StreamStats_RtpStatsContext_t *context, const ARSTREAM2_RTP_RtpStats_t *rtpStats)
{
    if ((!context) || (!rtpStats))
    {
        return;
    }

    if (!context->outputFile)
    {
        return;
    }

    if (context->fileOutputTimestamp == 0)
    {
        /* init */
        context->fileOutputTimestamp = rtpStats->timestamp;
    }
    if (rtpStats->timestamp >= context->fileOutputTimestamp + ARSTREAM2_STREAM_STATS_RTP_STATS_OUTPUT_INTERVAL)
    {
        if (context->outputFile)
        {
            fprintf(context->outputFile, "%llu %i %lu %lu %lu %lu %lu", (long long unsigned int)rtpStats->timestamp, rtpStats->rssi,
                    (long unsigned int)rtpStats->roundTripDelay, (long unsigned int)rtpStats->interarrivalJitter,
                    (long unsigned int)rtpStats->receiverLostCount, (long unsigned int)rtpStats->receiverFractionLost,
                    (long unsigned int)rtpStats->receiverExtHighestSeqNum);
            fprintf(context->outputFile, " %lu %lu %lu %lu %llu %lld %lu",
                    (long unsigned int)rtpStats->lastSenderReportInterval, (long unsigned int)rtpStats->senderReportIntervalPacketCount,
                    (long unsigned int)rtpStats->senderReportIntervalByteCount, (long unsigned int)rtpStats->senderPacketCount,
                    (long long unsigned int)rtpStats->senderByteCount, (long long int)rtpStats->peerClockDelta,
                    (long unsigned int)rtpStats->roundTripDelayFromClockDelta);
            fprintf(context->outputFile, "\n");
            fflush(context->outputFile);
        }
        context->fileOutputTimestamp = rtpStats->timestamp;
    }
}
