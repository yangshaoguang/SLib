/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "slib/core/log.h"

#include "slib/core/file.h"
#include "slib/core/console.h"
#include "slib/core/variant.h"
#include "slib/core/safe_static.h"

#if defined(SLIB_PLATFORM_IS_ANDROID)
#include <android/log.h>
#endif

#if defined(SLIB_PLATFORM_IS_TIZEN)
#include <dlog.h>
#endif

namespace slib
{

	SLIB_DEFINE_OBJECT(Logger, Object)

	Logger::Logger()
	{
	}

	Logger::~Logger()
	{
	}

	void Logger::logError(const String& tag, const String& content)
	{
		log(tag, content);
	}

	static String _priv_Log_getLineString(const String& tag, const String& content)
	{
		return String::format("%s [%s] %s", Time::now(), tag, content);
	}

	FileLogger::FileLogger()
	{
	}

	FileLogger::FileLogger(const String& fileName)
	{
		setFileName(fileName);
	}

	FileLogger::~FileLogger()
	{
	}

	void FileLogger::log(const String& tag, const String& content)
	{
		String fileName = getFileName();
		if (fileName.isEmpty()) {
			return;
		}
		String s = _priv_Log_getLineString(tag, content) + "\r\n";
		if (s.getLength() > 0) {
			ObjectLocker lock(this);
			File::appendAllTextUTF8(fileName, s);
		}
	}
	
	class ConsoleLogger : public Logger
	{
	public:
		SLIB_INLINE ConsoleLogger() {}

	public:
		void log(const String& tag, const String& content) override
		{
#if defined(SLIB_PLATFORM_IS_ANDROID)
			ObjectLocker lock(this);
			__android_log_print(ANDROID_LOG_INFO, tag.getData(), "%s", content.getData());
#elif defined(SLIB_PLATFORM_IS_TIZEN)
			ObjectLocker lock(this);
			if (content.isNotEmpty()) {
				::dlog_print(DLOG_INFO, tag.getData(), "%s", content.getData());
			} else {
				::dlog_print(DLOG_INFO, tag.getData(), " ");
			}
#else
			String s = _priv_Log_getLineString(tag, content);
			Console::println(s);
#endif
		}

		void logError(const String& tag, const String& content) override
		{
#if defined(SLIB_PLATFORM_IS_ANDROID)
			ObjectLocker lock(this);
			__android_log_print(ANDROID_LOG_ERROR, tag.getData(), "%s", content.getData());
#elif defined(SLIB_PLATFORM_IS_TIZEN)
			ObjectLocker lock(this);
			if (content.isNotEmpty()) {
				::dlog_print(DLOG_ERROR, tag.getData(), "%s", content.getData());
			} else {
				::dlog_print(DLOG_ERROR, tag.getData(), " ");
			}
#else
			log(tag, content);
#endif
		}
	};


	LoggerSet::LoggerSet()
	{
	}

	LoggerSet::LoggerSet(const Ref<Logger>& logger, const Ref<Logger>& errorLogger)
	{
		addDefaultLogger(logger);
		addErrorLogger(errorLogger);
	}

	LoggerSet::~LoggerSet()
	{
	}

	void LoggerSet::clearDefaultLogger()
	{
		m_listLoggers.removeAll();
	}

	void LoggerSet::addDefaultLogger(const Ref<Logger>& logger)
	{
		m_listLoggers.add(logger);
	}

	void LoggerSet::removeDefaultLogger(const Ref<Logger>& logger)
	{
		m_listLoggers.remove(logger);
	}


	void LoggerSet::clearErrorLogger()
	{
		m_listErrorLoggers.removeAll();
	}

	void LoggerSet::addErrorLogger(const Ref<Logger>& logger)
	{
		m_listErrorLoggers.add(logger);
	}

	void LoggerSet::removeErrorLogger(const Ref<Logger>& logger)
	{
		m_listErrorLoggers.remove(logger);
	}


	void LoggerSet::log(const String& tag, const String& content)
	{
		ListLocker< Ref<Logger> > list(m_listLoggers);
		for (sl_size i = 0; i < list.count; i++) {
			list[i]->log(tag, content);
		}
	}

	void LoggerSet::logError(const String& tag, const String& content)
	{
		ListLocker< Ref<Logger> > list(m_listLoggers);
		for (sl_size i = 0; i < list.count; i++) {
			list[i]->logError(tag, content);
		}
	}

	Ref<LoggerSet> Logger::global()
	{
		Ref<Logger> console(getConsoleLogger());
		SLIB_SAFE_STATIC(Ref<LoggerSet>, log, new LoggerSet(console, console))
		if (SLIB_SAFE_STATIC_CHECK_FREED(log)) {
			return sl_null;
		}
		return log;
	}

	Ref<Logger> Logger::getConsoleLogger()
	{
		SLIB_SAFE_STATIC(Ref<Logger>, logger, new ConsoleLogger)
		if (SLIB_SAFE_STATIC_CHECK_FREED(logger)) {
			return sl_null;
		}
		return logger;
	}

	Ref<Logger> Logger::createFileLogger(const String& fileName)
	{
		return new FileLogger(fileName);
	}

	void Logger::logGlobal(const String& tag, const String& content)
	{
		Ref<LoggerSet> log = global();
		if (log.isNotNull()) {
			log->log(tag, content);
		}
	}

	void Logger::logGlobalError(const String& tag, const String& content)
	{
		Ref<LoggerSet> log = global();
		if (log.isNotNull()) {
			log->logError(tag, content);
		}
	}

}

