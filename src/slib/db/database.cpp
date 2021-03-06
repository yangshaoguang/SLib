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

#include "slib/db/database.h"

namespace slib
{

	SLIB_DEFINE_OBJECT(Database, Object)

	Database::Database()
	{
	}

	Database::~Database()
	{
	}

	sl_int64 Database::executeBy(const String& sql, const Variant* params, sl_uint32 nParams)
	{
		Ref<DatabaseStatement> statement = prepareStatement(sql);
		if (statement.isNotNull()) {
			return statement->executeBy(params, nParams);
		}
		return -1;
	}

	Ref<DatabaseCursor> Database::queryBy(const String& sql, const Variant* params, sl_uint32 nParams)
	{
		Ref<DatabaseStatement> statement = prepareStatement(sql);
		if (statement.isNotNull()) {
			return statement->queryBy(params, nParams);
		}
		return sl_null;
	}

	List< HashMap<String, Variant> > Database::getListForQueryResultBy(const String& sql, const Variant* params, sl_uint32 nParams)
	{
		Ref<DatabaseStatement> statement = prepareStatement(sql);
		if (statement.isNotNull()) {
			return statement->getListForQueryResultBy(params, nParams);
		}
		return sl_null;
	}

	HashMap<String, Variant> Database::getRecordForQueryResultBy(const String& sql, const Variant* params, sl_uint32 nParams)
	{
		Ref<DatabaseStatement> statement = prepareStatement(sql);
		if (statement.isNotNull()) {
			return statement->getRecordForQueryResultBy(params, nParams);
		}
		return sl_null;
	}

	Variant Database::getValueForQueryResultBy(const String& sql, const Variant* params, sl_uint32 nParams)
	{
		Ref<DatabaseStatement> statement = prepareStatement(sql);
		if (statement.isNotNull()) {
			return statement->getValueForQueryResultBy(params, nParams);
		}
		return sl_null;
	}

	sl_int64 Database::execute(const String& sql)
	{
		return executeBy(sql, sl_null, 0);
	}

	Ref<DatabaseCursor> Database::query(const String& sql)
	{
		return queryBy(sql, sl_null, 0);
	}

	List< HashMap<String, Variant> > Database::getListForQueryResult(const String& sql)
	{
		List< HashMap<String, Variant> > ret;
		Ref<DatabaseCursor> cursor = query(sql);
		if (cursor.isNotNull()) {
			while (cursor->moveNext()) {
				ret.add_NoLock(cursor->getRow());
			}
		}
		return ret;
	}

	HashMap<String, Variant> Database::getRecordForQueryResult(const String& sql)
	{
		Ref<DatabaseCursor> cursor = query(sql);
		if (cursor.isNotNull()) {
			if (cursor->moveNext()) {
				return cursor->getRow();
			}
		}
		return sl_null;
	}

	Variant Database::getValueForQueryResult(const String& sql)
	{
		Ref<DatabaseCursor> cursor = query(sql);
		if (cursor.isNotNull()) {
			if (cursor->moveNext()) {
				return cursor->getValue(0);
			}
		}
		return sl_null;
	}

}
