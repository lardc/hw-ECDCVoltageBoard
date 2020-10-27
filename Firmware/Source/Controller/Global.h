#ifndef __GLOBAL_H
#define __GLOBAL_H

// Includes
#include "SysConfig.h"

// Definitions
// 
#define	SCCI_TIMEOUT_TICKS			1000	// ������� ���������� SCCI (� ��)
#define EP_WRITE_COUNT				0		// ���������� �������� ��� ������
#define EP_COUNT					5		// ���������� �������� ��� ������
#define ENABLE_LOCKING				FALSE	// ������ NV ��������� �������
#define EP_SIZE						1000	// ������ ������� ������������

// ��������� ���������
//
#define TIME_LED_BLINK				500		// ������� ����������� (� ��)
#define TIME_DBG_PULSE				1000	// ������������ ����������� �������� (� ��)
#define TIME_TRANSIENT_DELAY		100		// �������� ���������� � ���������� ��������� (� ��)

// ��������� ������
#define VB_VOUT_MIN					40			// � ��
#define VB_VOUT_MAX					270000		// � ��
#define VB_IOUT_MIN					8			// � ���
#define VB_IOUT_MAX					110000		// � ���

// ��������� ���, ���
#define DAC_MAX_RESOLUTION			0xFFF
#define DAC_REF_VOLTAGE				5000		// � ��

#define ADC_MAX_RESOLUTION			0xFFF
#define ADC_REF_VOLTAGE				3000		// � ��

#define ADC_AVG_COUNT				4

// ��������� ����������
#define REGLTR_ERROR_I_SAT_H		10000
#define REGLTR_PERIOD				TIMER2_uS

#endif //  __GLOBAL_H
