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
        Fw::ComBuffer &data,
        U32 context
    )
  {
      // std::cout << "BUFFER" << std::endl;
      std::ofstream file;
    
      // Emit telemetry and events
      this->log_ACTIVITY_HI_BUNDLE_RECEIVED();

      // this->m_count++;
      // this->tlmWrite_RECV(m_count);

      // print buffer data
      file.open("bundle-log.txt", std::ios::app);
      file.write((const char*)data.getBuffAddr(), data.getBuffCapacity());
      // file.put('\n');
      file.close();
      
      // for (int i = 0; i < recvBuffer.getSize(); i++) {
      //     std::cout << data[i];
      // }
      // std::cout << std::endl;
  
  }

} // end namespace Dtn
