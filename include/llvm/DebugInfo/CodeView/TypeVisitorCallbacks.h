//===- TypeVisitorCallbacks.h -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_CODEVIEW_TYPEVISITORCALLBACKS_H
#define LLVM_DEBUGINFO_CODEVIEW_TYPEVISITORCALLBACKS_H

#include "llvm/DebugInfo/CodeView/TypeRecord.h"
#include "llvm/Support/Error.h"

namespace llvm {
namespace codeview {

class TypeVisitorCallbacks {
public:
  virtual ~TypeVisitorCallbacks() = default;

  /// Action to take on unknown types. By default, they are ignored.
  virtual Error visitUnknownType(CVType &Record) { return Error::success(); }
  /// Paired begin/end actions for all types. Receives all record data,
  /// including the fixed-length record prefix.  visitTypeBegin() should return
  /// the type of the Record, or an error if it cannot be determined.  Exactly
  /// one of the two visitTypeBegin methods will be called, depending on whether
  /// records are being visited sequentially or randomly.  An implementation
  /// should be prepared to handle both (or assert if it can't handle random
  /// access visitation).
  virtual Error visitTypeBegin(CVType &Record) { return Error::success(); }
  virtual Error visitTypeBegin(CVType &Record, TypeIndex Index) {
    return Error::success();
  }
  virtual Error visitTypeEnd(CVType &Record) { return Error::success(); }

  virtual Error visitUnknownMember(CVMemberRecord &Record) {
    return Error::success();
  }

  virtual Error visitMemberBegin(CVMemberRecord &Record) {
    return Error::success();
  }

  virtual Error visitMemberEnd(CVMemberRecord &Record) {
    return Error::success();
  }

#define TYPE_RECORD(EnumName, EnumVal, Name)                                   \
  virtual Error visitKnownRecord(CVType &CVR, Name##Record &Record) {          \
    return Error::success();                                                   \
  }
#define MEMBER_RECORD(EnumName, EnumVal, Name)                                 \
  virtual Error visitKnownMember(CVMemberRecord &CVM, Name##Record &Record) {  \
    return Error::success();                                                   \
  }

#define TYPE_RECORD_ALIAS(EnumName, EnumVal, Name, AliasName)
#define MEMBER_RECORD_ALIAS(EnumName, EnumVal, Name, AliasName)
#include "TypeRecords.def"
};

} // end namespace codeview
} // end namespace llvm

#endif // LLVM_DEBUGINFO_CODEVIEW_TYPEVISITORCALLBACKS_H
