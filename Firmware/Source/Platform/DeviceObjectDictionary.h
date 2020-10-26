#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning

#define ACT_START_PROCESS				100	// Страрт процесса формирования импульса
#define ACT_STOP_PROCESS				101	// Остановка процесса формирования импульса

//debug commands
#define ACT_DBG_PULSE_SYNC1				50	// Одиночный импульс SYNC_1
#define ACT_DBG_PULSE_SYNC2				51	// Одиночный импульс SYNC_2

#define ACT_DBG_IS_STATE_SYNC_1			54	// Состояние цепи SYNC_1
#define ACT_DBG_IS_STATE_SYNC_2			55	// Состояние цепи SYNC_2
#define ACT_DBG_PULSE_EXT_LED			56	// Одиночный импусль внешнего светодиода

#define ACT_DBG_RELAY_ON				57	// Включение реле [REG_DBG_STATE]  //1..8
#define ACT_DBG_RELAY_OFF				58	// Выключение реле [REG_DBG_STATE] //1..8

#define ACT_DBG_LHVSELECT_LOW			59	// Подключение низковольтного источника
#define ACT_DBG_LHVSELECT_HIGH			60	// Подключение высоковольтного источника
#define ACT_DBG_CTRL48V_ENABLE			61	// Включение источника 48В
#define ACT_DBG_CTRL48V_DISABLE			62	// Выключение источника 48В
#define ACT_DBG_CTRL350V_ENABLE			63	// Включение источника 350В
#define ACT_DBG_CTRL350V_DISABLE		64	// Выключение источника 350В
#define ACT_DBG_SELECT_VHV_CTRLS		65	// Выбор диапазона измерения напряжения [REG_DBG_STATE] //1..4
#define ACT_DBG_VSENS_SELECT_SRC		66	// Выбор источника для измерения напряжения [REG_DBG_STATE] //1:LV_SENS_EN, 2:HV_SENS_EN
#define ACT_DBG_ISENS_SELECT_SRC		67	// Выбор источника для измерения тока [REG_DBG_STATE] //1:LV_CUR_SENS_EN, 2:HV_CUR_SENS_EN

#define ACT_DBG_SELECT_LV_CTRLS			70	// Выбор шунта
#define ACT_DBG_SELECT_HV_CTRLS			71	// Выбор диапазона ... напряжения
#define ACT_DBG_READ_ADC_ICH			72	// Измерение тока
#define ACT_DBG_READ_ADC_VCH			73	// Измерение напряжения

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры
#define REG_I_RANGE1_LIMIT				0	// Верхний предел диапазона тока 1 (в мкА)
#define REG_I_RANGE2_LIMIT				1	// Верхний предел диапазона тока 2 (в мкА)
#define REG_I_RANGE3_LIMIT				2	// Верхний предел диапазона тока 3 (в мкА)
#define REG_I_RANGE4_LIMIT				3	// Верхний предел диапазона тока 4 (в мА)

#define REG_I_RANGE1_RES				4	// Сопротивление шунтовых резисторов диапазона 1 низковольтного источника (в Омах)
#define REG_I_RANGE2_RES				5	// Сопротивление шунтовых резисторов диапазона 2 низковольтного источника (в Омах)
#define REG_I_RANGE3_RES				6	// Сопротивление шунтовых резисторов диапазона 3 низковольтного источника (в Омах)
#define REG_I_RANGE4_RES				7	// Сопротивление шунтовых резисторов диапазона 4 низковольтного источника (в Омах)

#define REG_DAC_I_CONV_K_N				8	// Коэффициент пересчёта тока в ЦАП низковольтного источника, числитель
#define REG_DAC_I_CONV_K_D				9	// Коэффициент пересчёта тока в ЦАП низковольтного источника, знаменатель
#define REG_DAC_I_OFFSET				10	// Оффсет пересчёта тока в ЦАП низковольтного источника (в мВ выхода ЦAП)

#define REG_HV_I_RANGE1_RES				11	// Сопротивление шунтовых резисторов диапазона 1 высоковольтного источника (в Омах)
#define REG_HV_I_RANGE2_RES				12	// Сопротивление шунтовых резисторов диапазона 2 высоковольтного источника (в Омах)
#define REG_HV_I_RANGE3_RES				13	// Сопротивление шунтовых резисторов диапазона 3 высоковольтного источника (в Омах)
#define REG_HV_I_RANGE4_RES				14	// Сопротивление шунтовых резисторов диапазона 4 высоковольтного источника (в Омах)

