/**
 */

//////////////////////////////////////////////////////////////////////////////

#ifndef ROUTER_H_
#define ROUTER_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

//#define DEBUG

/// Namespace to isolate router from ArchC
namespace user
{

/// A TLM router
class router :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;
  /// Internal write
  ac_tlm_rsp_status writem( const uint32_t & , const uint32_t & );
  /// Internal read
  ac_tlm_rsp_status readm( const uint32_t & , uint32_t & );
  //Communication port to the memory.
  ac_tlm_port DM_port;

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be sent
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    

    return DM_port->transport (request);
  }


  /**
   * Default constructor.
   *
   * @param k Memory size in kilowords.
   *
   */
  router( sc_module_name module_name , int k = 5242880 );

  /**
   * Default destructor.
   */
  ~router();


};

};

#endif //ROUTER_H_
