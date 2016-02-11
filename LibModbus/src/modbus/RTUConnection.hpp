#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_RTUCONNECTION_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_RTUCONNECTION_HPP

#include "AbstractConnection.hpp"

#include <modbus.h>

#include <QString>

namespace modbus {

/**
 * RTU connection base-from-member. So called base-from-member idiom is used to initialize
 * members before calling real parent class constructor.
 */
class CUTEHMI_MODBUS_API RTUConnection_baseFromMember
{
	protected:
		enum class Parity : int
		{
			NONE,
			EVEN,
			ODD
		};

		enum class DataBits : int
		{
			BITS_5 = 5,
			BITS_6 = 6,
			BITS_7 = 7,
			BITS_8 = 8,
		};

		enum class StopBits : int
		{
			BITS_1 = 1,
			BITS_2 = 2
		};

		RTUConnection_baseFromMember(const QString & port, int baudRate, Parity parity, DataBits dataBits, StopBits stopBits);

		QString m_port;
		int m_baudRate;
		Parity m_parity;
		DataBits m_dataBits;
		StopBits m_stopBits;
};

/**
 * RTU connection.
 */
class CUTEHMI_MODBUS_API RTUConnection:
	private RTUConnection_baseFromMember,
	public AbstractConnection
{
	typedef AbstractConnection Parent;

	public:
		typedef RTUConnection_baseFromMember::Parity Parity;
		typedef RTUConnection_baseFromMember::DataBits DataBits;
		typedef RTUConnection_baseFromMember::StopBits StopBits;

//<workaround id="LibModbus-1" target="libmodbus" cause="bug">
//		enum class Mode : int
//		{
//			RS232 = MODBUS_RTU_RS232,
//			RS485 = MODBUS_RTU_RS485
//		};
//</workaround>
//<workaround id="LibModbus-2" target="LibModbus" cause="LibModbus-1">
		enum class Mode : int
		{
			RS232 = MODBUS_RTU_RS232
		};
//</workaround>

		RTUConnection(const QString & port, int baudRate = 19200, Parity parity = Parity::NONE, DataBits dataBits = DataBits::BITS_8, StopBits stopBits = StopBits::BITS_1, Mode mode = Mode::RS232);

		virtual ~RTUConnection();

	private:
		static char ToLibmodbusParity(Parity parity);

		Mode m_mode;
};

}

#endif
