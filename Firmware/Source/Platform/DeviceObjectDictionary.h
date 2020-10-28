#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_FAULT_CLEAR					3	// ������� fault
#define ACT_WARNING_CLEAR				4	// ������� warning

#define ACT_DBG_PULSE_SYNC1				50	// ��������� ������� SYNC_1
#define ACT_DBG_PULSE_SYNC2				51	// ��������� ������� SYNC_2

#define ACT_DBG_IS_STATE_SYNC_1			54	// ��������� ���� SYNC_1
#define ACT_DBG_IS_STATE_SYNC_2			55	// ��������� ���� SYNC_2
#define ACT_DBG_PULSE_EXT_LED			56	// ��������� ������� �������� ����������

#define ACT_DBG_RELAY_ON				57	// ��������� ���� [REG_DBG_STATE]  //1..8
#define ACT_DBG_RELAY_OFF				58	// ���������� ���� [REG_DBG_STATE] //1..8

#define ACT_DBG_LHVSELECT_LOW			59	// ����������� �������������� ���������
#define ACT_DBG_LHVSELECT_HIGH			60	// ����������� ��������������� ���������
#define ACT_DBG_CTRL48V_ENABLE			61	// ��������� ��������� 48�
#define ACT_DBG_CTRL48V_DISABLE			62	// ���������� ��������� 48�
#define ACT_DBG_CTRL350V_ENABLE			63	// ��������� ��������� 350�
#define ACT_DBG_CTRL350V_DISABLE		64	// ���������� ��������� 350�
#define ACT_DBG_SELECT_VHV_CTRLS		65	// ����� ��������� ��������� ���������� [REG_DBG_STATE] //1..4
#define ACT_DBG_VSENS_SELECT_SRC		66	// ����� ��������� ��� ��������� ���������� [REG_DBG_STATE] //1:LV_SENS_EN, 2:HV_SENS_EN
#define ACT_DBG_ISENS_SELECT_SRC		67	// ����� ��������� ��� ��������� ���� [REG_DBG_STATE] //1:LV_CUR_SENS_EN, 2:HV_CUR_SENS_EN

#define ACT_DBG_SELECT_LV_CTRLS			70	// ����� �����
#define ACT_DBG_SELECT_HV_CTRLS			71	// ����� ��������� ... ����������
#define ACT_DBG_READ_ADC_ICH			72	// ��������� ����
#define ACT_DBG_READ_ADC_VCH			73	// ��������� ����������
#define ACT_DBG_WRITE_DAC_LV_VOLTAGE	74	// ������ � ������������� ��� ����������
#define ACT_DBG_WRITE_DAC_LV_CURRENT	75	// ������ � ������������� ��� ����
#define ACT_DBG_WRITE_DAC_HV_VOLTAGE	76	// ������ � �������������� ��� ����������
#define ACT_DBG_WRITE_DAC_HV_CURRENT	77	// ������ � �������������� ��� ����

#define ACT_START_PROCESS				100	// ������ �������� ������������ ��������
#define ACT_STOP_PROCESS				101	// ��������� �������� ������������ ��������

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������
#define REG_I_RANGE1_LIMIT				0	// ������� ������ ��������� ���� 1 (� ���)
#define REG_I_RANGE2_LIMIT				1	// ������� ������ ��������� ���� 2 (� ���)
#define REG_I_RANGE3_LIMIT				2	// ������� ������ ��������� ���� 3 (� ���)
#define REG_I_RANGE4_LIMIT				3	// ������� ������ ��������� ���� 4 (� ��)

#define REG_I_RANGE1_RES				4	// ������������� �������� ���������� ��������� 1 �������������� ��������� (� ����)
#define REG_I_RANGE2_RES				5	// ������������� �������� ���������� ��������� 2 �������������� ��������� (� ����)
#define REG_I_RANGE3_RES				6	// ������������� �������� ���������� ��������� 3 �������������� ��������� (� ����)
#define REG_I_RANGE4_RES				7	// ������������� �������� ���������� ��������� 4 �������������� ��������� (� ����)