#define REG_DAC_HV_I_CONV_K_N			15	// Коэффициент пересчёта тока в ЦАП высоковольтного источника, числитель
#define REG_DAC_HV_I_CONV_K_D			16	// Коэффициент пересчёта тока в ЦАП высоковольтного источника, знаменатель
#define REG_DAC_HV_I_OFFSET				17	// Оффсет пересчёта тока в ЦАП высоковольтного источника (в мВ выхода ЦAП)

#define REG_CURRENT_LIMIT_MARGIN		18	// Запас аппаратного ограничения тока (в %)

// 19

#define REG_V_RANGE1_LIMIT				20	// Верхний предел диапазона 1 (в мВ)
#define REG_V_RANGE2_LIMIT				21	// Верхний предел диапазона 2 (в мВ)
#define REG_V_RANGE3_LIMIT				22	// Верхний предел диапазона 3 (в мВ)
#define REG_V_RANGE4_LIMIT				23	// Верхний предел диапазона 4 (в В)

#define REG_DAC_V1_CONV_K_N				24	// Коэффициент пересчёта напряжения в ЦАП диапазона 1, числитель
#define REG_DAC_V1_CONV_K_D				25	// Коэффициент пересчёта напряжения в ЦАП диапазона 1, знаменатель
#define REG_DAC_V1_OFFSET				26	// Оффсет пересчёта напряжения в ЦАП диапазона 1 (в мВ выхода ЦAП)

#define REG_DAC_V2_CONV_K_N				27	// Коэффициент пересчёта напряжения в ЦАП диапазона 2, числитель
#define REG_DAC_V2_CONV_K_D				28	// Коэффициент пересчёта напряжения в ЦАП диапазона 2, знаменатель
#define REG_DAC_V2_OFFSET				29	// Оффсет пересчёта напряжения в ЦАП диапазона 2 (в мВ выхода ЦAП)

#define REG_DAC_V3_CONV_K_N				30	// Коэффициент пересчёта напряжения в ЦАП диапазона 3, числитель
#define REG_DAC_V3_CONV_K_D				31	// Коэффициент пересчёта напряжения в ЦАП диапазона 3, знаменатель
#define REG_DAC_V3_OFFSET				32	// Оффсет пересчёта напряжения в ЦАП диапазона 3 (в мВ выхода ЦAП)

#define REG_DAC_V4_CONV_K_N				33	// Коэффициент пересчёта напряжения в ЦАП диапазона 4, числитель
#define REG_DAC_V4_CONV_K_D				34	// Коэффициент пересчёта напряжения в ЦАП диапазона 4, знаменатель
#define REG_DAC_V4_OFFSET				35	// Оффсет пересчёта напряжения в ЦАП диапазона 4 (в мВ выхода ЦAП)

// 36 - 39

#define REG_ADC_I1_FINE_P2				40	// Коэффициент тонкой подстройки оцифровки тока диапазона 1 P2 x1e6
#define REG_ADC_I1_FINE_P1				41  // Коэффициент тонкой подстройки оцифровки тока диапазона 1 P1 x1000
#define REG_ADC_I1_FINE_P0				42	// Коэффициент тонкой подстройки оцифровки тока диапазона 1 P0
#define REG_ADC_I1_CONV_K_N				43	// Коэффициент пересчёта оцифровки тока диапазона 1, числитель
#define REG_ADC_I1_CONV_K_D				44	// Коэффициент пересчёта оцифровки тока диапазона 1, знаменатель
#define REG_ADC_I1_CONV_OFFSET			45	// Оффсет оцифровки тока диапазона 1 (в мВ входа АЦП)

#define REG_ADC_I2_FINE_P2				46	// Коэффициент тонкой подстройки оцифровки тока диапазона 2 P2 x1e6
#define REG_ADC_I2_FINE_P1				47  // Коэффициент тонкой подстройки оцифровки тока диапазона 2 P1 x1000
#define REG_ADC_I2_FINE_P0				48	// Коэффициент тонкой подстройки оцифровки тока диапазона 2 P0
#define REG_ADC_I2_CONV_K_N				49	// Коэффициент пересчёта оцифровки тока диапазона 2, числитель
#define REG_ADC_I2_CONV_K_D				50	// Коэффициент пересчёта оцифровки тока диапазона 2, знаменатель
#define REG_ADC_I2_CONV_OFFSET			51	// Оффсет оцифровки тока диапазона 2 (в мВ входа АЦП)

