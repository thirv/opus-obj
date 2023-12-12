/* Copyright (c) 2016 Mark Harris, Jean-Marc Valin */
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "opus_multistream.h"
#include "opus.h"
#include "test_opus_common.h"


static int celt_ec_internal_error(void)
{
    OpusMSEncoder *enc;
    int err;
    unsigned char data[2460];
    int streams;
    int coupled_streams;
    unsigned char mapping[1];

    enc = opus_multistream_surround_encoder_create(16000, 1, 1, &streams,
        &coupled_streams, mapping, OPUS_APPLICATION_VOIP, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(8));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(OPUS_AUTO));
    {
        static const short pcm[320] =
        {
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,  1792,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,     0, 25600,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,     7,     0,   255,     0,     0,
                 0,     0,     0,     0,     0,     0,     0, 32767,    -1,
                 0,     0,     0,   100,     0, 16384,     0,     0,     0,
                 0,     0,     0,     4,     0,     0,  -256,   255,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,-32768,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,   128,     0,     0,     0,     0,
                 0,     0,     0,     0,  -256,     0,     0,    32,     0,
                 0,     0,     0,     0,     0,     0,  4352,     4,   228,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,  5632,     0,     0,
                 0,     0,-32768,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,   256,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
             -3944, 10500,  4285, 10459, -6474, 10204, -6539, 11601, -6824,
             13385, -7142, 13872,-11553, 13670, -7725, 13463, -6887,  7874,
             -5580, 12600, -4964, 12480,  3254, 11741, -4210,  9741, -3155,
              7558, -5468,  5431, -1073,  3641, -1304,     0,    -1,   343,
                26,     0,     0,   150,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,  1799,  1799,  1799,  1799,  1799, -2553,
                 7,  1792,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799, -9721
        };
        err = opus_multistream_encode(enc, pcm, 320, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9526, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, 25600, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9494, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9479, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
              -256,   255,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,   128,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,    32,     0,     0,     0,     0,     0,     0,     0,
              4352,     4,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,   148,     0,     0,     0,     0,
              5632
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(12));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(41));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(21425));
    {
        static const short pcm[40] =
        {
             10459, -6474, 10204, -6539, 11601, -6824, 13385, -7142, 13872,
            -11553, 13670, -7725, 13463, -6887, 12482, -5580, 12600, -4964,
             12480,  3254, 11741, -4210,  9741, -3155,  7558, -5468,  5431,
             -1073,  3641, -1304,     0,    -1,   343,    26,     0,     0,
                 0,     0,  -256,   226
        };
        err = opus_multistream_encode(enc, pcm, 40, data, 2460);
        opus_test_assert(err > 0);
        /* returns -3 */
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

static int mscbr_encode_fail10(void)
{
    OpusMSEncoder *enc;
    int err;
    unsigned char data[627300];
    static const unsigned char mapping[255] =
    {
          0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
         17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
         34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
         51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
         68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
         85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,
        102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,
        119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,
        136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,
        153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,
        170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,
        187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,
        204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,
        221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,
        238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254
    };

    enc = opus_multistream_encoder_create(8000, 255, 254, 1, mapping,
        OPUS_APPLICATION_RESTRICTED_LOWDELAY, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(2));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(2));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(14));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(57));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(3642675));
    {
        static const short pcm[20*255] =
        {
                 0
        };
        err = opus_multistream_encode(enc, pcm, 20, data, 627300);
        opus_test_assert(err > 0);
        /* returns -1 */
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

static int mscbr_encode_fail(void)
{
    OpusMSEncoder *enc;
    int err;
    unsigned char data[472320];
    static const unsigned char mapping[192] =
    {
          0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
         17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
         34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
         51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
         68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
         85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,
        102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,
        119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,
        136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,
        153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,
        170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,
        187,188,189,190,191
    };

    enc = opus_multistream_encoder_create(8000, 192, 189, 3, mapping,
        OPUS_APPLICATION_RESTRICTED_LOWDELAY, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_MEDIUMBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(8));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(15360));
    {
        static const short pcm[20*192] =
        {
                 0
        };
        err = opus_multistream_encode(enc, pcm, 20, data, 472320);
        opus_test_assert(err > 0);
        /* returns -1 */
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

static int object_analysis_uninit(void)
{
    OpusMSEncoder* enc;
    int err;
    unsigned char data[7380];
    int streams;
    int coupled_streams;
    unsigned char mapping[3];

    enc = opus_multistream_surround_encoder_create(24000, 3, 3, &streams,
        &coupled_streams, mapping, OPUS_APPLICATION_AUDIO, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(6));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(9));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(5));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(775410));
    {
        static const short pcm[1440 * 3] =
        {
             30449, 15083, 14088, 31205,-18678,-12830, 14090,-26138,-25337,
            -11541, -3254, 27628,-22270, 30953,-16136,-30745, 20991,-17406,
              5632,-14330, 28911,-25594, 17408,-20474, 13041, -8731,  2292,
             -3860, 24049, 10225,-19220, 10478, -4374, -1199,   148,  -330,
               -74,   593,   188,  1558, -4152, 15984, 15934, 15934, 15934,
             15934, 15934, 15934, 15934, 15934, 15934, 15934, 15934,  1598,
               156,  1604, -1163,  2278,-30018,-25821,-21763,-23776, 24066,
              9502, 25866,-25055, 10004,-24798,  7204, -4581, -9678,  1554,
             10553,  3102, 12193,  2443, 11955,  1213, 10689, -1293,   921,
             -4173,  8661, -6049,  8815,-21221,-14854, 23840, -9477,  8549,
              5278,  8743,  9375,  6940, 13038,  4826, 14598,  7721,-24308,
            -29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769, 24361,
             28648, 10274,-11292,-29665,-16417, 24346, 14580, 18707, 26323,
             -4410,-17711,  5133, 26328,-14579,-31008, 24583, 18404, 28417,
            -24350, 19453, 28642,-32513,-10777, -3079, 30188, -7686, 27635,
            -32521,-16384,-20240, -6386, 10986, 23827,-25880,-32752,-23321,
             14605, 32231,   780,-13849, 15119, 28647,  4888, -7705, 30750,
                64,     0, 32488,  6687,-20758, 19745, -2070,    -1,    -1,
                28,   256, -4608,  7168,  7444, 23557,-21998, 13064,  3345,
             -4086,-28915, -8594, 32262,  8461, 27387,-12275, 12012, 23563,
            -18719,-28410, 29144,-22271,-32562,-16384, 12528, -6386, 10986,
             23827,-25880,-32752,-23321, 14605, 32231,   780,-13849, 15119,
             28647,  4888, -7705, 30750,    64,     0, 32488,  6687,-20758,
             19745, -2070,-13792, -6414, 28188, -2821, -4585,  7168,  7444,
             23557,-21998, 13064,  3345, -4086,-28915, -8694, 32262,  8461,
            -14853,-14907,-14907,-14907,-14907, 32767,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14891,-14907,-14907,-14907,
            -14907,-14907,  8901,  9375,  6940, 13038,  4826, 14598,  7721,
            -24308,-29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769,
             24361, 28648, 10274,-11292,-29665,-16417, 24346, 14580, 18707,
             26323, -4440,-17711,  5133, 26328,-14579,-31008, 24583, 18404,
             28417,-24350, 19453, 28642,-32513,-10777, -3079, 30188, -7686,
             27635,-32521,-16384,-20240, -6386, 10986, 23827,-25880,-32752,
            -23321, 14605, 32231,   780,-13849, 15119, 28647,  4888, -7705,
            -15074,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,  8192,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14897,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-15931,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907, 26121, 12890,
              2604, 12228,-11634, 12299,  5573,-16642, 32452, 29182,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-10811,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14917,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14938,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,  -571, -9986,   -58, 12542,-18491,
             32507, 12838,  6653,   294,    -1,     0,-19968, 18368, -4357,
             -5696,  2804, 12998,-22802,-22080, -7701, -5183,   486, -3133,
             -5660, -1083, 13799,-28726,-11029,   205,-14848, 32464,    -1,
              -129,-13072,  6380, -7948, 20717, 18425, 17392, 14335, -5646,
             30973, -3598,  7188, -3867,  3055, -4247,  5597, -4011,-26427,
               -11,-30418,  7922,  2614,   237, -5839,-27413,-17624,-29716,
            -13539,   239, 20991, 18164, -4082,-16647,-27386, 19458, 20224,
              4619, 19728, -7409,-18186,-25073, 27627,-23539, -7945,-31464,
             14330,-12523,-22021, -7701, -5183,   486, -3133, -5660, -1083,
             13799,-28726,-11029,   205,-14848, 32464,    -1,  -129,-13072,
              6380, -7948, 20717, 18425, 17392, 14093, -5646, 30973, -3598,
              7188, -3867,  3055,  3689, -5401,  4906, -6051,  4250, -6272,
              3492, -6343,  3197, -6397,  4041, -6341,  6255, -6381,   239,
             20991, 18164, -4082,-16647,-27386, 19458, 20224,  4619, 19728,
             -7409,-18186,-25073, 27627,-23539, -7945,-31464, 14330,-12523,
             14843, -6130, 30202,  -250,-28420, 10467, 16907, -3359, -6644,
             31965,  3343,-11727,  2966,-12616,  3064,-13472,  6732,-12349,
              5541,-11965,  5530,-10820, -1912, -3637, 32285, -4607,   310,
            -32768,     0, -5258,  2106, -6857,  2681, -5449, -3606, -6717,
             -5482, -3606, -1853,  4082, -7631, -9808, -1742, -2851, -5112,
                64,  -868,-13546,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,  7883, -2316,
              9086, -3944, 10500,  4285, 10459, -6474, 10204, -6539, 11601,
             -6824, 13385, -7142, 13872, -7457, 13670, -7725, 13463, -6887,
             12482, -5580, 12600, -4964, 12480,  3254, 11741, -4210,-24819,
             23282, 22798,   491, -1774, -1073,  3641, -1304, 28928,  -250,
            -27396,  6657, -8961, 22524, 19987, 10231,  1791,  8947,-32763,
            -26385,-31227,  -792,-30461,  8926,  4866, 27863, 27756, 27756,
             27756, 27756, 27756, 27756, 27756, 27756,  5630,-11070,-16136,
             20671,-11530, 27328,  8179,  5059,-31503,-24379,-19472, 17863,
            -29202, 22986,   -23,  8909,  8422, 10450
        };
        err = opus_multistream_encode(enc, pcm, 1440, data, 7380);
        /* reads uninitialized data at src/opus_multistream_encoder.c:293 */
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

static int surround_analysis_uninit(void)
{
    OpusMSEncoder *enc;
    int err;
    unsigned char data[7380];
    int streams;
    int coupled_streams;
    unsigned char mapping[3];

    enc = opus_multistream_surround_encoder_create(24000, 3, 1, &streams,
        &coupled_streams, mapping, OPUS_APPLICATION_AUDIO, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(8));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(84315));
    {
        static const short pcm[960*3] =
        {
             -6896,  4901, -6158,  4120, -5164,  3631, -4442,  3153, -4070,
              3349, -4577,  4474, -5541,  5058, -6701,  3881, -7933,  1863,
             -8041,   697, -6738,-31464, 14330,-12523,  4096, -6130, 29178,
              -250,-21252, 10467, 16907, -3359, -6644, 31965, 14607,-21544,
            -32497, 24020, 12557,-26926,-18421, -1842, 24587, 19659,  4878,
             10954, 23060,  8907,-10215,-16179, 31772,-11825,-15590,-23089,
             17173,-25903,-17387, 11733,  4884, 10204,-16476,-14367,   516,
             20453,-16898, 20967,-23813,   -20, 22011,-17167,  9459, 32499,
            -25855,  -523, -3883,  -390, -4206,   634, -3767,  2325, -2751,
              3115, -2392,  2746, -2173,  2317, -1147,  2326, 23142, 11314,
            -15350,-24529,  3026,  6146,  2150,  2476,  1105,  -830,  1775,
             -3425,  3674,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
              4293,-14023,  3879,-15553,  3158,-16161,  2629, 18433,-12535,
             -6645,-20735,-32763,-13824,-20992, 25859, 13052, -8731,  2292,
             -3860, 24049, 10225,-19220, 10478,-22294, 22773, 28137, 13816,
             30953,-25863,-24598, 16888,-14612,-28942, 20974,-27397,-18944,
            -18690, 20991,-16638,  5632,-14330, 28911,-25594, 17408, 29958,
              -517,-20984, -1800, 11281,  9977,-21221,-14854, 23840, -9477,
              3362,-12805,-22493, 32507,   156, 16384, -1163,  2301, -1874,
              4600, -1748,  6950, 16557,  8192, -7372, -1033, -3278,  2806,
             20275,  3317,  -717,  9792,  -767,  9099,  -613,  8362,  5027,
              7774,  2597,  8549,  5278,  8743,  9343,  6940, 13038,  4826,
             14086,  2964, 13215,  1355, 11596,   455,  9850,  -519, 10680,
             -2287, 12551, -3736, 13639, -4291, 13790, -2722, 14544,  -866,
             15050,  -304, 22833, -1196, 13520, -2063, 13051, -2317, 13066,
             -2737, 13773, -2664, 14105, -3447, 13854, 24589, 24672, -5280,
             10388, -4933,  7543, -4149,  3654, -1552,  1726,   661,    57,
              2922,  -751,  3917,  8419,  3840, -5218,  3435,  5540, -1073,
              4153, -6656,  1649,  -769, -7276,-13072,  6380, -7948, 20717,
             18425, 17392, 14335,-18190, -1842, 24587, 19659, 11790, 10954,
             23060,  8907,-10215,-16179, 31772,-11825,-15590,-23101, 17173,
            -25903,-17387, 11733,  4884, 10192,-16627,-14367,   516, 20453,
            -16898, 20967,-23813,   -20, 22011,-17167,  9468, 32499,-25607,
              -523, -3883,  -390, -4206,   634, -3767,  2325, -2751,  3115,
             -2392,  2746, -2161,  2317, -1147,  2326, 23142, 11314,-15350,
            -29137,  3026,-15056,  -491,-15170,  -386,-16015,  -641,-16505,
              -930,-16206,  -717,-16175, -2839,-16374, -4558,-16237, -5207,
            -15903, -6421,  6373, -1403,  5431, -1073,  3641, -1304, -4495,
              -769, -7276,  2856, -7870,  3314, -8730,  3964,-10183,  4011,
            -11135,  3421,-11727,  2966,-12360,  2818,-13472,  3660,-13805,
              5162,-13478,  6434,-12840,  7335,-12420,  6865,-12349,  5541,
            -11965,  5530,-10820,  5132, -9197,  3367, -7745,  1223, -6910,
              -433, -6211, -1711, -4958, -1025, -3755,  -836, -3292, -1666,
             -2661,-10755, 31472,-27906, 31471, 18690,  5617, 16649, 11253,
            -22516,-17674,-31990,  3575,-31479,  5883, 26121, 12890, -6612,
             12228,-11634,   523, 26136,-21496, 20745,-15868, -4100,-24826,
             23282, 22798,   491, -1774, 15075,-27373,-13094,  6417,-29487,
             14608, 10185, 16143, 22211, -8436,  4288, -8694,  2375,  3023,
               486,  1455,   128,   202,   942,  -923,  2068, -1233,  -717,
             -1042, -2167, 32255, -4632,   310, -4458, -3639, -5258,  2106,
             -6857,  2681, -7497,  2765, -6601,  1945, -5219, 19154, -4877,
               619, -5719, -1928, -6208,  -121,   593,   188,  1558, -4152,
              1648,   156,  1604, -3664, -6862, -2851, -5112, -3600, -3747,
             -5081, -4428, -5592, 20974,-27397,-18944,-18690, 20991,-17406,
              5632,-14330, 28911, 15934, 15934, 15934, 15934, 15934, 15934,
             15934, 15934, 15934, 15934, 15934, 15934,-25594, 17408, 29958,
             -7173,-16888,  9098,  -613,  8362,   675,  7774,  2597,  8549,
              5278,  8743,  9375,  6940, 13038,  4826, 14598,  7721,-24308,
            -29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769, 24353,
             28648,  6946, -1363, 12485, -1187, 26074,-25055, 10004,-24798,
              7204, -4581, -9678,  1554, 10553,  3102, 12193,  2443, 11955,
              1213, 10689, -1293,   921, -4173, 10709, -6049,  8815, -7128,
              8147, -8308,  6847, -2977,  4920,-11447,-22426,-11794,  3514,
            -10220,  3430, -7993,  1926, -7072,   327, -7569,  -608, -7605,
              3695, -6271, -1579, -4877, -1419, -3103, -2197,   128, -3904,
              3760, -5401,  4906, -6051,  4250, -6272,  3492, -6343,  3197,
             -6397,  4041, -6341,  6255, -6381,  7905, 16504,     0, -6144,
              8062, -5606,  8622, -5555,    -9,    -1,  7423,     0,     1,
               238,  5148,  1309,  4700,  2218,  4403,  2573,  3568, 28303,
              1758,  3454, -1247,  3434, -4912,  2862, -7844,  1718,-10095,
               369,-12631,   128, -3904,  3632, -5401,  4906, -6051,  4250,
             -6272,  3492, -6343,  3197, -6397,  4041, -6341,  6255, -6381,
              7905, 16504,     0, -6144,  8062, -5606,  8622, -5555,  8439,
             -3382,  7398, -1170,  6132,   238,  5148,  1309,  4700,  2218,
              4403,  2573,  3568,  2703,  1758,  3454, -1247,  3434, -4912,
              2862, -7844,  1718,-10095,   369,-12631,  -259,-14632,   234,
            -15056,  -521,-15170,  -386,-16015,  -641,-16505,  -930,-16206,
             -1209,-16146, -2839,-16374, -4558,-16218, -5207,-15903, -6421,
            -15615, -6925,-14871, -6149,-13759, -5233,-12844, 18313, -4357,
             -5696,  2804, 12992,-22802, -6720, -9770, -7088, -8998, 14330,
            -12523, 14843, -6130, 29178,  -250,-27396, 10467, 16907, -3359,
             -6644, 31965, 14607,-21544,-32497, 24020, 12557,-26926,  -173,
              -129, -6401,  -130,-25089, -3841, -4916, -3048,   224,  -237,
             -3969,  -189, -3529,  -535, -3464,-14863,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14395,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,     0, 32512,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,  9925,  -718,  9753,  -767,
              9099,  -613,  8362,   675,  7774,  2597,  8549,  5278,  8743,
              9375,  6940, 13038,  4826, 14598,  7721,-24308,-29905,-19703,
            -17106,-16124, -3287,-26118,-19709,     0, 24353, 28648, 10274,
            -11292,-29665,-16417, 24346, 14553, 18707, 26323, -4596,-17711,
              5133, 26328,    13,-31168, 24583, 18404,-28927,-24350, 19453,
             28642,  1019,-10777, -3079, 30188, -7686, 27635,-32521,-16384,
             12528, -6386, 10986, 23827,-25880,-32752,-23321, 14605, 32231,
               780,-13849, 15119, 28647,  4888, -7705, 30750,    64,     0,
             32488,  6687,-20758, 19745, -2070,-13792, -6414, 28188, -2821,
             -4585,  7168,  7444, 23557,-21998, 13064,  3345, -4086,-28915,
             -8694, 32262,  8461, 27387,-12275, 12012, 23563,-18719,-28410,
             29144,-22271,  -562, -9986, -5434, 12288,  5573,-16642, 32448,
             29182, 32705,-30723, 24255,-19716, 18368, -4357, -5696,  2804,
             12992,-22802,-22080, -7701, -5183,   486, -3133, -5660, -1083,
             16871,-28726,-11029,-30259, -1209,-16146, -2839,-16374, -4558,
            -16218,-10523, 20697, -9500, -1316,  5431, -1073,  3641, -1304,
              1649,  -769, -7276,  2856, -7870,  3314, -8730,  3964,-10183,
              4011,-11135,  3421,-11727, 21398, 32767,    -1, 32486,    -1,
              6301,-13071,  6380, -7948,    -1, 32767,   240, 14081, -5646,
             30973, -3598,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907, 32767,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,  8901,  9375,  6940, 13038,  4826, 14598,  7721,-24308,
            -29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769, 24361,
             28648, 10274,-11292,-29665,-16417, 24346, 14580, 18707, 26323,
             -4440,-17711,  5133, 26328,-14579,-31008, 24583, 18404, 28417,
            -24350, 19453, 28642,-32513,-10777, -3079, 30188, -7686, 27635,
            -32521,-16384,-20240, -6386, 10986, 23827,-25880,-32752,-23321,
             14605, 32231,   780,-13849, 15119, 28647,  4888, -7705,-15074,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,  8192,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14897,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -15931,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907, 26121, 12890,  2604,
             12228,-11634, 12299,  5573,-16642, 32452, 29182, 32705,-30723,
             24255,-19716, 13248,-11779, -5696,  2804, 12992,-27666,-22080,
             -7701, -5183, -6682,-31464, 14330,-12523, 14843, -6130, 29178,
               -18,-27396, 10467, 16907, -3359, -6644, 31965, 14607,-21544,
            -32497, 24020, 12557,-26926,-18421,   706, 24587, 19659,  4878,
             10954, 23060,  8907,-10215,-22579, 31772,-11825,-15590,-23089,
             17173,-25903,-17387,  3285,  4884, 10204,-16627,-14367,   516,
             20453,-16898, 20967,-23815,   -20, 22011,-17167,  9468, 32499,
            -25607,  -523, -3883,  -390, -4206,   634, -3767,  2325, -2751,
              3115, -2392,  2746, -2173,  2317, -1147,  2326, 23142, 11314,
            -15130,-29137,  3026,  6146,  2150,  2476,  1105,  -830,  1775,
             -3425,  3674, -5287,  4609, -7175,  4922, -9579,  4556,-12007,
              4236,-14023,  3879,-15553,  3158,-16161,  2576, 18398,-12535,
             -6645,-20735,-32763,-13824,-20992, 25859,  5372, 12040, 13307,
             -4355,-30213,    -9, -6019, 14061,-31487,-13842, 30449, 15083,
             14088, 31205,-18678,-12830, 14090,-26138,-25337,-11541, -3254,
             27628,-22270, 30953,-16136,-30745, 20991,-17406,  5632,-14330,
             28911,-25594, 17408,-20474, 13041, -8731,  2292, -3860, 24049,
             10225,-19220, 10478, -4374, -1199,   148,  -330,   -74,   593,
               188,  1558, -4152, 15984, 15934, 15934, 15934, 15934, 15934,
             15934, 15934, 15934, 15934, 15934, 15934,  1598,   156,  1604,
             -1163,  2278,-30018,-25821,-21763,-23776, 24066,  9502, 25866,
            -25055, 10004,-24798,  7204, -4581, -9678,  1554, 10553,  3102,
             12193,  2443, 11955,  1213, 10689, -1293,   921, -4173,  8661,
             -6049,  8815,-21221,-14854, 23840, -9477,  8549,  5278,  8743,
              9375,  6940, 13038,  4826, 14598,  7721,-24308,-29905,-19703,
            -17106,-16124, -3287,-26118,-19709,-10769, 24361, 28648, 10274,
            -11292,-29665,-16417, 24346, 14580, 18707, 26323, -4410,-17711,
              5133, 26328,-14579,-31008, 24583, 18404, 28417,-24350, 19453,
             28642,-32513,-10777, -3079, 30188, -7686, 27635,-32521,-16384,
            -20240, -6386, 10986, 23827,-25880,-32752,-23321, 14605, 32231,
               780,-13849, 15119, 28647,  4888, -7705, 30750,    64,     0,
             32488,  6687,-20758, 19745, -2070,    -1,    -1,    28,   256,
             -4608,  7168,  7444, 23557,-21998, 13064,  3345, -4086,-28915,
             -8594, 32262,  8461, 27387,-12275, 12012, 23563,-18719,-28410,
             29144,-22271,-32562,-16384, 12528, -6386, 10986, 23827,-25880,
            -32752,-23321, 14605, 32231,   780,-13849, 15119, 28647,  4888,
             -7705, 30750,    64,     0, 32488,  6687,-20758, 19745, -2070,
            -13792, -6414, 28188, -2821, -4585,  7168,  7444, 23557,-21998,
             13064,  3345, -4086,-28915, -8694, 32262,  8461, 27387,-12275,
             12012, 23563,-18719,-28410, 29144,-22271,  -562, -9986, -5434,
             12288, -2107,-16643, 32452, 29182, 32705,-30723, 24255,-19716,
             18368, -4357, -5696,  2804, 12992,-22802,-22080, -7701, -5183,
               486, -3133, -5660, -1083, 16871,-28726,-11029,-30259, -1209,
            -16146, -2839,-16374, -4558,-16218,-10523, 20697, -9500, -1316,
              5431, -1073,  3641, -1304,  1649,  -769, -7276,  2856, -7870,
              3314, -8730,  3964,-10183,  4011,-11135,  3421,-11727, 21398,
             32767,    -1, 32486,    -1,   -99,-13072,  6380, -7948,  4864,
             32767, 17392, 14335, -5646, 30973, -3598,-10299,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14905,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-19771,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-16443,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-15931,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,    -1,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,  7877,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  -994, -7276,  2856, -7870,
              3314, -8730,  3964,-10183,  4011,-11135,  3421,-11727, 21398,
             32767,    -1, 32486,    -1,   -99,-13072,  6380, -7948,  4864,
             32767, 17392, 14335, -5646, 30973, -3598,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14905,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,   197,     0,-14977,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907, 12838,  6653,   294,
            -29699,-25821,-21763,-23776, 24066,  9502, 25866,-25055, 10004,
            -24798,  7204, -4581, -9678,  1554, 10553,  3102, 12193,  2443,
             11955,  1213, 10689, -1293,   921,   179,  8448, -6049,  8815,
             -7128,  8147, -8308,  6847, -9889,  4920,-11447,  3174,-11794,
              3514,-10220,  3430, 16384,  1926, -7072,   327, -7537,  -608,
             -7605, -1169, -6397, -1579, -4877, -1419, -3103, -2197,   128,
             -3904,  3632, -5401,  4906, -6051,  4250, -6272,  3492, -6343,
              3197, -6397,  4041, -6341,  6255, -6381,  7905, 16504,     0,
             -6144,  8062, -5606,  8622, -5555,  8439, -3382,  7398, -1170,
              6132,   238,  5148,  1309,  4700,  2218,  4403,  2573,  3568,
              2703,  1758,  3454, -1247,  3434, -4912,  2862, -7844,  1718,
            -10095,   369,-12631,  -259,-14632,   234,-15056,  -491,-16194,
              -386,-16015,  -641,-16505,  -930,-16206, -1209,-16146, -2839,
            -16374, -4558,-16218, -5207,-15903, -6421,-15615, -6925,-14871,
             -6149,-13759, -5233,-12844, 18313, -4357, -5696,  2804, 12992,
            -22802, -6720, -9770, -7088, -8998, 14330,-12523, 14843, -6130,
             29178,  -250,-27396, 10467, 16907, -3359, -6644, 31965, 14607,
            -21544,-32497, 24020, 12557,-26926,  -173,  -129, -6401,  -130,
            -25089, -3816, -4916, -3048,   -32,    -1, -3969,   256, -3529,
              -535, -3464,-14863,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
             -1209,-16146, -2839,-16374, -4558,-16218,-10523, 20697, -9500,
             -1316,  5431, -1073,  3641, -1304,  1649,  -769, -7276,  2856,
             -7870,  3314, -8730,  3964,-10183,  4011,-11135,  3421,-11727,
             21398, 32767,    -1, 32486,    -1,  6301,-13071,  6380, -7948,
                -1, 32767,   240, 14081, -5646, 30973, -3598,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
             32767,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,  8901,  9375,  6940,
             13038,  4826, 14598,  7721,-24308,-29905,-19703,-17106,-16124,
             -3287,-26118,-19709,-10769, 24361, 28648, 10274,-11292,-29665,
            -16417, 24346, 14580, 18707, 26323, -4440,-17711,  5133, 26328,
            -14579,-31008, 24583, 18404, 28417,-24350, 19453, 28642,-32513,
            -10777, -3079, 30188, -7686, 27635,-32521,-16384,-20240, -6386,
             10986, 23827,-25880,-32752,-23321, 14605, 32231,   780,-13849,
             15119, 28647,  4888, -7705,-15074,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,  8192,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14897,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-15931,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907, 26121, 12890,  2604, 12228,-11634, 12299,  5573,
            -16642, 32452, 29182, 32705,-30723, 24255,-19716, 13248,-11779,
             -5696,  2804, 12992,-27666,-22080, -7701, -5183, -6682,-31464,
             14330,-12523, 14843, -6130, 29178,   -18,-27396, 10467, 16907,
             -3359, -6644, 31965, 14607,-21544,-32497, 24020, 12557,-26926,
            -18421,   706, 24587, 19659,  4878, 10954, 23060,  8907,-10215,
            -22579, 31772,-11825,-15590,-23089, 17173,-25903,-17387,  3285,
              4884, 10204,-16627,-14367,   516, 20453,-16898, 20967,-23815,
               -20, 22011,-17167,  9468, 32499,-25607,  -523, -3883,  -390,
             -4206,   634, -3767,  2325, -2751,  3115, -2392,  2746, -2173,
              2317, -1147,  2326, 23142, 11314,-15130,-29137,  3026,  6146,
              2150,  2476,  1105,  -830,  1775, -3425,  3674, -5287,  4609,
             -7175,  4922, -9579,  4556,-12007,  4236,-14023,  3879,-15553,
              3158,-16161,  2576, 18398,-12535, -6645,-20735,-32763,-13824,
            -20992, 25859,  5372, 12040, 13307, -4355,-30213,    -9, -6019
        };
        err = opus_multistream_encode(enc, pcm, 960, data, 7380);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(6));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(9));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(5));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(775410));
    {
        static const short pcm[1440*3] =
        {
             30449, 15083, 14088, 31205,-18678,-12830, 14090,-26138,-25337,
            -11541, -3254, 27628,-22270, 30953,-16136,-30745, 20991,-17406,
              5632,-14330, 28911,-25594, 17408,-20474, 13041, -8731,  2292,
             -3860, 24049, 10225,-19220, 10478, -4374, -1199,   148,  -330,
               -74,   593,   188,  1558, -4152, 15984, 15934, 15934, 15934,
             15934, 15934, 15934, 15934, 15934, 15934, 15934, 15934,  1598,
               156,  1604, -1163,  2278,-30018,-25821,-21763,-23776, 24066,
              9502, 25866,-25055, 10004,-24798,  7204, -4581, -9678,  1554,
             10553,  3102, 12193,  2443, 11955,  1213, 10689, -1293,   921,
             -4173,  8661, -6049,  8815,-21221,-14854, 23840, -9477,  8549,
              5278,  8743,  9375,  6940, 13038,  4826, 14598,  7721,-24308,
            -29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769, 24361,
             28648, 10274,-11292,-29665,-16417, 24346, 14580, 18707, 26323,
             -4410,-17711,  5133, 26328,-14579,-31008, 24583, 18404, 28417,
            -24350, 19453, 28642,-32513,-10777, -3079, 30188, -7686, 27635,
            -32521,-16384,-20240, -6386, 10986, 23827,-25880,-32752,-23321,
             14605, 32231,   780,-13849, 15119, 28647,  4888, -7705, 30750,
                64,     0, 32488,  6687,-20758, 19745, -2070,    -1,    -1,
                28,   256, -4608,  7168,  7444, 23557,-21998, 13064,  3345,
             -4086,-28915, -8594, 32262,  8461, 27387,-12275, 12012, 23563,
            -18719,-28410, 29144,-22271,-32562,-16384, 12528, -6386, 10986,
             23827,-25880,-32752,-23321, 14605, 32231,   780,-13849, 15119,
             28647,  4888, -7705, 30750,    64,     0, 32488,  6687,-20758,
             19745, -2070,-13792, -6414, 28188, -2821, -4585,  7168,  7444,
             23557,-21998, 13064,  3345, -4086,-28915, -8694, 32262,  8461,
            -14853,-14907,-14907,-14907,-14907, 32767,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14891,-14907,-14907,-14907,
            -14907,-14907,  8901,  9375,  6940, 13038,  4826, 14598,  7721,
            -24308,-29905,-19703,-17106,-16124, -3287,-26118,-19709,-10769,
             24361, 28648, 10274,-11292,-29665,-16417, 24346, 14580, 18707,
             26323, -4440,-17711,  5133, 26328,-14579,-31008, 24583, 18404,
             28417,-24350, 19453, 28642,-32513,-10777, -3079, 30188, -7686,
             27635,-32521,-16384,-20240, -6386, 10986, 23827,-25880,-32752,
            -23321, 14605, 32231,   780,-13849, 15119, 28647,  4888, -7705,
            -15074,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,  8192,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14897,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-15931,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907, 26121, 12890,
              2604, 12228,-11634, 12299,  5573,-16642, 32452, 29182,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,  7710,
              7710,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-10811,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14917,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14938,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,-14907,
            -14907,-14907,-14907,-14907,  -571, -9986,   -58, 12542,-18491,
             32507, 12838,  6653,   294,    -1,     0,-19968, 18368, -4357,
             -5696,  2804, 12998,-22802,-22080, -7701, -5183,   486, -3133,
             -5660, -1083, 13799,-28726,-11029,   205,-14848, 32464,    -1,
              -129,-13072,  6380, -7948, 20717, 18425, 17392, 14335, -5646,
             30973, -3598,  7188, -3867,  3055, -4247,  5597, -4011,-26427,
               -11,-30418,  7922,  2614,   237, -5839,-27413,-17624,-29716,
            -13539,   239, 20991, 18164, -4082,-16647,-27386, 19458, 20224,
              4619, 19728, -7409,-18186,-25073, 27627,-23539, -7945,-31464,
             14330,-12523,-22021, -7701, -5183,   486, -3133, -5660, -1083,
             13799,-28726,-11029,   205,-14848, 32464,    -1,  -129,-13072,
              6380, -7948, 20717, 18425, 17392, 14093, -5646, 30973, -3598,
              7188, -3867,  3055,  3689, -5401,  4906, -6051,  4250, -6272,
              3492, -6343,  3197, -6397,  4041, -6341,  6255, -6381,   239,
             20991, 18164, -4082,-16647,-27386, 19458, 20224,  4619, 19728,
             -7409,-18186,-25073, 27627,-23539, -7945,-31464, 14330,-12523,
             14843, -6130, 30202,  -250,-28420, 10467, 16907, -3359, -6644,
             31965,  3343,-11727,  2966,-12616,  3064,-13472,  6732,-12349,
              5541,-11965,  5530,-10820, -1912, -3637, 32285, -4607,   310,
            -32768,     0, -5258,  2106, -6857,  2681, -5449, -3606, -6717,
             -5482, -3606, -1853,  4082, -7631, -9808, -1742, -2851, -5112,
                64,  -868,-13546,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,-13365,
            -13365,-13365,-13365,-13365,-13365,-13365,-13365,  7883, -2316,
              9086, -3944, 10500,  4285, 10459, -6474, 10204, -6539, 11601,
             -6824, 13385, -7142, 13872, -7457, 13670, -7725, 13463, -6887,
             12482, -5580, 12600, -4964, 12480,  3254, 11741, -4210,-24819,
             23282, 22798,   491, -1774, -1073,  3641, -1304, 28928,  -250,
            -27396,  6657, -8961, 22524, 19987, 10231,  1791,  8947,-32763,
            -26385,-31227,  -792,-30461,  8926,  4866, 27863, 27756, 27756,
             27756, 27756, 27756, 27756, 27756, 27756,  5630,-11070,-16136,
             20671,-11530, 27328,  8179,  5059,-31503,-24379,-19472, 17863,
            -29202, 22986,   -23,  8909,  8422, 10450
        };
        err = opus_multistream_encode(enc, pcm, 1440, data, 7380);
        /* reads uninitialized data at src/opus_multistream_encoder.c:293 */
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

static int ec_enc_shrink_assert(void)
{
    OpusEncoder *enc;
    int err;
    int data_len;
    unsigned char data[2000];
    static const short pcm1[960] = { 5140 };
    static const short pcm2[2880] =
    {
          -256,-12033,     0, -2817,  6912,     0, -5359,  5200,  3061,
             0, -2903,  5652, -1281,-24656,-14433,-24678,    32,-29793,
          2870,     0,  4096,  5120,  5140,  -234,-20230,-24673,-24633,
        -24673,-24705,     0,-32768,-25444,-25444,     0,-25444,-25444,
           156,-20480, -7948, -5920, -7968, -7968,   224,     0, 20480,
            11, 20496,    13, 20496,    11,-20480,  2292,-20240,   244,
         20480,    11, 20496,    11,-20480,   244,-20240,  7156, 20456,
          -246,-20243,   244,   128,   244, 20480,    11, 20496,    11,
        -20480,   244,-20256,   244, 20480,   256,     0,  -246, 16609,
          -176,     0, 29872, -4096, -2888,   516,  2896,  4096,  2896,
        -20480, -3852, -2896, -1025,-31056,-14433,   244,  1792,  -256,
        -12033,     0, -2817,     0,     0, -5359,  5200,  3061,    16,
         -2903,  5652, -1281,-24656,-14433,-24678,    32,-29793,  2870,
             0,  4096,  5120,  5140,  -234,-20230,-24673,-24633,-24673,
        -24705,     0,-32768,-25444,-25444,     0,-25444,-25444,   156,
        -20480, -7973, -5920, -7968, -7968,   224,     0, 20480,    11,
         20496,    11, 20496,    11,-20480,  2292,-20213,   244, 20480,
            11, 20496,    11,-24698, -2873,     0,     7,    -1,   208,
          -256,   244,     0,  4352, 20715, -2796,    11,-22272,  5364,
          -234,-20230,-24673,-25913,  8351,-24832, 13963,    11,     0,
            16,  5140,  5652, -1281,-24656,-14433,-24673, 32671,   159,
             0,-25472,-25444,   156,-25600,-25444,-25444,     0, -2896,
         -7968, -7960, -7968, -7968,     0,     0,  2896,  4096,  2896,
          4096,  2896,     0, -2896, -4088, -2896,     0,  2896,     0,
         -2896, -4096, -2896,    11,  2640, -4609, -2896,-32768, -3072,
             0,  2896,  4096,  2896,     0, -2896, -4096, -2896,     0,
            80,     1,  2816,     0, 20656,   255,-20480,   116,-18192
    };
    static const short pcm3[2880] = { 0 };

    enc = opus_encoder_create(48000, 1, OPUS_APPLICATION_AUDIO, &err);
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(6));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(6000));
    data_len = opus_encode(enc, pcm1, 960, data, 2000);
    opus_test_assert(data_len > 0);

    opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_SUPERWIDEBAND));
    opus_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(15600));
    data_len = opus_encode(enc, pcm2, 2880, data, 122);
    opus_test_assert(data_len > 0);

    opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(27000));
    data_len = opus_encode(enc, pcm3, 2880, data, 122); /* assertion failure */
    opus_test_assert(data_len > 0);

    opus_encoder_destroy(enc);
    return 0;
}

