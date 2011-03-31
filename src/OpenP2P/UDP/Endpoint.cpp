#include <stdint.h>
#include <cstddef>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <OpenP2P/BinaryStream.hpp>

#include <OpenP2P/UDP/Endpoint.hpp>

namespace OpenP2P {

	namespace {

		const uint8_t ipversion_4 = 0;
		const uint8_t ipversion_6 = 1;

	}

	BinaryStream& operator>>(BinaryStream& stream, UDP::Endpoint& endpoint) {
		uint8_t ipversion;
		uint8_t address_data[16];
		uint16_t port;

		stream >> ipversion >> port;

		if (ipversion == ipversion_4) {
			stream.read(address_data, 4);
			boost::array<unsigned char, 4> array;
			for (std::size_t i = 0; i < 4; i++) {
				array[i] = address_data[i];
			}
			endpoint.address(boost::asio::ip::address_v4(array));
		}
		else {
			stream.read(address_data, 16);
			boost::array<unsigned char, 16> array;
			for (std::size_t i = 0; i < 16; i++) {
				array[i] = address_data[i];
			}
			endpoint.address(boost::asio::ip::address_v6(array));
		}

		endpoint.port(port);

		return stream;
	}

	BinaryStream& operator<<(BinaryStream& stream, const UDP::Endpoint& endpoint) {
		uint8_t ipVersion;
		const uint8_t * addressData;
		std::size_t addressSize;

		if (endpoint.address().is_v4()) {
			boost::asio::ip::address_v4 address = endpoint.address().to_v4();
			addressData = (const uint8_t *) address.to_bytes().data();
			addressSize = 4;
			ipVersion = ipversion_4;
		}
		else {
			boost::asio::ip::address_v6 address = endpoint.address().to_v6();
			addressData = (const uint8_t *) address.to_bytes().data();
			addressSize = 16;
			ipVersion = ipversion_6;
		}

		stream << ipVersion << uint16_t(endpoint.port());
		stream.write(addressData, addressSize);

		return stream;
	}

}

