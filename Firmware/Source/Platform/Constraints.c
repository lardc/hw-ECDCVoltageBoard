// Header
#include "Constraints.h"

// Constants
const TableItemConstraint NVConstraint[DATA_TABLE_NV_SIZE] = {
		{I_RANGE_MIN, I_RANGE_MAX, I_RANGE_DEF1},									// 0
		{I_RANGE_MIN, I_RANGE_MAX, I_RANGE_DEF2},									// 1
		{I_RANGE_MIN, I_RANGE_MAX, I_RANGE_DEF3},									// 2
		{I_RANGE_MIN, I_RANGE_MAX, I_RANGE_DEF4},									// 3

		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 4
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 5
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 6
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 7

		{1, INT16U_MAX, 1000},														// 8
		{1, INT16U_MAX, 1000},														// 9
		{0, INT16U_MAX, 0},															// 10

		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 11
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 12
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 13
		{I_SHUNT_RES_MIN, I_SHUNT_RES_MAX, I_SHUNT_RES_DEF},						// 14

		{1, INT16U_MAX, 1000},														// 15
		{1, INT16U_MAX, 1000},														// 16
		{0, INT16U_MAX, 0},															// 17

		{ILIM_MARGIN_MIN, ILIM_MARGIN_MAX, ILIM_MARGIN_DEF},						// 18
		{0, 0, 0},																	// 19

		{V_RANGE_MIN, V_RANGE_MAX, V_RANGE_DEF1},									// 20
		{V_RANGE_MIN, V_RANGE_MAX, V_RANGE_DEF2},									// 21
		{V_RANGE_MIN, V_RANGE_MAX, V_RANGE_DEF3},									// 22
		{V_RANGE_MIN, V_RANGE_MAX, V_RANGE_DEF4},									// 23

		{1, INT16U_MAX, 1000},														// 24
		{1, INT16U_MAX, 1000},														// 25
		{0, INT16U_MAX, 0},															// 26

		{1, INT16U_MAX, 1000},														// 27
		{1, INT16U_MAX, 1000},														// 28
		{0, INT16U_MAX, 0},															// 29

		{1, INT16U_MAX, 1000},														// 30
		{1, INT16U_MAX, 1000},														// 31
		{0, INT16U_MAX, 0},															// 32

		{1, INT16U_MAX, 1000},														// 33
		{1, INT16U_MAX, 1000},														// 34
		{0, INT16U_MAX, 0},															// 35

		{0, 0, 0},																	// 36
		{0, 0, 0},																	// 37
		{0, 0, 0},																	// 38
		{0, 0, 0},																	// 39

		{0, INT16U_MAX, 0},															// 40
		{1, INT16U_MAX, 1000},														// 41
		{0, INT16U_MAX, 0},															// 42
		{1, INT16U_MAX, 1000},														// 43
		{1, INT16U_MAX, 1000},														// 44
		{0, INT16U_MAX, 0},															// 45

		{0, INT16U_MAX, 0},															// 46
		{1, INT16U_MAX, 1000},														// 47
		{0, INT16U_MAX, 0},															// 48
		{1, INT16U_MAX, 1000},														// 49
		{1, INT16U_MAX, 1000},														// 50
		{0, INT16U_MAX, 0},															// 51

		{0, INT16U_MAX, 0},															// 52
		{1, INT16U_MAX, 1000},														// 53
		{0, INT16U_MAX, 0},															// 54
		{1, INT16U_MAX, 1000},														// 55
		{1, INT16U_MAX, 1000},														// 56
		{0, INT16U_MAX, 0},															// 57

		{0, INT16U_MAX, 0},															// 58
		{1, INT16U_MAX, 1000},														// 59
		{0, INT16U_MAX, 0},															// 60
		{1, INT16U_MAX, 1000},														// 61
		{1, INT16U_MAX, 1000},														// 62
		{0, INT16U_MAX, 0},															// 63

		{0, INT16U_MAX, 0},															// 64
		{1, INT16U_MAX, 1000},														// 65
		{0, INT16U_MAX, 0},															// 66
		{1, INT16U_MAX, 1000},														// 67
		{1, INT16U_MAX, 1000},														// 68
		{0, INT16U_MAX, 0},															// 69

		{0, INT16U_MAX, 0},															// 70
		{1, INT16U_MAX, 1000},														// 71
		{0, INT16U_MAX, 0},															// 72
		{1, INT16U_MAX, 1000},														// 73
		{1, INT16U_MAX, 1000},														// 74
		{0, INT16U_MAX, 0},															// 75

		{0, INT16U_MAX, 0},															// 76
		{1, INT16U_MAX, 1000},														// 77
		{0, INT16U_MAX, 0},															// 78
		{1, INT16U_MAX, 1000},														// 79
		{1, INT16U_MAX, 1000},														// 80
		{0, INT16U_MAX, 0},															// 81

		{0, INT16U_MAX, 0},															// 82
		{1, INT16U_MAX, 1000},														// 83
		{0, INT16U_MAX, 0},															// 84
		{1, INT16U_MAX, 1000},														// 85
		{1, INT16U_MAX, 1000},														// 86
		{0, INT16U_MAX, 0},															// 87

		{0, INT16U_MAX, 0},															// 88
		{1, INT16U_MAX, 1000},														// 89
		{0, INT16U_MAX, 0},															// 90
		{1, INT16U_MAX, 1000},														// 91
		{1, INT16U_MAX, 1000},														// 92
		{0, INT16U_MAX, 0},															// 93

		{0, INT16U_MAX, 0},															// 94
		{1, INT16U_MAX, 1000},														// 95
		{0, INT16U_MAX, 0},															// 96
		{1, INT16U_MAX, 1000},														// 97
		{1, INT16U_MAX, 1000},														// 98
		{0, INT16U_MAX, 0},															// 99

		{0, INT16U_MAX, 0},															// 100
		{1, INT16U_MAX, 1000},														// 101
		{0, INT16U_MAX, 0},															// 102
		{1, INT16U_MAX, 1000},														// 103
		{1, INT16U_MAX, 1000},														// 104
		{0, INT16U_MAX, 0},															// 105

		{0, INT16U_MAX, 0},															// 106
		{1, INT16U_MAX, 1000},														// 107
		{0, INT16U_MAX, 0},															// 108
		{1, INT16U_MAX, 1000},														// 109
		{1, INT16U_MAX, 1000},														// 110
		{0, INT16U_MAX, 0},															// 111

		{KPI_MIN, KPI_MAX, KPI_DEF},												// 112
		{KPI_MIN, KPI_MAX, KPI_DEF},												// 113
		{RISE_FRONT_MIN, RISE_FRONT_MAX, RISE_FRONT_DEF},							// 114

		{KPI_MIN, KPI_MAX, KPI_DEF},												// 115
		{KPI_MIN, KPI_MAX, KPI_DEF},												// 116
		{RISE_FRONT_MIN, RISE_FRONT_MAX, RISE_FRONT_DEF},							// 117

		{OUTPUT_READY_MIN, OUTPUT_READY_MAX, OUTPUT_READY_DEF},						// 118

		{NO, YES, NO},																// 119
		{FE_COUNTER_MIN, FE_COUNTER_MAX, FE_COUNTER_DEF},							// 120
		{FE_TRIG_LEVEL_MIN, FE_TRIG_LEVEL_MAX, FE_TRIG_LEVEL_DEF},					// 121

		{0, 0, 0},																	// 122
		{0, 0, 0},																	// 123
		{0, 0, 0},																	// 124
		{0, 0, 0},																	// 125
		{0, 0, 0},																	// 126
		{0, 0, 0}																	// 127
};

