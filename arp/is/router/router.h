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
#define LOCK_ADDR (8*1024*1024)
#define SIN_ADDR (9*1024*1024)

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
  //Communication port to the lock.
  ac_tlm_port LOCK_port;
  //Communication port to the sin.
  ac_tlm_port SIN_port;	


  /**
   * Implementation of TLM transport method that
   * handles packets of the protocol doing apropriate actions.
   * @param request is a received request packet
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    //Access to the lock.
    if (request.addr == LOCK_ADDR) {
        return LOCK_port->transport (request);
    //Access to other memory positions.
    } else if (request.addr == SIN_ADDR) {
        return SIN_port->transport (request);

    } else {
        return DM_port->transport (request);
    }
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
