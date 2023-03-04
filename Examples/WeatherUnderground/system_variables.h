// You must uncomment the variable name to be uploaded for it to be included, then recompile

//#define SW_winddir          // e.g. = 230   [°] NOTE do-not assign/send units text!
//#define SW_windspeedmph     // e.g. = 12    [mph]
//#define SW_windgustmph      // e.g. = 12    [mph]
//#define SW_windspdmph_avg2m // e.g. = 12    [mph 2 minute average wind speed]
//#define SW_winddir_avg2m    // e.g. = 170   [° 0-360 2 minute average wind direction]
//#define SW_windgustmph_10m  // e.g. = 45    [mph 10 minutes wind gust]
//#define SW_windgustdir_10m  // e.g. = 252   [° 0-360 10 minutes wind gust direction]
#define SW_tempf            // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
//#define SW_temp2f           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
//#define SW_temp3f           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
//#define SW_temp4f           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
//#define SW_indoortempf      // e.g. = 65.3  [°F]
//#define SW_indoorhumidity   // e.g. = 52.3  [% range 0 - 100]
//#define SW_soiltempf        // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
//#define SW_soiltemp2f       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
//#define SW_soiltemp3f       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
//#define SW_soiltemp4f       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
//#define SW_soilmoisture     // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
//#define SW_soilmoisture2    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
//#define SW_soilmoisture3    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
//#define SW_soilmoisture4    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
//#define SW_leafwetness      // e.g. = 5     [% range 0 - 100]  * for sensor 2 use leafwetness2
//#define SW_leafwetness2     // e.g. = 7     [% range 0 - 100]  * for sensor 2 use leafwetness2
//#define SW_solarradiation   // e.g. = 548   [W/m^2]
//#define SW_UV               // e.g. = 2     [index 0 - 10]
//#define SW_visibility       // e.g. = 1.2   [nm visibility]
//#define SW_rainin           // e.g. = 1.65  [inches of rain]
//#define SW_dailyrainin      // e.g. = 0.65  [daily rain in inches accumulated]
//#define SW_baromin          // e.g. = 29.1  [inches of mercury]
#define SW_dewptf           // e.g. = 68.2  [°F]
#define SW_humidity         // e.g. = 90    [% range 0 - 100]
//#define SW_weather          // e.g. = "+RA" [text -- METAR style (+RA) means light rain showers]
//#define SW_clouds           // e.g. = "SCT" [text -- METAR style SKC, FEW, SCT, BKN, OVC respectively meaning Sky Clear, Few, Scattered, Broken, Overcast]
//#define SW_softwaretype     // e.g. = "vws" [text version01]
//#define SW_AqNO             // e.g. = 100   [No. (nitric oxide) ppb]
//#define SW_AqNO2T           // e.g. = 100   [(nitrogen dioxide), true measure ppb]
//#define SW_AqNO2            // e.g. = 100   [NO2 computed, NOx - NO ppb]
//#define SW_AqNO2Y           // e.g. = 100   [NO2 computed, NOy - NO ppb]
//#define SW_AqNOX            // e.g. = 100   [NOx (nitrogen oxides) - ppb]
//#define SW_AqNOY            // e.g. = 100   [NOy (total reactive nitrogen) - ppb]
//#define SW_AqNO3            // e.g. = 100   [NO3 ion (nitrate, not adjusted for ammonium ion) UG/M3]
//#define SW_AqSO4            // e.g. = 100   [SO4 ion (sulfate, not adjusted for ammonium ion) UG/M3]
//#define SW_AqSO2            // e.g. = 100   [(sulfur dioxide), conventional ppb]
//#define SW_AqSO2T           // e.g. = 100   [trace levels ppb]
//#define SW_AqCO             // e.g. = 100   [CO (carbon monoxide), conventional ppm]
//#define SW_AqCOT            // e.g. = 100   [CO trace levels ppb]
//#define SW_AqEC             // e.g. = 100   [EC (elemental carbon) – PM2.5 UG/M3]
//#define SW_AqOC             // e.g. = 100   [OC (organic carbon, not adjusted for oxygen and hydrogen) – PM2.5 UG/M3]
//#define SW_AqBC             // e.g. = 100   [BC (black carbon at 880 nm) UG/M3]
//#define SW_AqUV_AETH        // e.g. = 100   [UV-AETH (second channel of Aethalometer at 370 nm) UG/M3]
//#define SW_AqPM2_5          // e.g. = 100   [PM2.5 mass - UG/M3]
//#define SW_AqPM10           // e.g. = 100   [PM10 mass - PM10 mass]
//#define SW_AqOZONE          // e.g. = 100   [Ozone/O3 - ppb]
//############################################################################################################################
String WU_winddir;  // e.g. = 230   [° 0-360] NOTE do-not assign/send units text!
String WU_windspeedmph;     // e.g. = 12    [mph]
String WU_windgustmph;      // e.g. = 12    [mph]
String WU_windgustdir;      // e.g. = 90    [° 0-360]
String WU_windspdmph_avg2m; // e.g. = 12    [mph 2 minute average wind speed]
String WU_winddir_avg2m;    // e.g. = 170   [° 0-360 2 minute average wind direction]
String WU_windgustmph_10m;  // e.g. = 45    [mph 10 minutes wind gust]
String WU_windgustdir_10m;  // e.g. = 252   [° 0-360 10 minutes wind gust direction]
String WU_tempf;            // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
String WU_temp2f;           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
String WU_temp3f;           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
String WU_temp4f;           // e.g. = 71.2  [°F] * for extra outdoor sensors use temp2f, temp3f, and so on
String WU_indoortempf;      // e.g. = 65.3  [°F]
String WU_indoorhumidity;   // e.g. = 52.3  [% range 0 - 100]
String WU_soiltempf;        // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
String WU_soiltemp2f;       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
String WU_soiltemp3f;       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
String WU_soiltemp4f;       // e.g. = 45.7  [°F] * for sensors 2,3,4 use soiltemp2f, soiltemp3f, and soiltemp4f
String WU_soilmoisture;     // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
String WU_soilmoisture2;    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
String WU_soilmoisture3;    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
String WU_soilmoisture4;    // e.g. = 12    [% range 0 - 100]  * for sensors 2,3,4 use soilmoisture2, soilmoisture3, and soilmoisture4
String WU_leafwetness;      // e.g. = 5     [% range 0 - 100]  * for sensor 2 use leafwetness2
String WU_leafwetness2;     // e.g. = 7     [% range 0 - 100]  * for sensor 2 use leafwetness2
String WU_solarradiation;   // e.g. = 548   [W/m^2]
String WU_UV;               // e.g. = 2     [index 0 - 10]
String WU_visibility;       // e.g. = 1.2   [nm visibility]
String WU_rainin;           // e.g. = 1.65  [inches of rain]
String WU_dailyrainin;      // e.g. = 0.65  [daily rain in inches accumulated]
String WU_baromin;          // e.g. = 29.1  [inches of mercury]
String WU_dewptf;           // e.g. = 68.2  [°F]
String WU_humidity;         // e.g. = 90    [% range 0 - 100]
String WU_weather;          // e.g. = "+RA" [text -- METAR style (+RA) means light rain showers]
String WU_clouds;           // e.g. = "SCT" [text -- METAR style SKC, FEW, SCT, BKN, OVC respectively meaning Sky Clear, Few, Scattered, Broken, Overcast]
String WU_softwaretype;     // e.g. = "vws" [text version01]
String WU_AqNO;             // e.g. = 100   [No. (nitric oxide) ppb]
String WU_AqNO2T;           // e.g. = 100   [(nitrogen dioxide), true measure ppb]
String WU_AqNO2;            // e.g. = 100   [NO2 computed, NOx - NO ppb]
String WU_AqNO2Y;           // e.g. = 100   [NO2 computed, NOy - NO ppb]
String WU_AqNOX;            // e.g. = 100   [NOx (nitrogen oxides) - ppb]
String WU_AqNOY;            // e.g. = 100   [NOy (total reactive nitrogen) - ppb]
String WU_AqNO3;            // e.g. = 100   [NO3 ion (nitrate, not adjusted for ammonium ion) UG/M3]
String WU_AqSO4;            // e.g. = 100   [SO4 ion (sulfate, not adjusted for ammonium ion) UG/M3]
String WU_AqSO2;            // e.g. = 100   [(sulfur dioxide), conventional ppb]
String WU_AqSO2T;           // e.g. = 100   [trace levels ppb]
String WU_AqCO;             // e.g. = 100   [CO (carbon monoxide), conventional ppm]
String WU_AqCOT;            // e.g. = 100   [CO trace levels ppb]
String WU_AqEC;             // e.g. = 100   [EC (elemental carbon) – PM2.5 UG/M3]
String WU_AqOC;             // e.g. = 100   [OC (organic carbon, not adjusted for oxygen and hydrogen) – PM2.5 UG/M3]
String WU_AqBC;             // e.g. = 100   [BC (black carbon at 880 nm) UG/M3]
String WU_AqUV_AETH;        // e.g. = 100   [UV-AETH (second channel of Aethalometer at 370 nm) UG/M3]
String WU_AqPM2_5;          // e.g. = 100   [PM2.5 mass - UG/M3]
String WU_AqPM10;           // e.g. = 100   [PM10 mass - PM10 mass]
String WU_AqOZONE;          // e.g. = 100   [Ozone/O3 - ppb]
String WU_dateutc;          // e.g. = "2000-01-01+10%3A32%3A35" or "=now" must be escaped characters formated [YYYY-MM-DD HH:MM:SS (mysql format)] or dateutc=now
String WU_action;           // e.g. = "=updateraw"
