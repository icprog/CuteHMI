#ifndef CUTEHMI_LIBBASE_SRC_BASE_ERRORINFO_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_ERRORINFO_HPP

#include <QString>

#include <typeinfo>

#include "Error.hpp"

namespace cutehmi {
namespace base {

struct ErrorInfo
{
	int code;				///< Error code.
	const char * errClass;	///< Error class.
	QString str;			///< Error string.
};

/**
 * Get error info. Produces ErrorInfo from instance of Error or its subclass.
 * @param err instance of Error class or its subclass.
 * @return error info structure.
 */
template <typename ERR>
ErrorInfo errorInfo(ERR err)
{
	return ErrorInfo{err.code(), typeid(ERR).name(), err.str()};
}

}
}

Q_DECLARE_METATYPE(cutehmi::base::ErrorInfo)

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
