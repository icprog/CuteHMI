#include "../../../../include/cutehmi/authssh/internal/ChannelsThread.hpp"
#include "../../../../include/cutehmi/authssh/logging.hpp"
#include "../../../../include/cutehmi/authssh/AbstractChannel.hpp"
#include "../../../../include/cutehmi/authssh/Exception.hpp"
#include "../../../../include/cutehmi/authssh/Session.hpp"

#include <libssh/libssh.h>

namespace cutehmi {
namespace authssh {
namespace internal {

//QString ChannelsThread::Error::str() const
//{
//	switch (code()) {
//		case Error::SESSION_SWITCH:
//			return tr("Session switch requested.");
//		default:
//			return Error::str();
//	}
//}

ChannelsThread::ChannelsThread(QObject * parent):
	QThread(parent),
	m_session(NULL)
{
}

ChannelsThread::~ChannelsThread()
{
	while (!m_channels.isEmpty())
		delete m_channels.takeFirst();
}

void ChannelsThread::start(Session * session)
{
	m_session = session;
	Parent::start();
}

void ChannelsThread::addChannel(std::unique_ptr<AbstractChannel> channel)
{
	channel.get()->moveToThread(this);
	m_channels.append(channel.release());
}

//void ChannelsThread::pushSession(Session * session)
//{
////	m_switchSession = session;
//	exit(Error::SESSION_SWITCH);
////	ssh_session session = m_session->acquireLibsshSession();
////	emit sessionSwitched
//}

void ChannelsThread::quit()
{
	if (isRunning()) {
		CUTEHMI_LOG_DEBUG("Requesting channels thread to quit...");
		requestInterruption();
		Parent::quit();
	}
}

void ChannelsThread::run()
{
	int retVal = 0;

	ssh_session session = m_session->acquireLibsshSession();

	for (ChannelsContainer::iterator it = m_channels.begin(); it != m_channels.end(); ++it)
		(*it)->init(session);

	if (!isInterruptionRequested())
//		do {
			retVal = exec();
//			if (retVal == Error::SESSION_SWITCH) {
//				ssh_session =
//				for (ChannelsContainer::iterator it = m_channels.begin(); it != m_channels.end(); ++it)
//					(*it)->switchSession(newSession);
//			}
//		} while (retVal != Error::SESSION_SWITCH);

	for (ChannelsContainer::iterator it = m_channels.begin(); it != m_channels.end(); ++it)
		if ((*it)->isInitialized())
			(*it)->shutdown();


	m_session->releaseLibsshSession(session);
	m_session = nullptr;

	CUTEHMI_LOG_DEBUG("Channels thread quits with return code: " << retVal << ".");
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