#define REG_DAC_I_CONV_K_N				8	// ����������� ��������� ���� � ��� �������������� ���������, ���������
#define REG_DAC_I_CONV_K_D				9	// ����������� ��������� ���� � ��� �������������� ���������, �����������
#define REG_DAC_I_OFFSET				10	// ������ ��������� ���� � ��� �������������� ��������� (� �� ������ �A�)

#define REG_HV_I_RANGE1_RES				11	// ������������� �������� ���������� ��������� 1 ��������������� ��������� (� ����)
#define REG_HV_I_RANGE2_RES				12	// ������������� �������� ���������� ��������� 2 ��������������� ��������� (� ����)
#define REG_HV_I_RANGE3_RES				13	// ������������� �������� ���������� ��������� 3 ��������������� ��������� (� ����)
#define REG_HV_I_RANGE4_RES				14	// ������������� �������� ���������� ��������� 4 ��������������� ��������� (� ����)

#define REG_DAC_HV_I_CONV_K_N			15	// ����������� ��������� ���� � ��� ��������������� ���������, ���������
#define REG_DAC_HV_I_CONV_K_D			16	// ����������� ��������� ���� � ��� ��������������� ���������, �����������
#define REG_DAC_HV_I_OFFSET				17	// ������ ��������� ���� � ��� ��������������� ��������� (� �� ������ �A�)

#define REG_CURRENT_LIMIT_MARGIN		18	// ����� ����������� ����������� ���� (� %)

// 19

#define REG_V_RANGE1_LIMIT				20	// ������� ������ ��������� 1 (� ��)
#define REG_V_RANGE2_LIMIT				21	// ������� ������ ��������� 2 (� ��)
#define REG_V_RANGE3_LIMIT				22	// ������� ������ ��������� 3 (� ��)
#define REG_V_RANGE4_LIMIT				23	// ������� ������ ��������� 4 (� �)

#define REG_DAC_V1_CONV_K_N				24	// ����������� ��������� ���������� � ��� ��������� 1, ���������
#define REG_DAC_V1_CONV_K_D				25	// ����������� ��������� ���������� � ��� ��������� 1, �����������
#define REG_DAC_V1_OFFSET				26	// ������ ��������� ���������� � ��� ��������� 1 (� �� ������ �A�)

#define REG_DAC_V2_CONV_K_N				27	// ����������� ��������� ���������� � ��� ��������� 2, ���������
#define REG_DAC_V2_CONV_K_D				28	// ����������� ��������� ���������� � ��� ��������� 2, �����������
#define REG_DAC_V2_OFFSET				29	// ������ ��������� ���������� � ��� ��������� 2 (� �� ������ �A�)

#define REG_DAC_V3_CONV_K_N				30	// ����������� ��������� ���������� � ��� ��������� 3, ���������
#define REG_DAC_V3_CONV_K_D				31	// ����������� ��������� ���������� � ��� ��������� 3, �����������
#define REG_DAC_V3_OFFSET				32	// ������ ��������� ���������� � ��� ��������� 3 (� �� ������ �A�)

#define REG_DAC_V4_CONV_K_N				33	// ����������� ��������� ���������� � ��� ��������� 4, ���������
#define REG_DAC_V4_CONV_K_D				34	// ����������� ��������� ���������� � ��� ��������� 4, �����������
#define REG_DAC_V4_OFFSET				35	// ������ ��������� ���������� � ��� ��������� 4 (� �� ������ �A�)

// 36 - 39

#define REG_ADC_I1_FINE_P2				40	// ����������� ������ ���������� ��������� ���� ��������� 1 P2 x1e6
#define REG_ADC_I1_FINE_P1				41  // ����������� ������ ���������� ��������� ���� ��������� 1 P1 x1000
#define REG_ADC_I1_FINE_P0				42	// ����������� ������ ���������� ��������� ���� ��������� 1 P0
#define REG_ADC_I1_CONV_K_N				43	// ����������� ��������� ��������� ���� ��������� 1, ���������
#define REG_ADC_I1_CONV_K_D				44	// ����������� ��������� ��������� ���� ��������� 1, �����������
#define REG_ADC_I1_CONV_OFFSET			45	// ������ ��������� ���� ��������� 1 (� �� ����� ���)