const TableItemConstraint VConstraint[DATA_TABLE_WP_START - DATA_TABLE_WR_START] = {
		{DC_BUS_LV, PS2, DC_BUS_LV},												// 128
		{OT_Voltage, OT_Current, OT_Voltage},										// 129
		{OM_Pulse, OM_Continuous, OM_Pulse},										// 130
		{PULSE_LENGH_MIN, PULSE_LENGH_MAX, PULSE_LENGH_DEF},						// 131
		{0, 0, 0},																	// 132
		{0, 0, 0},																	// 133
		{0, 0, 0},																	// 134
		{0, INT16U_MAX, 0},															// 135
		{0, INT16U_MAX, 0},															// 136
		{0, INT16U_MAX, 0},															// 137
		{0, INT16U_MAX, 0},															// 138
		{0, 0, 0},																	// 139
		{0, 0, 0},																	// 140
		{0, 0, 0},																	// 141
		{0, 0, 0},																	// 142
		{0, 0, 0},																	// 143
		{0, 0, 0},																	// 144
		{0, 0, 0},																	// 145
		{0, 0, 0},																	// 146
		{0, 0, 0},																	// 147
		{0, 0, 0},																	// 148
		{0, 0, 0},																	// 149
		{0, INT16U_MAX, 0},															// 150
		{0, 0, 0},																	// 151
		{0, 0, 0},																	// 152
		{0, 0, 0},																	// 153
		{0, 0, 0},																	// 154
		{0, 0, 0},																	// 155
		{0, 0, 0},																	// 156
		{0, 0, 0},																	// 157
		{0, 0, 0},																	// 158
		{0, 0, 0},																	// 159
		{0, 0, 0},																	// 160
		{0, 0, 0},																	// 161
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
		{0, INT16U_MAX, 0},															// 190
		{0, 0, 0}																	// 191
};
