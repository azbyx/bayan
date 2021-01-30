#include <boost/uuid/detail/md5.hpp>
#include "md5hash.h"


std::string bayan::Md5Hash::hashAsString(const char* data, size_t size) {

	std::string res;

	boost::uuids::detail::md5 hash;
	boost::uuids::detail::md5::digest_type digest;

	hash.process_bytes(data, size);
	hash.get_digest(digest);
	for (int i = 0; i < 4; i++)
		res += std::to_string(digest[i]);

	return res;

}
