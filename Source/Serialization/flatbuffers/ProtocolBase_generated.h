// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PROTOCOLBASE_PROTOCOL_H_
#define FLATBUFFERS_GENERATED_PROTOCOLBASE_PROTOCOL_H_

#include "flatbuffers/flatbuffers.h"

#include "AServerProtocol_generated.h"
#include "BServerProtocol_generated.h"

namespace Protocol {

struct Protocol;
struct ProtocolBuilder;

enum Message : uint8_t {
  Message_NONE = 0,
  Message_RequestSomeThing = 1,
  Message_ResponseSomThing = 2,
  Message_RequestAttack = 3,
  Message_ResponseAttack = 4,
  Message_MIN = Message_NONE,
  Message_MAX = Message_ResponseAttack
};

inline const Message (&EnumValuesMessage())[5] {
  static const Message values[] = {
    Message_NONE,
    Message_RequestSomeThing,
    Message_ResponseSomThing,
    Message_RequestAttack,
    Message_ResponseAttack
  };
  return values;
}

inline const char * const *EnumNamesMessage() {
  static const char * const names[6] = {
    "NONE",
    "RequestSomeThing",
    "ResponseSomThing",
    "RequestAttack",
    "ResponseAttack",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessage(Message e) {
  if (flatbuffers::IsOutRange(e, Message_NONE, Message_ResponseAttack)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesMessage()[index];
}

template<typename T> struct MessageTraits {
  static const Message enum_value = Message_NONE;
};

template<> struct MessageTraits<Protocol::RequestSomeThing> {
  static const Message enum_value = Message_RequestSomeThing;
};

template<> struct MessageTraits<Protocol::ResponseSomThing> {
  static const Message enum_value = Message_ResponseSomThing;
};

template<> struct MessageTraits<Protocol::RequestAttack> {
  static const Message enum_value = Message_RequestAttack;
};

template<> struct MessageTraits<Protocol::ResponseAttack> {
  static const Message enum_value = Message_ResponseAttack;
};

bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type);
bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct Protocol FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ProtocolBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BODY_TYPE = 4,
    VT_BODY = 6
  };
  Protocol::Message body_type() const {
    return static_cast<Protocol::Message>(GetField<uint8_t>(VT_BODY_TYPE, 0));
  }
  const void *body() const {
    return GetPointer<const void *>(VT_BODY);
  }
  template<typename T> const T *body_as() const;
  const Protocol::RequestSomeThing *body_as_RequestSomeThing() const {
    return body_type() == Protocol::Message_RequestSomeThing ? static_cast<const Protocol::RequestSomeThing *>(body()) : nullptr;
  }
  const Protocol::ResponseSomThing *body_as_ResponseSomThing() const {
    return body_type() == Protocol::Message_ResponseSomThing ? static_cast<const Protocol::ResponseSomThing *>(body()) : nullptr;
  }
  const Protocol::RequestAttack *body_as_RequestAttack() const {
    return body_type() == Protocol::Message_RequestAttack ? static_cast<const Protocol::RequestAttack *>(body()) : nullptr;
  }
  const Protocol::ResponseAttack *body_as_ResponseAttack() const {
    return body_type() == Protocol::Message_ResponseAttack ? static_cast<const Protocol::ResponseAttack *>(body()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_BODY_TYPE) &&
           VerifyOffset(verifier, VT_BODY) &&
           VerifyMessage(verifier, body(), body_type()) &&
           verifier.EndTable();
  }
};

template<> inline const Protocol::RequestSomeThing *Protocol::body_as<Protocol::RequestSomeThing>() const {
  return body_as_RequestSomeThing();
}

template<> inline const Protocol::ResponseSomThing *Protocol::body_as<Protocol::ResponseSomThing>() const {
  return body_as_ResponseSomThing();
}

template<> inline const Protocol::RequestAttack *Protocol::body_as<Protocol::RequestAttack>() const {
  return body_as_RequestAttack();
}

template<> inline const Protocol::ResponseAttack *Protocol::body_as<Protocol::ResponseAttack>() const {
  return body_as_ResponseAttack();
}

struct ProtocolBuilder {
  typedef Protocol Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_body_type(Protocol::Message body_type) {
    fbb_.AddElement<uint8_t>(Protocol::VT_BODY_TYPE, static_cast<uint8_t>(body_type), 0);
  }
  void add_body(flatbuffers::Offset<void> body) {
    fbb_.AddOffset(Protocol::VT_BODY, body);
  }
  explicit ProtocolBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Protocol> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Protocol>(end);
    return o;
  }
};

inline flatbuffers::Offset<Protocol> CreateProtocol(
    flatbuffers::FlatBufferBuilder &_fbb,
    Protocol::Message body_type = Protocol::Message_NONE,
    flatbuffers::Offset<void> body = 0) {
  ProtocolBuilder builder_(_fbb);
  builder_.add_body(body);
  builder_.add_body_type(body_type);
  return builder_.Finish();
}

inline bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type) {
  switch (type) {
    case Message_NONE: {
      return true;
    }
    case Message_RequestSomeThing: {
      auto ptr = reinterpret_cast<const Protocol::RequestSomeThing *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_ResponseSomThing: {
      auto ptr = reinterpret_cast<const Protocol::ResponseSomThing *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_RequestAttack: {
      auto ptr = reinterpret_cast<const Protocol::RequestAttack *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_ResponseAttack: {
      auto ptr = reinterpret_cast<const Protocol::ResponseAttack *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyMessage(
        verifier,  values->Get(i), types->GetEnum<Message>(i))) {
      return false;
    }
  }
  return true;
}

inline const Protocol::Protocol *GetProtocol(const void *buf) {
  return flatbuffers::GetRoot<Protocol::Protocol>(buf);
}

inline const Protocol::Protocol *GetSizePrefixedProtocol(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<Protocol::Protocol>(buf);
}

inline bool VerifyProtocolBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<Protocol::Protocol>(nullptr);
}

inline bool VerifySizePrefixedProtocolBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<Protocol::Protocol>(nullptr);
}

inline void FinishProtocolBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Protocol::Protocol> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedProtocolBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<Protocol::Protocol> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace Protocol

#endif  // FLATBUFFERS_GENERATED_PROTOCOLBASE_PROTOCOL_H_
