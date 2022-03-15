// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SCHEMATEST_MYGAME_H_
#define FLATBUFFERS_GENERATED_SCHEMATEST_MYGAME_H_

#include "flatbuffers/flatbuffers.h"

namespace MyGame {

struct Vec3;

struct Monster;
struct MonsterBuilder;

struct RequestSomeThing;
struct RequestSomeThingBuilder;

struct ResponseSomThing;
struct ResponseSomThingBuilder;

struct Protocol;
struct ProtocolBuilder;

enum Color : int8_t {
  Color_Red = 1,
  Color_Green = 2,
  Color_Blue = 3,
  Color_MIN = Color_Red,
  Color_MAX = Color_Blue
};

inline const Color (&EnumValuesColor())[3] {
  static const Color values[] = {
    Color_Red,
    Color_Green,
    Color_Blue
  };
  return values;
}

inline const char * const *EnumNamesColor() {
  static const char * const names[4] = {
    "Red",
    "Green",
    "Blue",
    nullptr
  };
  return names;
}

inline const char *EnumNameColor(Color e) {
  if (flatbuffers::IsOutRange(e, Color_Red, Color_Blue)) return "";
  const size_t index = static_cast<size_t>(e) - static_cast<size_t>(Color_Red);
  return EnumNamesColor()[index];
}

enum Message : uint8_t {
  Message_NONE = 0,
  Message_RequestSomeThing = 1,
  Message_ResponseSomThing = 2,
  Message_MIN = Message_NONE,
  Message_MAX = Message_ResponseSomThing
};

inline const Message (&EnumValuesMessage())[3] {
  static const Message values[] = {
    Message_NONE,
    Message_RequestSomeThing,
    Message_ResponseSomThing
  };
  return values;
}

inline const char * const *EnumNamesMessage() {
  static const char * const names[4] = {
    "NONE",
    "RequestSomeThing",
    "ResponseSomThing",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessage(Message e) {
  if (flatbuffers::IsOutRange(e, Message_NONE, Message_ResponseSomThing)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesMessage()[index];
}

template<typename T> struct MessageTraits {
  static const Message enum_value = Message_NONE;
};

template<> struct MessageTraits<MyGame::RequestSomeThing> {
  static const Message enum_value = Message_RequestSomeThing;
};

template<> struct MessageTraits<MyGame::ResponseSomThing> {
  static const Message enum_value = Message_ResponseSomThing;
};

bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type);
bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  Vec3()
      : x_(0),
        y_(0),
        z_(0) {
  }
  Vec3(float _x, float _y, float _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(Vec3, 12);

struct Monster FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MonsterBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POS = 4,
    VT_MANA = 6,
    VT_HP = 8,
    VT_NAME = 10,
    VT_INVENTORY = 14,
    VT_COLOR = 16
  };
  const MyGame::Vec3 *pos() const {
    return GetStruct<const MyGame::Vec3 *>(VT_POS);
  }
  int16_t mana() const {
    return GetField<int16_t>(VT_MANA, 150);
  }
  int16_t hp() const {
    return GetField<int16_t>(VT_HP, 100);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::Vector<uint8_t> *inventory() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_INVENTORY);
  }
  MyGame::Color color() const {
    return static_cast<MyGame::Color>(GetField<int8_t>(VT_COLOR, 3));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<MyGame::Vec3>(verifier, VT_POS) &&
           VerifyField<int16_t>(verifier, VT_MANA) &&
           VerifyField<int16_t>(verifier, VT_HP) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_INVENTORY) &&
           verifier.VerifyVector(inventory()) &&
           VerifyField<int8_t>(verifier, VT_COLOR) &&
           verifier.EndTable();
  }
};

struct MonsterBuilder {
  typedef Monster Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_pos(const MyGame::Vec3 *pos) {
    fbb_.AddStruct(Monster::VT_POS, pos);
  }
  void add_mana(int16_t mana) {
    fbb_.AddElement<int16_t>(Monster::VT_MANA, mana, 150);
  }
  void add_hp(int16_t hp) {
    fbb_.AddElement<int16_t>(Monster::VT_HP, hp, 100);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Monster::VT_NAME, name);
  }
  void add_inventory(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> inventory) {
    fbb_.AddOffset(Monster::VT_INVENTORY, inventory);
  }
  void add_color(MyGame::Color color) {
    fbb_.AddElement<int8_t>(Monster::VT_COLOR, static_cast<int8_t>(color), 3);
  }
  explicit MonsterBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Monster> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Monster>(end);
    return o;
  }
};

inline flatbuffers::Offset<Monster> CreateMonster(
    flatbuffers::FlatBufferBuilder &_fbb,
    const MyGame::Vec3 *pos = 0,
    int16_t mana = 150,
    int16_t hp = 100,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> inventory = 0,
    MyGame::Color color = MyGame::Color_Blue) {
  MonsterBuilder builder_(_fbb);
  builder_.add_inventory(inventory);
  builder_.add_name(name);
  builder_.add_pos(pos);
  builder_.add_hp(hp);
  builder_.add_mana(mana);
  builder_.add_color(color);
  return builder_.Finish();
}

inline flatbuffers::Offset<Monster> CreateMonsterDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const MyGame::Vec3 *pos = 0,
    int16_t mana = 150,
    int16_t hp = 100,
    const char *name = nullptr,
    const std::vector<uint8_t> *inventory = nullptr,
    MyGame::Color color = MyGame::Color_Blue) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto inventory__ = inventory ? _fbb.CreateVector<uint8_t>(*inventory) : 0;
  return MyGame::CreateMonster(
      _fbb,
      pos,
      mana,
      hp,
      name__,
      inventory__,
      color);
}

