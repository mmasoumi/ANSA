//
// Marek Cerny, 2MSK
// FIT VUT 2011
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __ANSAINET_CONFIGLOADER_H_
#define __ANSAINET_CONFIGLOADER_H_

#include <omnetpp.h>

#include "RoutingTable6Access.h"
#include "InterfaceTableAccess.h"
#include "InterfaceTableAccess.h"
#include "AnsaRoutingTableAccess.h"
#include "PimInterfaceTable.h"
#include "IPv4InterfaceData.h"

#include "RIPngRouting.h"


class DeviceConfigurator : public cSimpleModule {

   protected:
      IInterfaceTable *ift;
      RoutingTable6 *rt6;
      AnsaRoutingTable *rt;
      PimInterfaceTable *pimIft;        /**< Link to table of PIM interfaces. */

   private:
      void loadDefaultRouter(cXMLElement *gateway);
      void loadInterfaceConfig(cXMLElement *iface);
      void loadStaticRouting(cXMLElement *route);

   protected:
      virtual int numInitStages() const {return 4;}
      virtual void initialize(int stage);
      virtual void handleMessage(cMessage *msg);

   protected:
      //configuration for PIM
      bool isMulticastEnabled(cXMLElement *device);
      void loadPimInterfaceConfig(cXMLElement *iface);

   public:
      // configuration for RIPng
      /**
       * Loads configuration for RIPngModule
       * @param RIPngModule [in]
       */
      void loadRIPngConfig(RIPngRouting *RIPngModule);

      /**
       * Adds unicast prefixes obtained from the interface configuration to the RIPngRouting table
       * @param RIPngModule [in]
       * @param interface [in] interface, from which should be added prefixes
       * @see InterfaceTable
       */
      void loadPrefixesFromInterfaceToRIPngRT(RIPngRouting *RIPngModule, cXMLElement *interface);
};

#endif