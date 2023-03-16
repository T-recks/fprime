// ======================================================================
// \title  Outduct.cpp
// \author tim
// \brief  cpp file for Outduct component implementation class
// ======================================================================


#include <Ref/DTN/Outduct.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  Outduct ::
    Outduct(
        const char *const compName
    ) : OutductComponentBase(compName)
  {

  }

  void Outduct ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    OutductComponentBase::init(queueDepth, instance);
  }

  Outduct ::
    ~Outduct()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void Outduct ::
    send_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::ComBuffer &data,
        U32 context
    )
  {
      this->toSocket_out(0, data, 0);
  }

} // end namespace Dtn
