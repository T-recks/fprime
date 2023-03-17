// ======================================================================
// \title  Induct.cpp
// \author tim
// \brief  cpp file for Induct component implementation class
// ======================================================================


#include <Ref/DTN/Induct.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Dtn {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  Induct ::
    Induct(
        const char *const compName
    ) : InductComponentBase(compName)
  {

  }

  void Induct ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    InductComponentBase::init(queueDepth, instance);
  }

  Induct ::
    ~Induct()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void Induct ::
    fromSocket_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::ComBuffer &data,
        U32 context
    )
  {
    // TODO
  }

} // end namespace Dtn
