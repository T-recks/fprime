// ======================================================================
// \title  BpSerializer.cpp
// \author tim
// \brief  cpp file for BpSerializer component implementation class
// ======================================================================


#include <Ref/DTN/BpSerializer.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Ref {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  BpSerializer ::
    BpSerializer(
        const char *const compName
    ) : BpSerializerComponentBase(compName)
  {

  }

  void BpSerializer ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    BpSerializerComponentBase::init(queueDepth, instance);
  }

  BpSerializer ::
    ~BpSerializer()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void BpSerializer ::
    SEND_DUMMY_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    // 0x9F88070000820282020182028201018202820101820018281A000F424085010100005823526561647920746F2067656E657261746520612033322D62797465207061796C6F6164FF
    U8 data[] = {0x9F, 0x88, 0x07, 0x00, 0x00, 0x82, 0x02, 0x82, 0x02, 0x01, 0x82, 0x02, 0x82, 0x01, 0x01, 0x82, 0x02, 0x82, 0x01, 0x01, 0x82, 0x00, 0x18, 0x28, 0x1A, 0x00, 0x0F, 0x42, 0x40, 0x85, 0x01, 0x01, 0x00, 0x00, 0x58, 0x23, 0x52, 0x65, 0x61, 0x64, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74, 0x65, 0x20, 0x61, 0x20, 0x33, 0x32, 0x2D, 0x62, 0x79, 0x74, 0x65, 0x20, 0x70, 0x61, 0x79, 0x6C, 0x6F, 0x61, 0x64, 0xFF};
    Fw::ComBuffer msg(data, sizeof(data));
    this->out_out(0, msg, 0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Dtn
