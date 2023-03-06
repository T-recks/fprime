// ======================================================================
// \title  BundleProtocol.cpp
// \author T-recks
// \brief  cpp file for BundleProtocol class
//
// \copyright
// Copyright 2009-2022, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <limits>

#include "BundleProtocol.hpp"

namespace Svc {

BundleFraming::BundleFraming(): FramingProtocol() {}

BundleDeframing::BundleDeframing(): DeframingProtocol() {}

void BundleFraming::frame(const U8* const data, const U32 size, Fw::ComPacket::ComPacketType packet_type) {
    FW_ASSERT(data != nullptr);
    FW_ASSERT(m_interface != nullptr);
    // FpFrameHeader::TokenType real_data_size = size;
    // FpFrameHeader::TokenType total = real_data_size;
    Fw::Buffer buffer = m_interface->allocate(size);
    Fw::SerializeBufferBase& serializer = buffer.getSerializeRepr();

    // Serialize data
    Fw::SerializeStatus status;

    status = serializer.serialize(data, size, true);  // Serialize without length
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    // buffer.setSize(total);
    buffer.setSize(size);

    m_interface->send(buffer);
}

bool BundleDeframing::validate(Types::CircularBuffer& ring, U32 size) {
    return true;
}

DeframingProtocol::DeframingStatus BundleDeframing::deframe(Types::CircularBuffer& ring, U32& needed) {
    U32 size = 0;
    FW_ASSERT(m_interface != nullptr);
    // Read size
    size = ring.get_allocated_size();
    const U32 maxU32 = std::numeric_limits<U32>::max();
    if (size > maxU32) {
        // Size is too large to process: needed would overflow
        return DeframingProtocol::DEFRAMING_INVALID_SIZE;
    }
    needed = size;
    // Check frame size
    const U32 frameSize = size;
    if (frameSize > ring.get_capacity()) {
        // Frame size is too large for ring buffer
        return DeframingProtocol::DEFRAMING_INVALID_SIZE;
    }
    // Check for enough data to deserialize everything;
    // otherwise break and wait for more.
    else if (ring.get_allocated_size() < needed) {
        return DeframingProtocol::DEFRAMING_MORE_NEEDED;
    }
    Fw::Buffer buffer = m_interface->allocate(size);
    // Some allocators may return buffers larger than requested.
    // That causes issues in routing; adjust size.
    FW_ASSERT(buffer.getSize() >= size);
    buffer.setSize(size);
    ring.peek(buffer.getData(), size);
    m_interface->route(buffer);
    return DeframingProtocol::DEFRAMING_STATUS_SUCCESS;
}
};
