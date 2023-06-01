// ======================================================================
// \title  Sender.cpp
// \author tim
// \brief  cpp file for Sender component implementation class
// ======================================================================


#include <Ref/DTN/Sender.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <string>
#include <dirent.h>
#include <iostream>
#include <limits.h>       //For PATH_MAX

namespace Dtn {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  Sender ::
    Sender(
        const char *const compName
    ) : SenderComponentBase(compName)
  {

  }

  void Sender ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    SenderComponentBase::init(queueDepth, instance);
  }

  Sender ::
    ~Sender()
  {

  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void Sender ::
    SEND_HELLO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    U8 data[] = {0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x0A};
    Fw::ComBuffer msg(data, sizeof(data));
    this->out_out(0, msg, 0);
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

  void Sender ::
    SEND_FILES_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
      DIR *dp = nullptr;
      struct dirent *entry = nullptr;
      FILE *entry_file;
      char buffer[1024];
      U8 data[1024];
      size_t len;
      char path[PATH_MAX + 1] = "/home/tim/files/";
      
      dp = opendir("/home/tim/files");
      if (dp != nullptr) {
          while ((entry = readdir(dp))) {
              len = 0;
              strcpy(path, "/home/tim/files/");
              if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                  strcat(path, entry->d_name);
                  
                  entry_file = fopen(path, "rw");
                  if (entry_file == NULL)
                  {
                      fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
                  }

                  /* Doing some stuff with entry file : */
                  /* For example use fgets */
                  while (fgets(buffer, 1024, entry_file) != NULL)
                  {
                  }

                  /* When you finish with the file, close it */
                  fclose(entry_file);
                  remove(path);

                  memcpy(data, buffer, strlen(buffer));
                  Fw::ComBuffer msg(data, strlen(buffer));
                  this->out_out(0, msg, 0);
              }
          }
      }

      closedir(dp);
    
      this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace Dtn
