// -----------------------------------------
// Global definitions
// ----------------------------------------
// Header
#include "Constraints.h"

// Constants
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {
		{0, 0, 0},										// 0
		{0, DAC_MAX_VALUE, 0},							// 1	DAC_V200_NULL
		{0, DAC_MAX_VALUE, DAC_V200_DEF},				// 2	DAC_V200_TOP
		{0, DAC_MAX_VALUE, 0},							// 3	DAC_2V00_NULL
		{0, DAC_MAX_VALUE, DAC_2V00_DEF},				// 4	DAC_2V00_TOP
		{0, DAC_MAX_VALUE, 0},							// 5	DAC_20V0_NULL
		{0, DAC_MAX_VALUE, DAC_20V0_DEF},				// 6	DAC_20V0_TOP
		{0, DAC_MAX_VALUE, 0},							// 7	DAC_270V_NULL
		{0, DAC_MAX_VALUE, DAC_270V_DEF},				// 8	DAC_270V_TOP

		{0, 0, 0},										// 9	----
		{0, ADC_MAX_VALUE, 0},							// 10	ADC_BLV_V200_NULL
		{0, ADC_MAX_VALUE, ADC_BLV_V200_DEF},			// 11	ADC_BLV_V200_TOP
		{0, ADC_MAX_VALUE, 0},							// 12	ADC_BLV_2V00_NULL
		{0, ADC_MAX_VALUE, ADC_BLV_2V00_DEF},			// 13	ADC_BLV_2V00_TOP
		{0, ADC_MAX_VALUE, 0},							// 14	ADC_BLV_20V0_NULL
		{0, ADC_MAX_VALUE, ADC_BLV_20V0_DEF},			// 15	ADC_BLV_20V0_TOP
		{0, ADC_MAX_VALUE, 0},							// 16	ADC_BHV_270V_NULL
		{0, ADC_MAX_VALUE, ADC_BHV_270V_DEF},			// 17	ADC_BHV_270V_TOP
		{0, ADC_MAX_VALUE, 0},							// 18	ADC_POT_V200_NULL
		{0, ADC_MAX_VALUE, ADC_POT_V200_DEF},			// 19	ADC_POT_V200_TOP
		{0, ADC_MAX_VALUE, 0},							// 20	ADC_POT_2V00_NULL
		{0, ADC_MAX_VALUE, ADC_POT_2V00_DEF},			// 21	ADC_POT_2V00_TOP
		{0, ADC_MAX_VALUE, 0},							// 22	ADC_POT_20V0_NULL
		{0, ADC_MAX_VALUE, ADC_POT_20V0_DEF},			// 23	ADC_POT_20V0_TOP
		{0, ADC_MAX_VALUE, 0},							// 24	ADC_PHV_270V_NULL
		{0, ADC_MAX_VALUE, ADC_PHV_270V_DEF},			// 25	ADC_PHV_270V_TOP
		{0, 0, 0},										// 26
		{0, 0, 0},										// 27
		{0, 0, 0},										// 28
		{0, 0, 0},										// 29
		{0, ADC_MAX_VALUE, 0},							// 30	ADC_ILV_R1_NULL
		{0, ADC_MAX_VALUE, ADC_ILV_R1_DEF},				// 31	ADC_ILV_R1_TOP
		{0, ADC_MAX_VALUE, 0},							// 32	ADC_ILV_R2_NULL
		{0, ADC_MAX_VALUE, ADC_ILV_R2_DEF},				// 33	ADC_ILV_R2_TOP
		{0, ADC_MAX_VALUE, 0},							// 34	ADC_ILV_R3_NULL
		{0, ADC_MAX_VALUE, ADC_ILV_R3_DEF},				// 35	ADC_ILV_R3_TOP
		{0, ADC_MAX_VALUE, 0},							// 36	ADC_ILV_R4_NULL
		{0, ADC_MAX_VALUE, ADC_ILV_R4_DEF},				// 37	ADC_ILV_R4_TOP
		{0, ADC_MAX_VALUE, 0},							// 38
		{0, ADC_MAX_VALUE, 0},							// 39
		{0, ADC_MAX_VALUE, 0},							// 40	ADC_IHV_R1_NULL
		{0, ADC_MAX_VALUE, ADC_IHV_R1_DEF},				// 41	ADC_IHV_R1_TOP
		{0, ADC_MAX_VALUE, 0},							// 42	ADC_IHV_R2_NULL
		{0, ADC_MAX_VALUE, ADC_IHV_R2_DEF},				// 43	ADC_IHV_R2_TOP
		{0, ADC_MAX_VALUE, 0},							// 44	ADC_IHV_R3_NULL
		{0, ADC_MAX_VALUE, ADC_IHV_R3_DEF},				// 45	ADC_IHV_R3_TOP
		{0, 0, 0},										// 46
		{0, 0, 0},										// 47
		{0, 0, 0},										// 48
		{0, 0, 0},										// 49
		{DAC_LIMIT_MIN, DAC_LIMIT_MAX, DAC_LIMIT_DEF},	// 50	DAC_110MA_LIMIT
		{0, DAC_MAX_VALUE, 0},							// 51	DAC_100MKA_NULL
		{0, DAC_MAX_VALUE, DAC_100MKA_DEF},				// 52	DAC_100MKA_TOP
		{0, DAC_MAX_VALUE, 0},							// 53	DAC_1MA_NULL
		{0, DAC_MAX_VALUE, DAC_1MA_DEF},				// 54	DAC_1MA_TOP
		{0, DAC_MAX_VALUE, 0},							// 55	DAC_10MA_NULL
		{0, DAC_MAX_VALUE, DAC_10MA_DEF},				// 56	DAC_10MA_TOP
		{0, DAC_MAX_VALUE, 0},							// 57	DAC_110MA_NULL
		{0, DAC_MAX_VALUE, DAC_110MA_DEF},				// 58	DAC_110MA_TOP
		{0, 0, 0},																	// 59
		{0, 0, 0},																	// 60
		{0, 0, 0},																	// 61
		{0, 0, 0},																	// 62
		{0, 0, 0},																	// 63
		{0, 0, 0},																	// 64
		{0, 0, 0},																	// 65
		{0, 0, 0},																	// 66
		{0, 0, 0},																	// 67
		{0, 0, 0},																	// 68
		{0, 0, 0},																	// 69
		{0, 0, 0},																	// 70
		{0, 0, 0},																	// 71
		{0, 0, 0},																	// 72
		{0, 0, 0},																	// 73
		{0, 0, 0},																	// 74
		{0, 0, 0},																	// 75
		{0, 0, 0},																	// 76
		{0, 0, 0},																	// 77
		{0, 0, 0},																	// 78
		{0, 0, 0},																	// 79
		{0, 0, 0},																	// 80
		{0, 0, 0},																	// 81
		{0, 0, 0},																	// 82
		{0, 0, 0},																	// 83
		{0, 0, 0},																	// 84
		{0, 0, 0},																	// 85
		{0, 0, 0},																	// 86
		{0, 0, 0},																	// 87
		{0, 0, 0},																	// 88
		{0, 0, 0},																	// 89
		{0, 0, 0},																	// 90
		{0, 0, 0},																	// 91
		{0, 0, 0},																	// 92
		{0, 0, 0},																	// 93
		{0, 0, 0},																	// 94
		{0, 0, 0},																	// 95
		{0, 0, 0},																	// 96
		{0, 0, 0},																	// 97
		{0, 0, 0},																	// 98
		{0, 0, 0},																	// 99
		{0, 0, 0},																	// 100
		{0, 0, 0},																	// 101
		{0, 0, 0},																	// 102
		{0, 0, 0},																	// 103
		{0, 0, 0},																	// 104
		{0, 0, 0},																	// 105
		{0, 0, 0},																	// 106
		{0, 0, 0},																	// 107
		{0, 0, 0},																	// 108
		{0, 0, 0},																	// 109
		{0, 0, 0},																	// 110
		{0, 0, 0},																	// 111
		{0, 0, 0},																	// 112
		{0, 0, 0},																	// 113
		{0, 0, 0},																	// 114
		{0, 0, 0},																	// 115
		{0, 0, 0},																	// 116
		{0, 0, 0},																	// 117
		{0, 0, 0},																	// 118
		{0, 0, 0},																	// 119
		{0, 0, 0},																	// 120
		{0, 0, 0},																	// 121
		{0, 0, 0},																	// 122
		{0, 0, 0},																	// 123
		{0, 0, 0},																	// 124
		{0, 0, 0},																	// 125
		{0, 0, 0},																	// 126
		{0, 0, 0}																	// 127
};
//Min;Max;Default;

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{OUT_LINE_NONE, OUT_LINE_BUS, OUT_LINE_NONE},				// 128	REG_OUTPUT_LINE	// Регистр контроля выходных линий
		{WORK_MODE_OFF, WORK_MODE_CURR, WORK_MODE_OFF},				// 129	REG_WORK_MODE	// Регистр режима работы
		{SRC_TYPE_NONE, SRC_TYPE_PERMANENT, SRC_TYPE_NONE},			// 130	REG_PULSE_TYPE	// Регистр типа формируемого сигнала: импульс, постоянный
		{0, INT16U_MAX, 0},											// 131	REG_PULSE_TIME	// Регистр длительности импульса
		{0, INT16U_MAX, 0},											// 132	REG_I_SET_L		// Регистр установки источника тока LESS HALF
		{0, 1, 0},													// 133	REG_I_SET_M		// Регистр установки источника тока MOST HALF
		{0, 50000, 0},												// 134	REG_V_CUT_L		// Регистр напряжения отсечки в режиме источника тока LESS HALF
		{0, 0, 0},													// 135	REG_V_CUT_M		// Регистр напряжения отсечки в режиме источника тока MOST HALF
		{0, INT16U_MAX, 0},											// 136	REG_V_SET_L		// Регистр установки источника напряжения LESS HALF
		{0, 3, 0},													// 137	REG_V_SET_M		// Регистр установки источника напряжения MOST HALF
		{0, INT16U_MAX, 0},											// 138	REG_I_CUT_L		// Регистр тока отсечки в режиме источника напряжения LESS HALF
		{0, 1, 0},													// 139	REG_I_CUT_M		// Регистр тока отсечки в режиме источника напряжения MOST HALF
		{0, 0, 0},																	// 140
		{0, 0, 0},																	// 141
		{0, 0, 0},																	// 142
		{0, 0, 0},																	// 143
		{0, 0, 0},																	// 144
		{0, 0, 0},																	// 145
		{0, 0, 0},																	// 146
		{0, 0, 0},																	// 147
		{0, MAX_DBG, 16},																	// 148
		{0, 0, 0},																	// 149
		{NO, MAX_DBG, NO},															// 150
		{0, 0, 0},																	// 151
		{0, 0, 0},																	// 152
		{0, 0, 0},																	// 153
		{0, 0, 0},																	// 154
		{0, 0, 0},																	// 155
		{0, 0, 0},																	// 156
		{0, 0, 0},																	// 157
		{0, 0, 0},																	// 158
		{0, 0, 0},																	// 159
		{0, INT16U_MAX, 0},															// 160
		{0, INT16U_MAX, 0},															// 161
		{0, 0, 0},																	// 162
		{0, 0, 0},																	// 163
		{0, 0, 0},																	// 164
		{0, 0, 0},																	// 165
		{0, 0, 0},																	// 166
		{0, 0, 0},																	// 167
		{0, 0, 0},																	// 168
		{0, 0, 0},																	// 169
		{0, 0, 0},																	// 170
		{0, 0, 0},																	// 171
		{0, 0, 0},																	// 172
		{0, 0, 0},																	// 173
		{0, 0, 0},																	// 174
		{0, 0, 0},																	// 175
		{0, 0, 0},																	// 176
		{0, 0, 0},																	// 177
		{0, 0, 0},																	// 178
		{0, 0, 0},																	// 179
		{0, 0, 0},																	// 180
		{0, 0, 0},																	// 181
		{0, 0, 0},																	// 182
		{0, 0, 0},																	// 183
		{0, 0, 0},																	// 184
		{0, 0, 0},																	// 185
		{0, 0, 0},																	// 186
		{0, 0, 0},																	// 187
		{0, 0, 0},																	// 188
		{0, 0, 0},																	// 189
		{0, 0, 0},																	// 190
		{0, 0, 0}																	// 191
};
