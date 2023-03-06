// ======================================================================
// \title  BundleProtocol.hpp
// \author T-recks
// \brief  hpp file for BundleProtocol class
//
// \copyright
// Copyright 2009-2021, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef SVC_BUNDLE_PROTOCOL_HPP
#define SVC_BUNDLE_PROTOCOL_HPP

#include <Svc/FramingProtocol/FramingProtocol.hpp>
#include <Svc/FramingProtocol/DeframingProtocol.hpp>

namespace Svc {

  //! \brief Implements the F Prime framing protocol
  class BundleFraming: public FramingProtocol {
    public:

      //! Constructor
      BundleFraming();

      //! Implements the frame method
      void frame(
          const U8* const data, //!< The data
          const U32 size, //!< The data size in bytes
          Fw::ComPacket::ComPacketType packet_type //!< The packet type
      ) override;

  };

  //! \brief Implements the F Prime deframing protocol
  class BundleDeframing : public DeframingProtocol {
    public:

      //! Constructor
      BundleDeframing();

      //! Validates data against the stored hash value
      //! 1. Computes the hash value V of bytes [0,size-1] in the circular buffer
      //! 2. Compares V against bytes [size, size + HASH_DIGEST_LENGTH - 1] of
      //!    the circular buffer, which are expected to be the stored hash value.
      bool validate(
          Types::CircularBuffer& buffer, //!< The circular buffer
          U32 size //!< The data size in bytes
      );

      //! Implements the deframe method
      //! \return Status
      DeframingStatus deframe(
          Types::CircularBuffer& buffer, //!< The circular buffer
          U32& needed //!< The number of bytes needed, updated by the caller
      ) override;

  };

}
#endif  // SVC_BUNDLE_PROTOCOL_HPP
