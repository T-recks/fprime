// ======================================================================
// \title  STCP.cpp
// \author T-recks
// \brief  cpp file for StcpProtocol class
//
// \copyright
// Copyright 2009-2022, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <limits>

#include "STCP.hpp"


namespace Svc {

StcpFraming::StcpFraming(): FramingProtocol() {}

StcpDeframing::StcpDeframing(): DeframingProtocol() {}

void StcpFraming::frame(const U8* const data, const U32 size, Fw::ComPacket::ComPacketType packet_type) {
    FW_ASSERT(data != nullptr);
    FW_ASSERT(m_interface != nullptr);
    // Use of I32 size is explicit as ComPacketType will be specifically serialized as an I32
    StcpFrameHeader::TokenType real_data_size = size + ((packet_type != Fw::ComPacket::FW_PACKET_UNKNOWN) ? sizeof(I32) : 0);
    StcpFrameHeader::TokenType total = real_data_size + StcpFrameHeader::SIZE;
    Fw::Buffer buffer = m_interface->allocate(total);
    Fw::SerializeBufferBase& serializer = buffer.getSerializeRepr();
    
    // Serialize data
    Fw::SerializeStatus status;
    
    status = serializer.serialize(real_data_size);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    // Serialize packet type if supplied, otherwise it *must* be present in the data
    if (packet_type != Fw::ComPacket::FW_PACKET_UNKNOWN) {
        status = serializer.serialize(static_cast<I32>(packet_type)); // I32 used for enum storage
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    }
    
    status = serializer.serialize(data, size, true);  // Serialize without length
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    buffer.setSize(total);

    m_interface->send(buffer);
}

bool StcpDeframing::validate(Types::CircularBuffer& ring, U32 size) {
    return true;
}

DeframingProtocol::DeframingStatus StcpDeframing::deframe(Types::CircularBuffer& ring, U32& needed) {
    StcpFrameHeader::TokenType start = 0;
    StcpFrameHeader::TokenType size = 0;
    FW_ASSERT(m_interface != nullptr);
    // Check for header or ask for more data
    if (ring.get_allocated_size() < StcpFrameHeader::SIZE) {
        needed = StcpFrameHeader::SIZE;
        return DeframingProtocol::DEFRAMING_MORE_NEEDED;
    }
    // Read size from header
    Fw::SerializeStatus status = ring.peek(size, 0);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    const U32 maxU32 = std::numeric_limits<U32>::max();
    if (size > maxU32 - (StcpFrameHeader::SIZE)) {
        // Size is too large to process: needed would overflow
        return DeframingProtocol::DEFRAMING_INVALID_SIZE;
    }
    needed = (StcpFrameHeader::SIZE + size);
    // Check frame size
    const U32 frameSize = size + StcpFrameHeader::SIZE;
    if (frameSize > ring.get_capacity()) {
        // Frame size is too large for ring buffer
        return DeframingProtocol::DEFRAMING_INVALID_SIZE;
    }
    // Check for enough data to deserialize everything;
    // otherwise break and wait for more.
    else if (ring.get_allocated_size() < needed) {
        return DeframingProtocol::DEFRAMING_MORE_NEEDED;
    }
    // Check the checksum
    if (not this->validate(ring, needed)) {
        return DeframingProtocol::DEFRAMING_INVALID_CHECKSUM;
    }
    Fw::Buffer buffer = m_interface->allocate(size);
    // Some allocators may return buffers larger than requested.
    // That causes issues in routing; adjust size.
    FW_ASSERT(buffer.getSize() >= size);
    buffer.setSize(size);
    ring.peek(buffer.getData(), size, StcpFrameHeader::SIZE);
    m_interface->route(buffer);
    return DeframingProtocol::DEFRAMING_STATUS_SUCCESS;
}
};