#define REG_ADC_I2_FINE_P2				46	// ����������� ������ ���������� ��������� ���� ��������� 2 P2 x1e6
#define REG_ADC_I2_FINE_P1				47  // ����������� ������ ���������� ��������� ���� ��������� 2 P1 x1000
#define REG_ADC_I2_FINE_P0				48	// ����������� ������ ���������� ��������� ���� ��������� 2 P0
#define REG_ADC_I2_CONV_K_N				49	// ����������� ��������� ��������� ���� ��������� 2, ���������
#define REG_ADC_I2_CONV_K_D				50	// ����������� ��������� ��������� ���� ��������� 2, �����������
#define REG_ADC_I2_CONV_OFFSET			51	// ������ ��������� ���� ��������� 2 (� �� ����� ���)

#define REG_ADC_I3_FINE_P2				52	// ����������� ������ ���������� ��������� ���� ��������� 3 P2 x1e6
#define REG_ADC_I3_FINE_P1				53  // ����������� ������ ���������� ��������� ���� ��������� 3 P1 x1000
#define REG_ADC_I3_FINE_P0				54	// ����������� ������ ���������� ��������� ���� ��������� 3 P0
#define REG_ADC_I3_CONV_K_N				55	// ����������� ��������� ��������� ���� ��������� 3, ���������
#define REG_ADC_I3_CONV_K_D				56	// ����������� ��������� ��������� ���� ��������� 3, �����������
#define REG_ADC_I3_CONV_OFFSET			57	// ������ ��������� ���� ��������� 3 (� �� ����� ���)

#define REG_ADC_I4_FINE_P2				58	// ����������� ������ ���������� ��������� ���� ��������� 4 P2 x1e6
#define REG_ADC_I4_FINE_P1				59  // ����������� ������ ���������� ��������� ���� ��������� 4 P1 x1000
#define REG_ADC_I4_FINE_P0				60	// ����������� ������ ���������� ��������� ���� ��������� 4 P0
#define REG_ADC_I4_CONV_K_N				61	// ����������� ��������� ��������� ���� ��������� 4, ���������
#define REG_ADC_I4_CONV_K_D				62	// ����������� ��������� ��������� ���� ��������� 4, �����������
#define REG_ADC_I4_CONV_OFFSET			63	// ������ ��������� ���� ��������� 4 (� �� ����� ���)

#define REG_ADC_V1_FINE_P2				64	// ����������� ������ ���������� ��������� ���������� ��������� 1 P2 x1e6
#define REG_ADC_V1_FINE_P1				65  // ����������� ������ ���������� ��������� ���������� ��������� 1 P1 x1000
#define REG_ADC_V1_FINE_P0				66	// ����������� ������ ���������� ��������� ���������� ��������� 1 P0
#define REG_ADC_V1_CONV_K_N				67	// ����������� ��������� ��������� ���������� ��������� 1, ���������
#define REG_ADC_V1_CONV_K_D				68	// ����������� ��������� ��������� ���������� ��������� 1, �����������
#define REG_ADC_V1_CONV_OFFSET			69	// ������ ��������� ���������� ��������� 1 (� �� ����� ���)

#define REG_ADC_V2_FINE_P2				70	// ����������� ������ ���������� ��������� ���������� ��������� 2 P2 x1e6
#define REG_ADC_V2_FINE_P1				71  // ����������� ������ ���������� ��������� ���������� ��������� 2 P1 x1000
#define REG_ADC_V2_FINE_P0				72	// ����������� ������ ���������� ��������� ���������� ��������� 2 P0
#define REG_ADC_V2_CONV_K_N				73	// ����������� ��������� ��������� ���������� ��������� 2, ���������
#define REG_ADC_V2_CONV_K_D				74	// ����������� ��������� ��������� ���������� ��������� 2, �����������
#define REG_ADC_V2_CONV_OFFSET			75	// ������ ��������� ���������� ��������� 2 (� �� ����� ���)