#define REG_ADC_I3_FINE_P2				52	// Коэффициент тонкой подстройки оцифровки тока диапазона 3 P2 x1e6
#define REG_ADC_I3_FINE_P1				53  // Коэффициент тонкой подстройки оцифровки тока диапазона 3 P1 x1000
#define REG_ADC_I3_FINE_P0				54	// Коэффициент тонкой подстройки оцифровки тока диапазона 3 P0
#define REG_ADC_I3_CONV_K_N				55	// Коэффициент пересчёта оцифровки тока диапазона 3, числитель
#define REG_ADC_I3_CONV_K_D				56	// Коэффициент пересчёта оцифровки тока диапазона 3, знаменатель
#define REG_ADC_I3_CONV_OFFSET			57	// Оффсет оцифровки тока диапазона 3 (в мВ входа АЦП)

#define REG_ADC_I4_FINE_P2				58	// Коэффициент тонкой подстройки оцифровки тока диапазона 4 P2 x1e6
#define REG_ADC_I4_FINE_P1				59  // Коэффициент тонкой подстройки оцифровки тока диапазона 4 P1 x1000
#define REG_ADC_I4_FINE_P0				60	// Коэффициент тонкой подстройки оцифровки тока диапазона 4 P0
#define REG_ADC_I4_CONV_K_N				61	// Коэффициент пересчёта оцифровки тока диапазона 4, числитель
#define REG_ADC_I4_CONV_K_D				62	// Коэффициент пересчёта оцифровки тока диапазона 4, знаменатель
#define REG_ADC_I4_CONV_OFFSET			63	// Оффсет оцифровки тока диапазона 4 (в мВ входа АЦП)

#define REG_ADC_V1_FINE_P2				64	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 1 P2 x1e6
#define REG_ADC_V1_FINE_P1				65  // Коэффициент тонкой подстройки оцифровки напряжения диапазона 1 P1 x1000
#define REG_ADC_V1_FINE_P0				66	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 1 P0
#define REG_ADC_V1_CONV_K_N				67	// Коэффициент пересчёта оцифровки напряжения диапазона 1, числитель
#define REG_ADC_V1_CONV_K_D				68	// Коэффициент пересчёта оцифровки напряжения диапазона 1, знаменатель
#define REG_ADC_V1_CONV_OFFSET			69	// Оффсет оцифровки напряжения диапазона 1 (в мВ входа АЦП)

#define REG_ADC_V2_FINE_P2				70	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 2 P2 x1e6
#define REG_ADC_V2_FINE_P1				71  // Коэффициент тонкой подстройки оцифровки напряжения диапазона 2 P1 x1000
#define REG_ADC_V2_FINE_P0				72	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 2 P0
#define REG_ADC_V2_CONV_K_N				73	// Коэффициент пересчёта оцифровки напряжения диапазона 2, числитель
#define REG_ADC_V2_CONV_K_D				74	// Коэффициент пересчёта оцифровки напряжения диапазона 2, знаменатель
#define REG_ADC_V2_CONV_OFFSET			75	// Оффсет оцифровки напряжения диапазона 2 (в мВ входа АЦП)

#define REG_ADC_V3_FINE_P2				76	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 3 P2 x1e6
#define REG_ADC_V3_FINE_P1				77  // Коэффициент тонкой подстройки оцифровки напряжения диапазона 3 P1 x1000
#define REG_ADC_V3_FINE_P0				78	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 3 P0
#define REG_ADC_V3_CONV_K_N				79	// Коэффициент пересчёта оцифровки напряжения диапазона 3, числитель
#define REG_ADC_V3_CONV_K_D				80	// Коэффициент пересчёта оцифровки напряжения диапазона 3, знаменатель
#define REG_ADC_V3_CONV_OFFSET			81	// Оффсет оцифровки напряжения диапазона 3 (в мВ входа АЦП)

