#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

//TODO check define [1..4]
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
#define ACT_DBG_SELECT_DAC				68	// Выбор рабочего источника тока/напряжения [REG_DBG_STATE]
#define ACT_DBG_WRITE_DAC				69	// Запись параметров в источник тока/напряжения [REG_DBG_STATE]

#define ACT_DBG_SELECT_LV_CTRLS			70	// Выбор диапазона ... напряжения
#define ACT_DBG_SELECT_HV_CTRLS			71	// Выбор диапазона ... напряжения
#define ACT_DBG_READ_ADC_ICH			72	// Измерение тока
#define ACT_DBG_READ_ADC_VCH			73	// Измерение напряжения

//TODO add more ACT_DBG !!!

#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию

#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

// Несохраняемы регистры чтения-записи
#define REG_DBG_STATE					150	// Регистр режима Отладки

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции

#define REG_DBG_SYNC1				251	// Регистр состояния внутреннейи линии SYNC1
#define REG_DBG_SYNC2				252	// Регистр состояния внутреннейи линии SYNC2

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
#define ERR_CONFIGURATION_LOCKED		1	//  Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	//  Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	//  Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	//  Неправильный ключ

#endif //  __DEV_OBJ_DIC_H