static int ec_enc_shrink_assert2(void)
{
    OpusEncoder *enc;
    int err;
    int data_len;
    unsigned char data[2000];

    enc = opus_encoder_create(48000, 1, OPUS_APPLICATION_AUDIO, &err);
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(6));
    opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(26));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(27000));
    {
        static const short pcm[960] = { 0 };
        data_len = opus_encode(enc, pcm, 960, data, 2000);
        opus_test_assert(data_len > 0);
    }
    opus_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    {
        static const short pcm[480] =
        {
            32767, 32767, 0, 0, 32767, 32767, 0, 0, 32767, 32767,
            -32768, -32768, 0, 0, -32768, -32768, 0, 0, -32768, -32768
        };
        data_len = opus_encode(enc, pcm, 480, data, 19);
        opus_test_assert(data_len > 0);
    }
    opus_encoder_destroy(enc);
    return 0;
}

static int silk_gain_assert(void)
{
    OpusEncoder *enc;
    int err;
    int data_len;
    unsigned char data[1000];
    static const short pcm1[160] = { 0 };
    static const short pcm2[960] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        32767, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 32767
    };

    enc = opus_encoder_create(8000, 1, OPUS_APPLICATION_AUDIO, &err);
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(3));
    opus_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(6000));
    data_len = opus_encode(enc, pcm1, 160, data, 1000);
    opus_test_assert(data_len > 0);

    opus_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_MEDIUMBAND));
    opus_encoder_ctl(enc, OPUS_SET_BITRATE(2867));
    data_len = opus_encode(enc, pcm2, 960, data, 1000);
    opus_test_assert(data_len > 0);

    opus_encoder_destroy(enc);
    return 0;
}

void regression_test(void)
{
   fprintf(stderr, "Running simple tests for bugs that have been fixed previously\n");
   celt_ec_internal_error();
   mscbr_encode_fail10();
   mscbr_encode_fail();
   surround_analysis_uninit();
   object_analysis_uninit();
   ec_enc_shrink_assert();
   ec_enc_shrink_assert2();
   silk_gain_assert();
}