#define REG_ADC_V4_FINE_P2				82	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 4 P2 x1e6
#define REG_ADC_V4_FINE_P1				83  // Коэффициент тонкой подстройки оцифровки напряжения диапазона 4 P1 x1000
#define REG_ADC_V4_FINE_P0				84	// Коэффициент тонкой подстройки оцифровки напряжения диапазона 4 P0
#define REG_ADC_V4_CONV_K_N				85	// Коэффициент пересчёта оцифровки напряжения диапазона 4, числитель
#define REG_ADC_V4_CONV_K_D				86	// Коэффициент пересчёта оцифровки напряжения диапазона 4, знаменатель
#define REG_ADC_V4_CONV_OFFSET			87	// Оффсет оцифровки напряжения диапазона 4 (в мВ входа АЦП)

#define REG_ADC_HV_I1_FINE_P2			88	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 1 P2 x1e6
#define REG_ADC_HV_I1_FINE_P1			89  // Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 1 P1 x1000
#define REG_ADC_HV_I1_FINE_P0			90	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 1 P0
#define REG_ADC_HV_I1_CONV_K_N			91	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 1, числитель
#define REG_ADC_HV_I1_CONV_K_D			92	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 1, знаменатель
#define REG_ADC_HV_I1_CONV_OFFSET		93	// Оффсет оцифровки тока высокого напряжения диапазона 1 (в мВ входа АЦП)

#define REG_ADC_HV_I2_FINE_P2			94	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 2 P2 x1e6
#define REG_ADC_HV_I2_FINE_P1			95  // Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 2 P1 x1000
#define REG_ADC_HV_I2_FINE_P0			96	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 2 P0
#define REG_ADC_HV_I2_CONV_K_N			97	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 2, числитель
#define REG_ADC_HV_I2_CONV_K_D			98	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 2, знаменатель
#define REG_ADC_HV_I2_CONV_OFFSET		99	// Оффсет оцифровки тока высокого напряжения диапазона 2 (в мВ входа АЦП)

#define REG_ADC_HV_I3_FINE_P2			100	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 3 P2 x1e6
#define REG_ADC_HV_I3_FINE_P1			101 // Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 3 P1 x1000
#define REG_ADC_HV_I3_FINE_P0			102	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 3 P0
#define REG_ADC_HV_I3_CONV_K_N			103	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 3, числитель
#define REG_ADC_HV_I3_CONV_K_D			104	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 3, знаменатель
#define REG_ADC_HV_I3_CONV_OFFSET		105	// Оффсет оцифровки тока высокого напряжения диапазона 3 (в мВ входа АЦП)

#define REG_ADC_HV_I4_FINE_P2			106	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 4 P2 x1e6
#define REG_ADC_HV_I4_FINE_P1			107	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 4 P1 x1000
#define REG_ADC_HV_I4_FINE_P0			108	// Коэффициент тонкой подстройки оцифровки тока высокого напряжения диапазона 4 P0
#define REG_ADC_HV_I4_CONV_K_N			109	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 4, числитель
#define REG_ADC_HV_I4_CONV_K_D			110	// Коэффициент пересчёта оцифровки тока высокого напряжения диапазона 4, знаменатель
#define REG_ADC_HV_I4_CONV_OFFSET		111	// Оффсет оцифровки тока высокого напряжения диапазона 4 (в мВ входа АЦП)

#define REG_VOLTAGE_KP					112	// Пропорциональный коэффициент регулятора напряжения
#define REG_VOLTAGE_KI					113	// Интегральный коэффициент регулятора напряжения

#define REG_CURRENT_KP					114	// Пропорциональный коэффициент регулятора тока
#define REG_CURRENT_KI					115	// Интегральный коэффициент регулятора тока

// 116 - 127

//калиброванные значения DAC для каждого диапазона напряжения
#define DAC_V200_NULL		1
#define DAC_V200_TOP		2
#define DAC_2V00_NULL		3
#define DAC_2V00_TOP		4
#define DAC_20V0_NULL		5
#define DAC_20V0_TOP		6
#define DAC_270V_NULL		7
#define DAC_270V_TOP		8

