#include <OpenP2P.hpp>
#include <OpenP2P/UDP.hpp>

using namespace OpenP2P;

class TestRPCSocket: public RPCSocket<UDP::Endpoint, uint32_t>{
	public:
		TestRPCSocket(UDP::Socket& socket) : socket_(socket){ }

		void send(const UDP::Endpoint& endpoint, bool isRequest, const uint32_t& id, const Buffer& data){
			BufferBuilder builder;
			BinaryStream stream(builder);
			stream << isRequest << id << data;

			socket_.send(endpoint, builder.getBuffer());
		}
			
		bool receive(UDP::Endpoint& endpoint, bool& isRequest, uint32_t& id, Buffer& data){
			Buffer buff;
			if(socket_.receive(endpoint, buff)){
				BufferIterator iterator(buff);
				BinaryStream stream(iterator);
				return (stream >> isRequest >> id >> data);
			}else{
				return false;
			}
		}

		void cancel(){
			//
		}

		void close(){
			socket_.close();
		}

	private:
		UDP::Socket& socket_;

};