#define REG_ADC_V3_FINE_P2				76	// ����������� ������ ���������� ��������� ���������� ��������� 3 P2 x1e6
#define REG_ADC_V3_FINE_P1				77  // ����������� ������ ���������� ��������� ���������� ��������� 3 P1 x1000
#define REG_ADC_V3_FINE_P0				78	// ����������� ������ ���������� ��������� ���������� ��������� 3 P0
#define REG_ADC_V3_CONV_K_N				79	// ����������� ��������� ��������� ���������� ��������� 3, ���������
#define REG_ADC_V3_CONV_K_D				80	// ����������� ��������� ��������� ���������� ��������� 3, �����������
#define REG_ADC_V3_CONV_OFFSET			81	// ������ ��������� ���������� ��������� 3 (� �� ����� ���)

#define REG_ADC_V4_FINE_P2				82	// ����������� ������ ���������� ��������� ���������� ��������� 4 P2 x1e6
#define REG_ADC_V4_FINE_P1				83  // ����������� ������ ���������� ��������� ���������� ��������� 4 P1 x1000
#define REG_ADC_V4_FINE_P0				84	// ����������� ������ ���������� ��������� ���������� ��������� 4 P0
#define REG_ADC_V4_CONV_K_N				85	// ����������� ��������� ��������� ���������� ��������� 4, ���������
#define REG_ADC_V4_CONV_K_D				86	// ����������� ��������� ��������� ���������� ��������� 4, �����������
#define REG_ADC_V4_CONV_OFFSET			87	// ������ ��������� ���������� ��������� 4 (� �� ����� ���)

#define REG_ADC_HV_I1_FINE_P2			88	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 1 P2 x1e6
#define REG_ADC_HV_I1_FINE_P1			89  // ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 1 P1 x1000
#define REG_ADC_HV_I1_FINE_P0			90	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 1 P0
#define REG_ADC_HV_I1_CONV_K_N			91	// ����������� ��������� ��������� ���� �������� ���������� ��������� 1, ���������
#define REG_ADC_HV_I1_CONV_K_D			92	// ����������� ��������� ��������� ���� �������� ���������� ��������� 1, �����������
#define REG_ADC_HV_I1_CONV_OFFSET		93	// ������ ��������� ���� �������� ���������� ��������� 1 (� �� ����� ���)

#define REG_ADC_HV_I2_FINE_P2			94	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 2 P2 x1e6
#define REG_ADC_HV_I2_FINE_P1			95  // ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 2 P1 x1000
#define REG_ADC_HV_I2_FINE_P0			96	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 2 P0
#define REG_ADC_HV_I2_CONV_K_N			97	// ����������� ��������� ��������� ���� �������� ���������� ��������� 2, ���������
#define REG_ADC_HV_I2_CONV_K_D			98	// ����������� ��������� ��������� ���� �������� ���������� ��������� 2, �����������
#define REG_ADC_HV_I2_CONV_OFFSET		99	// ������ ��������� ���� �������� ���������� ��������� 2 (� �� ����� ���)

#define REG_ADC_HV_I3_FINE_P2			100	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 3 P2 x1e6
#define REG_ADC_HV_I3_FINE_P1			101 // ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 3 P1 x1000
#define REG_ADC_HV_I3_FINE_P0			102	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 3 P0
#define REG_ADC_HV_I3_CONV_K_N			103	// ����������� ��������� ��������� ���� �������� ���������� ��������� 3, ���������
#define REG_ADC_HV_I3_CONV_K_D			104	// ����������� ��������� ��������� ���� �������� ���������� ��������� 3, �����������
#define REG_ADC_HV_I3_CONV_OFFSET		105	// ������ ��������� ���� �������� ���������� ��������� 3 (� �� ����� ���)

