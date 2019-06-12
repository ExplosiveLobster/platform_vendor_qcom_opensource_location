/* Copyright (c) 2019 The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <LocationClientApiImpl.h>

namespace location_client {

void translateDiagGnssLocationPositionDynamics(clientDiagGnssLocationPositionDynamics& out,
        const GnssLocationPositionDynamics& in) {
    out.bodyFrameDataMask = in.bodyFrameDataMask;
    out.longAccel = in.longAccel;
    out.latAccel = in.latAccel;
    out.vertAccel = in.vertAccel;
    out.yawRate = in.yawRate;
    out.pitch = in.pitch;
    out.longAccelUnc = in.longAccelUnc;
    out.latAccelUnc = in.latAccelUnc;
    out.vertAccelUnc = in.vertAccelUnc;
    out.yawRateUnc = in.yawRateUnc;
    out.pitchUnc = in.pitchUnc;
}

clientDiagGnssSystemTimeStructType parseDiagGnssTime(
        const GnssSystemTimeStructType &halGnssTime) {

    clientDiagGnssSystemTimeStructType gnssTime;
    memset(&gnssTime, 0, sizeof(gnssTime));
    uint32_t gnssTimeFlags = 0;

    if (GNSS_SYSTEM_TIME_WEEK_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_TIME_WEEK_VALID;
        gnssTime.systemWeek = halGnssTime.systemWeek;
    }
    if (GNSS_SYSTEM_TIME_WEEK_MS_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_TIME_WEEK_MS_VALID;
        gnssTime.systemMsec = halGnssTime.systemMsec;
    }
    if (GNSS_SYSTEM_CLK_TIME_BIAS_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_CLK_TIME_BIAS_VALID;
        gnssTime.systemClkTimeBias = halGnssTime.systemClkTimeBias;
    }
    if (GNSS_SYSTEM_CLK_TIME_BIAS_UNC_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_CLK_TIME_BIAS_UNC_VALID;
        gnssTime.systemClkTimeUncMs = halGnssTime.systemClkTimeUncMs;
    }
    if (GNSS_SYSTEM_REF_FCOUNT_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_REF_FCOUNT_VALID;
        gnssTime.refFCount = halGnssTime.refFCount;
    }
    if (GNSS_SYSTEM_NUM_CLOCK_RESETS_VALID & halGnssTime.validityMask) {
        gnssTimeFlags |= GNSS_SYSTEM_NUM_CLOCK_RESETS_VALID;
        gnssTime.numClockResets = halGnssTime.numClockResets;
    }

    gnssTime.validityMask = (clientDiagGnssSystemTimeStructTypeFlags)gnssTimeFlags;

    return gnssTime;
}

clientDiagGnssGloTimeStructType parseDiagGloTime(const GnssGloTimeStructType &halGloTime) {

    clientDiagGnssGloTimeStructType gloTime;
    memset(&gloTime, 0, sizeof(gloTime));
    uint32_t gloTimeFlags = 0;

    if (GNSS_CLO_DAYS_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_CLO_DAYS_VALID;
        gloTime.gloDays = halGloTime.gloDays;
    }
    if (GNSS_GLO_MSEC_VALID  & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_MSEC_VALID ;
        gloTime.gloMsec = halGloTime.gloMsec;
    }
    if (GNSS_GLO_CLK_TIME_BIAS_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_CLK_TIME_BIAS_VALID;
        gloTime.gloClkTimeBias = halGloTime.gloClkTimeBias;
    }
    if (GNSS_GLO_CLK_TIME_BIAS_UNC_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_CLK_TIME_BIAS_UNC_VALID;
        gloTime.gloClkTimeUncMs = halGloTime.gloClkTimeUncMs;
    }
    if (GNSS_GLO_REF_FCOUNT_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_REF_FCOUNT_VALID;
        gloTime.refFCount = halGloTime.refFCount;
    }
    if (GNSS_GLO_NUM_CLOCK_RESETS_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_NUM_CLOCK_RESETS_VALID;
        gloTime.numClockResets = halGloTime.numClockResets;
    }
    if (GNSS_GLO_FOUR_YEAR_VALID & halGloTime.validityMask) {
        gloTimeFlags |= GNSS_GLO_FOUR_YEAR_VALID;
        gloTime.gloFourYear = halGloTime.gloFourYear;
    }

    gloTime.validityMask = (clientDiagGnssGloTimeStructTypeFlags)gloTimeFlags;

    return gloTime;
}

void translateDiagSystemTime(clientDiagGnssSystemTime& out,
        const GnssSystemTime& in) {
    out.gnssSystemTimeSrc = (clientDiagGnss_LocSvSystemEnumType)in.gnssSystemTimeSrc;
    switch (in.gnssSystemTimeSrc) {
        case GNSS_LOC_SV_SYSTEM_GPS:
           out.u.gpsSystemTime = parseDiagGnssTime(in.u.gpsSystemTime);
           break;
        case GNSS_LOC_SV_SYSTEM_GALILEO:
           out.u.galSystemTime = parseDiagGnssTime(in.u.galSystemTime);
           break;
        case GNSS_LOC_SV_SYSTEM_GLONASS:
           out.u.gloSystemTime = parseDiagGloTime(in.u.gloSystemTime);
           break;
        case GNSS_LOC_SV_SYSTEM_BDS:
           out.u.bdsSystemTime = parseDiagGnssTime(in.u.bdsSystemTime);
           break;
        case GNSS_LOC_SV_SYSTEM_QZSS:
           out.u.qzssSystemTime = parseDiagGnssTime(in.u.qzssSystemTime);
           break;
        default:
           break;
    }
}

clientDiagGnssLocationSvUsedInPosition parseDiagLocationSvUsedInPosition(
        const GnssLocationSvUsedInPosition &halSv) {

    clientDiagGnssLocationSvUsedInPosition clientSv;
    clientSv.gpsSvUsedIdsMask = halSv.gpsSvUsedIdsMask;
    clientSv.gloSvUsedIdsMask = halSv.gloSvUsedIdsMask;
    clientSv.galSvUsedIdsMask = halSv.galSvUsedIdsMask;
    clientSv.bdsSvUsedIdsMask = halSv.bdsSvUsedIdsMask;
    clientSv.qzssSvUsedIdsMask = halSv.qzssSvUsedIdsMask;

    return clientSv;
}

void translateDiagGnssMeasUsageInfo(clientDiagGnssMeasUsageInfo& out,
        const GnssMeasUsageInfo& in) {
    out.gnssSignalType = in.gnssSignalType;
   /** Specifies GNSS Constellation Type */
    out.gnssConstellation = (clientDiagGnss_LocSvSystemEnumType)in.gnssConstellation;
    /**  GNSS SV ID.
     For GPS:      1 to 32
     For GLONASS:  65 to 96. When slot-number to SV ID mapping is unknown, set as 255.
     For SBAS:     120 to 151
     For QZSS-L1CA:193 to 197
     For BDS:      201 to 237
     For GAL:      301 to 336 */
    out.gnssSvId = in.gnssSvId;
}