struct RequestSomeThing FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RequestSomeThingBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_REQUESTSTRING = 4
  };
  const flatbuffers::String *RequestString() const {
    return GetPointer<const flatbuffers::String *>(VT_REQUESTSTRING);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_REQUESTSTRING) &&
           verifier.VerifyString(RequestString()) &&
           verifier.EndTable();
  }
};

struct RequestSomeThingBuilder {
  typedef RequestSomeThing Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_RequestString(flatbuffers::Offset<flatbuffers::String> RequestString) {
    fbb_.AddOffset(RequestSomeThing::VT_REQUESTSTRING, RequestString);
  }
  explicit RequestSomeThingBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<RequestSomeThing> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RequestSomeThing>(end);
    return o;
  }
};

inline flatbuffers::Offset<RequestSomeThing> CreateRequestSomeThing(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> RequestString = 0) {
  RequestSomeThingBuilder builder_(_fbb);
  builder_.add_RequestString(RequestString);
  return builder_.Finish();
}

inline flatbuffers::Offset<RequestSomeThing> CreateRequestSomeThingDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *RequestString = nullptr) {
  auto RequestString__ = RequestString ? _fbb.CreateString(RequestString) : 0;
  return MyGame::CreateRequestSomeThing(
      _fbb,
      RequestString__);
}

struct ResponseSomThing FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ResponseSomThingBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RESPONSESTRING = 4
  };
  const flatbuffers::String *ResponseString() const {
    return GetPointer<const flatbuffers::String *>(VT_RESPONSESTRING);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_RESPONSESTRING) &&
           verifier.VerifyString(ResponseString()) &&
           verifier.EndTable();
  }
};

struct ResponseSomThingBuilder {
  typedef ResponseSomThing Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_ResponseString(flatbuffers::Offset<flatbuffers::String> ResponseString) {
    fbb_.AddOffset(ResponseSomThing::VT_RESPONSESTRING, ResponseString);
  }
  explicit ResponseSomThingBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ResponseSomThing> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ResponseSomThing>(end);
    return o;
  }
};

inline flatbuffers::Offset<ResponseSomThing> CreateResponseSomThing(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> ResponseString = 0) {
  ResponseSomThingBuilder builder_(_fbb);
  builder_.add_ResponseString(ResponseString);
  return builder_.Finish();
}

inline flatbuffers::Offset<ResponseSomThing> CreateResponseSomThingDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *ResponseString = nullptr) {
  auto ResponseString__ = ResponseString ? _fbb.CreateString(ResponseString) : 0;
  return MyGame::CreateResponseSomThing(
      _fbb,
      ResponseString__);
}

struct Protocol FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ProtocolBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_BODY_TYPE = 4,
    VT_BODY = 6
  };
  MyGame::Message body_type() const {
    return static_cast<MyGame::Message>(GetField<uint8_t>(VT_BODY_TYPE, 0));
  }
  const void *body() const {
    return GetPointer<const void *>(VT_BODY);
  }
  template<typename T> const T *body_as() const;
  const MyGame::RequestSomeThing *body_as_RequestSomeThing() const {
    return body_type() == MyGame::Message_RequestSomeThing ? static_cast<const MyGame::RequestSomeThing *>(body()) : nullptr;
  }
  const MyGame::ResponseSomThing *body_as_ResponseSomThing() const {
    return body_type() == MyGame::Message_ResponseSomThing ? static_cast<const MyGame::ResponseSomThing *>(body()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_BODY_TYPE) &&
           VerifyOffset(verifier, VT_BODY) &&
           VerifyMessage(verifier, body(), body_type()) &&
           verifier.EndTable();
  }
};

template<> inline const MyGame::RequestSomeThing *Protocol::body_as<MyGame::RequestSomeThing>() const {
  return body_as_RequestSomeThing();
}

template<> inline const MyGame::ResponseSomThing *Protocol::body_as<MyGame::ResponseSomThing>() const {
  return body_as_ResponseSomThing();
}

struct ProtocolBuilder {
  typedef Protocol Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_body_type(MyGame::Message body_type) {
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
    MyGame::Message body_type = MyGame::Message_NONE,
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
      auto ptr = reinterpret_cast<const MyGame::RequestSomeThing *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_ResponseSomThing: {
      auto ptr = reinterpret_cast<const MyGame::ResponseSomThing *>(obj);
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

inline const MyGame::Protocol *GetProtocol(const void *buf) {
  return flatbuffers::GetRoot<MyGame::Protocol>(buf);
}

inline const MyGame::Protocol *GetSizePrefixedProtocol(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<MyGame::Protocol>(buf);
}

inline const char *ProtocolIdentifier() {
  return "PTTT";
}

inline bool ProtocolBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, ProtocolIdentifier());
}

inline bool VerifyProtocolBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MyGame::Protocol>(ProtocolIdentifier());
}

inline bool VerifySizePrefixedProtocolBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<MyGame::Protocol>(ProtocolIdentifier());
}

inline void FinishProtocolBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyGame::Protocol> root) {
  fbb.Finish(root, ProtocolIdentifier());
}

inline void FinishSizePrefixedProtocolBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyGame::Protocol> root) {
  fbb.FinishSizePrefixed(root, ProtocolIdentifier());
}

}  // namespace MyGame

#endif  // FLATBUFFERS_GENERATED_SCHEMATEST_MYGAME_H_