#define REG_ADC_HV_I4_FINE_P2			106	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 4 P2 x1e6
#define REG_ADC_HV_I4_FINE_P1			107	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 4 P1 x1000
#define REG_ADC_HV_I4_FINE_P0			108	// ����������� ������ ���������� ��������� ���� �������� ���������� ��������� 4 P0
#define REG_ADC_HV_I4_CONV_K_N			109	// ����������� ��������� ��������� ���� �������� ���������� ��������� 4, ���������
#define REG_ADC_HV_I4_CONV_K_D			110	// ����������� ��������� ��������� ���� �������� ���������� ��������� 4, �����������
#define REG_ADC_HV_I4_CONV_OFFSET		111	// ������ ��������� ���� �������� ���������� ��������� 4 (� �� ����� ���)

#define REG_VOLTAGE_KP					112	// ���������������� ����������� ���������� ����������
#define REG_VOLTAGE_KI					113	// ������������ ����������� ���������� ����������
#define REG_VOLTAGE_RISE_RATE			114	// �������� ���������� ���������� (�� / ��)

#define REG_CURRENT_KP					115	// ���������������� ����������� ���������� ����
#define REG_CURRENT_KI					116	// ������������ ����������� ���������� ����
#define REG_CURRENT_RISE_RATE			117	// �������� ���������� ���� (�� / ��)

#define REG_OUTPUT_READY_THR			118	// ���������� ����������� ���������� ��������� ������� (� %)

#define REG_ENABLE_FE					119	// ���������� ����������� FollowingError
#define REG_FE_COUNTER_MAX				120	// ������������ �������� �������� ����������� FollowingError
#define REG_FE_TRIG_LEVEL				121	// ������� ������������ FollowingError

// 122 - 127

// ������������� �������� ������-������
#define DCV_REG_OUTPUT_LINE				128	// ����� ������ ��������� ����������
#define DCV_REG_OUTPUT_TYPE				129	// ��� ������
#define DCV_REG_OUTPUT_MODE				130	// ����� ������
#define DCV_REG_PULSE_LENGTH			131	// ������������ ��������� ��������

#define DCV_REG_CURRENT_SETPOINT		135	// �������� ������� ���� (� ���)
#define DCV_REG_CURRENT_SETPOINT_32		136
#define DCV_REG_VOLTAGE_SETPOINT		137	// �������� ������� ���������� (� ��)
#define DCV_REG_VOLTAGE_SETPOINT_32		138

#define REG_SCOPE_RATE					150	// ����������� ������� ������� ��������� ����������� ������

#define REG_DEBUG						190	// ������� ������ �������

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������
#define REG_SUB_STATE					198	// ������� ���������������� ���������

#define REG_CURRENT_RESULT				200	// �������� ��������� ���� (� ���)
#define REG_CURRENT_RESULT_32			201
#define REG_VOLTAGE_RESULT				202	// �������� ��������� ���������� (� ��)
#define REG_VOLTAGE_RESULT_32			203

#define REG_VOLTAGE_READY				205	// ���� ������ �� ������� ����������

#define REG_EP_LAST_POINTER				250	// ��������� �� �������� ������� �������� ������������

#define REG_DBG_SYNC1					251	// ������� ��������� ����������� ����� SYNC1
#define REG_DBG_SYNC2					252	// ������� ��������� ����������� ����� SYNC2

#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record

// -----------------------------

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

// EPs
#define EP_I_MEASURE					1	// ��������� ����
#define EP_V_MEASURE					2	// ��������� ����������
#define EP_SETPOINT						3	// �������
#define EP_CONTROL						4	// ����� ����������
#define EP_RAW_CONTROL					5	// ����� ����� ����������

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0
#define PROBLEM_FOLLOWING_ERROR			1	// ������ �������������
#define PROBLEM_VI_LIMIT				2	// ���������� �������������� ������ �� ���� ��� ����������
#define PROBLEM_FORCED_STOP				3	// �������������� ��������� � ������������ ������������

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����
#define ERR_BAD_CONFIG					5	//  ������� ������� ��������� � �������� �������������

#endif //  __DEV_OBJ_DIC_H