void populateClientDiagLocation(clientDiagGnssLocationStructType* diagGnssLocPtr,
        const GnssLocation& gnssLocation) {
    diagGnssLocPtr->timestamp = gnssLocation.timestamp;
    diagGnssLocPtr->latitude = gnssLocation.latitude;
    diagGnssLocPtr->longitude = gnssLocation.longitude;
    diagGnssLocPtr->altitude = gnssLocation.altitude;
    diagGnssLocPtr->speed = gnssLocation.speed;
    diagGnssLocPtr->bearing = gnssLocation.bearing;
    diagGnssLocPtr->horizontalAccuracy = gnssLocation.horizontalAccuracy;
    diagGnssLocPtr->verticalAccuracy = gnssLocation.verticalAccuracy;
    diagGnssLocPtr->speedAccuracy = gnssLocation.speedAccuracy;
    diagGnssLocPtr->bearingAccuracy = gnssLocation.bearingAccuracy;
    diagGnssLocPtr->flags = gnssLocation.flags;
    diagGnssLocPtr->techMask = gnssLocation.techMask;

    diagGnssLocPtr->gnssInfoFlags = gnssLocation.gnssInfoFlags;
    diagGnssLocPtr->altitudeMeanSeaLevel = gnssLocation.altitudeMeanSeaLevel;
    diagGnssLocPtr->pdop = gnssLocation.pdop;
    diagGnssLocPtr->hdop = gnssLocation.hdop;
    diagGnssLocPtr->vdop = gnssLocation.vdop;
    diagGnssLocPtr->gdop = gnssLocation.gdop;
    diagGnssLocPtr->tdop = gnssLocation.tdop;
    diagGnssLocPtr->magneticDeviation = gnssLocation.magneticDeviation;
    diagGnssLocPtr->horReliability = (clientDiagLocationReliability)gnssLocation.horReliability;
    diagGnssLocPtr->verReliability = (clientDiagLocationReliability)gnssLocation.verReliability;
    diagGnssLocPtr->horUncEllipseSemiMajor = gnssLocation.horUncEllipseSemiMajor;
    diagGnssLocPtr->horUncEllipseSemiMinor = gnssLocation.horUncEllipseSemiMinor;
    diagGnssLocPtr->horUncEllipseOrientAzimuth = gnssLocation.horUncEllipseOrientAzimuth;
    diagGnssLocPtr->northStdDeviation = gnssLocation.northStdDeviation;
    diagGnssLocPtr->eastStdDeviation = gnssLocation.eastStdDeviation;
    diagGnssLocPtr->northVelocity = gnssLocation.northVelocity;
    diagGnssLocPtr->eastVelocity = gnssLocation.eastVelocity;
    diagGnssLocPtr->upVelocity = gnssLocation.upVelocity;
    diagGnssLocPtr->northVelocityStdDeviation = gnssLocation.northVelocityStdDeviation;
    diagGnssLocPtr->eastVelocityStdDeviation = gnssLocation.eastVelocityStdDeviation;
    diagGnssLocPtr->upVelocityStdDeviation = gnssLocation.upVelocityStdDeviation;
    diagGnssLocPtr->svUsedInPosition =
            parseDiagLocationSvUsedInPosition(gnssLocation.svUsedInPosition);
    diagGnssLocPtr->navSolutionMask = gnssLocation.navSolutionMask;
    diagGnssLocPtr->posTechMask = gnssLocation.posTechMask;
    translateDiagGnssLocationPositionDynamics(diagGnssLocPtr->bodyFrameData,
            gnssLocation.bodyFrameData);
    translateDiagSystemTime(diagGnssLocPtr->gnssSystemTime, gnssLocation.gnssSystemTime);
    diagGnssLocPtr->numOfMeasReceived = (uint8_t)gnssLocation.measUsageInfo.size();
    clientDiagGnssMeasUsageInfo measUsage;
    memset(diagGnssLocPtr->measUsageInfo, 0, sizeof(diagGnssLocPtr->measUsageInfo));
    for (int idx = 0; idx < gnssLocation.measUsageInfo.size(); idx++) {
        translateDiagGnssMeasUsageInfo(measUsage, gnssLocation.measUsageInfo[idx]);
        diagGnssLocPtr->measUsageInfo[idx] = measUsage;
    }
    diagGnssLocPtr->leapSeconds = gnssLocation.leapSeconds;
    diagGnssLocPtr->timeUncMs = gnssLocation.timeUncMs;
}

void translateDiagGnssSv(clientDiagGnssSv& out, const GnssSv& in) {

    /** Unique Identifier */
    out.svId = in.svId;
    /** type of SV (GPS, SBAS, GLONASS, QZSS, BEIDOU, GALILEO) */
    out.type = (clientDiagGnssSvType)in.type;
    /** signal strength */
    out.cN0Dbhz = in.cN0Dbhz;
    /** elevation of SV (in degrees) */
    out.elevation = in.elevation;
    /** azimuth of SV (in degrees) */
    out.azimuth = in.azimuth;
    /** Bitwise OR of GnssSvOptionsBits */
    out.gnssSvOptionsMask = in.gnssSvOptionsMask;
}

void populateClientDiagGnssSv(clientDiagGnssSvStructType* diagGnssSvPtr,
        std::vector<GnssSv>& gnssSvs) {
    clientDiagGnssSv diagGnssSv;
    diagGnssSvPtr->count = gnssSvs.size();
    for (int idx = 0; idx < gnssSvs.size(); ++idx) {
        translateDiagGnssSv(diagGnssSv, gnssSvs[idx]);
        diagGnssSvPtr->gnssSvs[idx] = diagGnssSv;
    }
}
}