//калиброванные значения ADC для каждого диапазона напряжения
#define ADC_BLV_V200_NULL	10
#define ADC_BLV_V200_TOP	11
#define ADC_BLV_2V00_NULL	12
#define ADC_BLV_2V00_TOP	13
#define ADC_BLV_20V0_NULL	14
#define ADC_BLV_20V0_TOP	15
#define ADC_BHV_270V_NULL	16
#define ADC_BHV_270V_TOP	17
#define ADC_POT_V200_NULL	18
#define ADC_POT_V200_TOP	19
#define ADC_POT_2V00_NULL	20
#define ADC_POT_2V00_TOP	21
#define ADC_POT_20V0_NULL	22
#define ADC_POT_20V0_TOP	23
#define ADC_PHV_270V_NULL	24
#define ADC_PHV_270V_TOP	25

//калиброванные значения ADC для каждого диапазона тока
#define ADC_ILV_R1_NULL	30
#define ADC_ILV_R1_TOP	31
#define ADC_ILV_R2_NULL	32
#define ADC_ILV_R2_TOP	33
#define ADC_ILV_R3_NULL	34
#define ADC_ILV_R3_TOP	35
#define ADC_ILV_R4_NULL	36
#define ADC_ILV_R4_TOP	37
#define ADC_IHV_R1_NULL	40
#define ADC_IHV_R1_TOP	41
#define ADC_IHV_R2_NULL	42
#define ADC_IHV_R2_TOP	43
#define ADC_IHV_R3_NULL	44
#define ADC_IHV_R3_TOP	45
#define VRANGE_20V0	46
//калиброванные значения DAC для каждого диапазона тока
#define DAC_110MA_LIMIT		50
#define DAC_100MKA_NULL		51
#define DAC_100MKA_TOP		52
#define DAC_1MA_NULL		53
#define DAC_1MA_TOP			54
#define DAC_10MA_NULL		55
#define DAC_10MA_TOP		56
#define DAC_110MA_NULL		57
#define DAC_110MA_TOP		58


// Несохраняемые регистры чтения-записи
#define DCV_REG_OUTPUT_LINE				128	// Линия подачи выходного напряжения
#define DCV_REG_OUTPUT_TYPE				129	// Тип выхода
#define DCV_REG_OUTPUT_MODE				130	// Режим выхода
#define DCV_REG_PULSE_LENGTH			131	// Длительность выходного импульса

#define DCV_REG_CURRENT_SETPOINT		135	// Значение задания тока (в мкА)
#define DCV_REG_CURRENT_SETPOINT_32		136
#define DCV_REG_VOLTAGE_SETPOINT		137	// Значение задания напряжения (в мВ)
#define DCV_REG_VOLTAGE_SETPOINT_32		138

#define REG_SCOPE_RATE					150	// Коэффициент деления частоты сэмплинга сохраняемых данных

#define REG_DEBUG						190	// Регистр режима Отладки

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
#define REG_SUB_STATE					198	// Регистр вспомогательного состояния


#define DCV_REG_CURRENT_RESULT			200	// Значение измерения тока (в мкА)
#define DCV_REG_CURRENT_RESULT_32		201
#define DCV_REG_VOLTAGE_RESULT			202	// Значение измерения напряжения (в мВ)
#define DCV_REG_VOLTAGE_RESULT_32		203

#define DCV_REG_VOLTAGE_READY			205	// Флаг выхода на уставку напряжения


#define REG_V_MEAS_L						200 // Регистр установки источника напряжения LESS HALF
#define REG_V_MEAS_M						201 // Регистр установки источника напряжения MOST HALF
#define REG_I_MEAS_L						202 // Регистр тока отсечки в режиме источника напряжения LESS HALF
#define REG_I_MEAS_M						203 // Регистр тока отсечки в режиме источника напряжения MOST HALF
//
#define REG_DBG_SYNC1				251	// Регистр состояния внутреннейи линии SYNC1
#define REG_DBG_SYNC2				252	// Регистр состояния внутреннейи линии SYNC2

#define REG_EP_LAST_POINTER		250	// Указатель на последий элемент быстрого логгирования

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
#define EP_I_MEASURE					1	// Измерение тока
#define EP_V_MEASURE					2	// Измерение напряжения
#define EP_SETPOINT						3	// Уставка
#define EP_CONTROL						4	// Выход управления
#define EP_RAW_CONTROL					5	// Сырой выход управления

//  Fault and disable codes
#define DF_NONE							0

// Problem
#define PROBLEM_NONE					0

//  Warning
#define WARNING_NONE					0

//  User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ
#define ERR_BAD_CONFIG					5	//  Попытка запуска измерения с неверной конфигурацией

#endif //  __DEV_OBJ_DIC_H
