// ======================================================================
// \title  DTN.cpp
// \author tim
// \brief  cpp file for DTN component implementation class
// ======================================================================


#include <Ref/DTN/DTN.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DTN ::
    DTN(
        const char *const compName
    ) : DTNComponentBase(compName)
  {

  }

  void DTN ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    DTNComponentBase::init(queueDepth, instance);
  }

  DTN ::
    ~DTN()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void DTN ::
    fromSocket_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::ComBuffer &data,
        U32 context
    )
  {
    this->log_ACTIVITY_HI_BUNDLE_RECEIVED();
  }

  void DTN ::
    sesend_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void DTN ::
    SEND_DUMMY_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // 0x9f88070000820282020282028201018202820101820018281a000f424085010100005823526561647920746f2067656e657261746520612033322d62797465207061796c6f6164ff
    U8 data[] = {0x9f, 0x88, 0x07, 0x00, 0x00, 0x82, 0x02, 0x82, 0x02, 0x02, 0x82, 0x02, 0x82, 0x01, 0x01, 0x82, 0x02, 0x82, 0x01, 0x01, 0x82, 0x00, 0x18, 0x28, 0x1a, 0x00, 0x0f, 0x42, 0x40, 0x85, 0x01, 0x01, 0x00, 0x00, 0x58, 0x23, 0x52, 0x65, 0x61, 0x64, 0x79, 0x20, 0x74, 0x6f, 0x20, 0x67, 0x65, 0x6e, 0x65, 0x72, 0x61, 0x74, 0x65, 0x20, 0x61, 0x20, 0x33, 0x32, 0x2d, 0x62, 0x79, 0x74, 0x65, 0x20, 0x70, 0x61, 0x79, 0x6c, 0x6f, 0x61, 0x64, 0xff};
    Fw::ComBuffer msg(data, sizeof(data));
    this->toSocket_out(0, msg, 0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Ref
