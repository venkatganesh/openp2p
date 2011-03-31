#ifndef OPENP2P_ROOTNETWORK_ID_HPP
#define OPENP2P_ROOTNETWORK_ID_HPP

#include <OpenP2P/Kademlia/Id.hpp>
#include <OpenP2P/RootNetwork/Parameters.hpp>

namespace OpenP2P{

	namespace RootNetwork{

		typedef typename Kademlia::Id<IdSize> Id;

		void zeroId(){
			return Kademlia::zeroId<IdSize>();
		}

	}

}

#endif
