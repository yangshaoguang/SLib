#ifndef CHECKHEADER_SLIB_NETWORK_MAC_ADDRESS
#define CHECKHEADER_SLIB_NETWORK_MAC_ADDRESS

#include "definition.h"

#include "ip_address.h"

#include "../core/string.h"

SLIB_NETWORK_NAMESPACE_BEGIN

class SLIB_EXPORT MacAddress
{
public:
	sl_uint8 m[6];

public:
	MacAddress() = default;
	
	MacAddress(const MacAddress& other) = default;

	MacAddress(const sl_uint8* m);
	
	MacAddress(sl_uint8 m0, sl_uint8 m1, sl_uint8 m2, sl_uint8 m3, sl_uint8 m4, sl_uint8 m5);
	
	MacAddress(const String& address);

public:
	static const MacAddress& zero();
	
	sl_bool isZero() const;
	
	sl_bool isNotZero() const;

	void setZero();

	static const MacAddress& getBroadcast();
	
	sl_bool isBroadcast() const;
	
	sl_bool isNotBroadcast() const;

	void setBroadcast();
	
	sl_bool isMulticast() const;

	sl_bool isNotMulticast() const;

	void makeMulticast(const IPv4Address& addrMulticast);
	
	void makeMulticast(const IPv6Address& addrMulticast);
	
	void getBytes(sl_uint8* _m) const;
	
	void setBytes(const sl_uint8* _m);
	
	int compare(const MacAddress& other) const;
	
	sl_uint32 hashCode() const;
	
	// m0-m1-m2-m3-m4-m5, m0:m1:m2:m3:m4:m5
	String toString(sl_char8 sep = '-') const;
	
	static sl_int32 parse(MacAddress* out, const char* sz, sl_uint32 posBegin = 0, sl_uint32 len = SLIB_INT32_MAX, sl_char8 sep = 0);
	
	static sl_int32 parse(MacAddress* out, const sl_char16* sz, sl_uint32 posBegin = 0, sl_uint32 len = SLIB_INT32_MAX, sl_char8 sep = 0);
	
	sl_bool parse(const String& str, sl_char8 sep = 0);
	
public:
	MacAddress& operator=(const MacAddress& other) = default;
	
	MacAddress& operator=(const String& address);

	sl_bool operator==(const MacAddress& other) const;
	
	sl_bool operator!=(const MacAddress& other) const;

private:
	static const sl_uint8 _zero[6];
	static const sl_uint8 _broadcast[6];

};

template <>
int Compare<MacAddress>::compare(const MacAddress& a, const MacAddress& b);

template <>
sl_bool Compare<MacAddress>::equals(const MacAddress& a, const MacAddress& b);

template <>
sl_uint32 Hash<MacAddress>::hash(const MacAddress& a);

SLIB_NETWORK_NAMESPACE_END


SLIB_NETWORK_NAMESPACE_BEGIN

SLIB_INLINE const MacAddress& MacAddress::zero()
{
	return *((MacAddress*)((void*)(&_zero)));
}

SLIB_INLINE sl_bool MacAddress::isZero() const
{
	return m[0] == 0 && m[1] == 0 && m[2] == 0 && m[3] == 0 && m[4] == 0 && m[5] == 0;
}

SLIB_INLINE sl_bool MacAddress::isNotZero() const
{
	return m[0] != 0 || m[1] != 0 || m[2] != 0 || m[3] != 0 || m[4] != 0 || m[5] != 0;
}

SLIB_INLINE const MacAddress& MacAddress::getBroadcast()
{
	return *((MacAddress*)((void*)(&_broadcast)));
}

SLIB_INLINE sl_bool MacAddress::isBroadcast() const
{
	return m[0] == 255 && m[1] == 255 && m[2] == 255 && m[3] == 255 && m[4] == 255 && m[5] == 255;
}

SLIB_INLINE sl_bool MacAddress::isNotBroadcast() const
{
	return m[0] != 255 || m[1] != 255 || m[2] != 255 || m[3] != 255 || m[4] != 255 || m[5] != 255;
}

SLIB_INLINE sl_bool MacAddress::isMulticast() const
{
	return (m[0] & 1);
}

SLIB_INLINE sl_bool MacAddress::isNotMulticast() const
{
	return (m[0] & 1) == 0;
}
SLIB_INLINE sl_bool MacAddress::operator==(const MacAddress& other) const
{
	return m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5];
}

SLIB_INLINE sl_bool MacAddress::operator!=(const MacAddress& other) const
{
	return m[0] != other.m[0] || m[1] != other.m[1] || m[2] != other.m[2] || m[3] != other.m[3] || m[4] != other.m[4] || m[5] != other.m[5];
}

SLIB_NETWORK_NAMESPACE_END

#endif
