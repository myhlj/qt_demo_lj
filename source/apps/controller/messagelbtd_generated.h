﻿// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_MESSAGELBTD_LBTDMESSAGE_H_
#define FLATBUFFERS_GENERATED_MESSAGELBTD_LBTDMESSAGE_H_

#include "flatbuffers/flatbuffers.h"

namespace LBTDMessage {

struct MessageLBTD;

/// 消息类型
enum MessType {
  /// 开门
  MessType_OPENGATE = 1,
  /// 常开
  MessType_SETGATE = 2,
  /// 关机
  MessType_CLOSETEMINAL = 3,
  /// 重启
  MessType_RESTART = 4,
  /// 验证模式切换
  MessType_VERIFYMODE = 5,
  /// 增加曝光
  MessType_ADDEXPOSE = 6,
  /// 减少曝光
  MessType_MINUSEXPOSE = 7,
  /// 更新参数
  MessType_UPDATAPARAM = 8,
  /// 退出当前系统
  MessType_EXIT = 9,
  MessType_MIN = MessType_OPENGATE,
  MessType_MAX = MessType_EXIT
};

inline const char **EnumNamesMessType() {
  static const char *names[] = { "OPENGATE", "SETGATE", "CLOSETEMINAL", "RESTART", "VERIFYMODE", "ADDEXPOSE", "MINUSEXPOSE", "UPDATAPARAM", "EXIT", nullptr };
  return names;
}

inline const char *EnumNameMessType(MessType e) { return EnumNamesMessType()[static_cast<int>(e) - static_cast<int>(MessType_OPENGATE)]; }

/// 左键按下消息控制闸机核验端
struct MessageLBTD FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SIGN = 4,
    VT_MESSAGETYPE = 6,
    VT_PARAML = 8,
    VT_PARAMR = 10
  };
  /// 暂时固定值："HisignMess"
  const flatbuffers::String *sign() const { return GetPointer<const flatbuffers::String *>(VT_SIGN); }
  flatbuffers::String *mutable_sign() { return GetPointer<flatbuffers::String *>(VT_SIGN); }
  /// 消息类型
  MessType messageType() const { return static_cast<MessType>(GetField<int32_t>(VT_MESSAGETYPE, 1)); }
  bool mutate_messageType(MessType _messageType) { return SetField(VT_MESSAGETYPE, static_cast<int32_t>(_messageType)); }
  /// 当消息类型为常开模式时，1：设置常开；0：取消常开
  /// 当消息类型为验证模式时，1：比对人脸模式；0：证件模式
  int32_t paramL() const { return GetField<int32_t>(VT_PARAML, 0); }
  bool mutate_paramL(int32_t _paramL) { return SetField(VT_PARAML, _paramL); }
  /// 参数
  const flatbuffers::String *paramR() const { return GetPointer<const flatbuffers::String *>(VT_PARAMR); }
  flatbuffers::String *mutable_paramR() { return GetPointer<flatbuffers::String *>(VT_PARAMR); }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SIGN) &&
           verifier.Verify(sign()) &&
           VerifyField<int32_t>(verifier, VT_MESSAGETYPE) &&
           VerifyField<int32_t>(verifier, VT_PARAML) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_PARAMR) &&
           verifier.Verify(paramR()) &&
           verifier.EndTable();
  }
};

struct MessageLBTDBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_sign(flatbuffers::Offset<flatbuffers::String> sign) { fbb_.AddOffset(MessageLBTD::VT_SIGN, sign); }
  void add_messageType(MessType messageType) { fbb_.AddElement<int32_t>(MessageLBTD::VT_MESSAGETYPE, static_cast<int32_t>(messageType), 1); }
  void add_paramL(int32_t paramL) { fbb_.AddElement<int32_t>(MessageLBTD::VT_PARAML, paramL, 0); }
  void add_paramR(flatbuffers::Offset<flatbuffers::String> paramR) { fbb_.AddOffset(MessageLBTD::VT_PARAMR, paramR); }
  MessageLBTDBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
  MessageLBTDBuilder &operator=(const MessageLBTDBuilder &);
  flatbuffers::Offset<MessageLBTD> Finish() {
    auto o = flatbuffers::Offset<MessageLBTD>(fbb_.EndTable(start_, 4));
    return o;
  }
};

inline flatbuffers::Offset<MessageLBTD> CreateMessageLBTD(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> sign = 0,
    MessType messageType = MessType_OPENGATE,
    int32_t paramL = 0,
    flatbuffers::Offset<flatbuffers::String> paramR = 0) {
  MessageLBTDBuilder builder_(_fbb);
  builder_.add_paramR(paramR);
  builder_.add_paramL(paramL);
  builder_.add_messageType(messageType);
  builder_.add_sign(sign);
  return builder_.Finish();
}

inline flatbuffers::Offset<MessageLBTD> CreateMessageLBTDDirect(flatbuffers::FlatBufferBuilder &_fbb,
    const char *sign = nullptr,
    MessType messageType = MessType_OPENGATE,
    int32_t paramL = 0,
    const char *paramR = nullptr) {
  return CreateMessageLBTD(_fbb, sign ? _fbb.CreateString(sign) : 0, messageType, paramL, paramR ? _fbb.CreateString(paramR) : 0);
}

inline const LBTDMessage::MessageLBTD *GetMessageLBTD(const void *buf) { return flatbuffers::GetRoot<LBTDMessage::MessageLBTD>(buf); }

inline MessageLBTD *GetMutableMessageLBTD(void *buf) { return flatbuffers::GetMutableRoot<MessageLBTD>(buf); }

inline bool VerifyMessageLBTDBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<LBTDMessage::MessageLBTD>(nullptr); }

inline void FinishMessageLBTDBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<LBTDMessage::MessageLBTD> root) { fbb.Finish(root); }

}  // namespace LBTDMessage

#endif  // FLATBUFFERS_GENERATED_MESSAGELBTD_LBTDMESSAGE_H_
