#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

//TODO check define [1..4]
// �������
#define ACT_ENABLE_POWER				1	// ������� � ��������� ��������
#define ACT_DISABLE_POWER				2	// ���������� �����
#define ACT_FAULT_CLEAR					3	// ������� fault
#define ACT_WARNING_CLEAR				4	// ������� warning

#define ACT_START_PROCESS				100	// ������ �������� ������������ ��������
#define ACT_STOP_PROCESS				101	// ��������� �������� ������������ ��������

//debug commands
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
#define ACT_DBG_SELECT_DAC				68	// ����� �������� ��������� ����/���������� [REG_DBG_STATE]
#define ACT_DBG_WRITE_DAC				69	// ������ ���������� � �������� ����/���������� [REG_DBG_STATE]

#define ACT_DBG_SELECT_LV_CTRLS			70	// ����� ��������� ... ����������
#define ACT_DBG_SELECT_HV_CTRLS			71	// ����� ��������� ... ����������
#define ACT_DBG_READ_ADC_ICH			72	// ��������� ����
#define ACT_DBG_READ_ADC_VCH			73	// ��������� ����������

//TODO add more ACT_DBG !!!

#define ACT_SAVE_TO_ROM					200	// ���������� ���������������� ������ �� FLASH ����������
#define ACT_RESTORE_FROM_ROM			201	// �������������� ������ �� FLASH
#define ACT_RESET_TO_DEFAULT			202	// ����� DataTable � ��������� �� ���������

#define ACT_BOOT_LOADER_REQUEST			320	// ���������� ���������� � ����� ��������������������
// -----------------------------

// ��������
// ����������� ��������

// ������������ �������� ������-������
#define REG_DBG_STATE					150	// ������� ������ �������

// �������� ������ ������
#define REG_DEV_STATE					192	// ������� ���������
#define REG_FAULT_REASON				193	// ������� Fault
#define REG_DISABLE_REASON				194	// ������� Disable
#define REG_WARNING						195	// ������� Warning
#define REG_PROBLEM						196	// ������� Problem
#define REG_OP_RESULT					197	// ������� ���������� ��������

#define REG_DBG_SYNC1				251	// ������� ��������� ����������� ����� SYNC1
#define REG_DBG_SYNC2				252	// ������� ��������� ����������� ����� SYNC2

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

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  ���������� �������� �� ������
#define ERR_OPERATION_BLOCKED			2	//  �������� �� ����� ���� ��������� � ������� ��������� ����������
#define ERR_DEVICE_NOT_READY			3	//  ���������� �� ������ ��� ����� ���������
#define ERR_WRONG_PWD					4	//  ������������ ����

#endif //  __DEV_OBJ_DIC_H
