// ======================================================================
// \title  Induct.cpp
// \author tim
// \brief  cpp file for Induct component implementation class
// ======================================================================


#include <Ref/DTN/Induct.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <fstream>

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
        const NATIVE_INT_TYPE instance
    )
  {
    InductComponentBase::init(instance);
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
        Fw::Buffer &recvBuffer,
        const Drv::RecvStatus &recvStatus
    )
  {
    // std::cout << "BUFFER" << std::endl;
    U8* data;
    std::ofstream file;
    
    if (recvStatus.e == Drv::RecvStatus::RECV_OK) {
      // Emit telemetry and events
      this->log_ACTIVITY_HI_BUNDLE_RECEIVED();

      this->m_count++;
      this->tlmWrite_RECV(m_count);

      // print buffer data
      data = recvBuffer.getData();

      file.open("bundle-log.txt", std::ios::app);
      file.write((const char*)data, recvBuffer.getSize());
      file.put('\n');
      file.close();
      
      // for (int i = 0; i < recvBuffer.getSize(); i++) {
      //     std::cout << data[i];
      // }
      // std::cout << std::endl;
    } else {
      this->log_ACTIVITY_HI_BUNDLE_ERROR();
    }
    deallocate_out(0, recvBuffer);
  
  }

} // end namespace Dtn
