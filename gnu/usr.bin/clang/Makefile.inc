# $OpenBSD: Makefile.inc,v 1.1 2016/09/05 10:56:48 pascal Exp $

LLVM_SRCS?=	${.CURDIR}/../../../llvm

CC=		egcc
CXX=		eg++

DEBUG=
NOPIE=

CLANG_INCLUDES=	-I${LLVM_SRCS}/tools/clang/include
CPPFLAGS+=	-I${LLVM_SRCS}/include -I${.CURDIR}/../include -I${.OBJDIR} \
		-I${.OBJDIR}/../include
CPPFLAGS+=	-DNDEBUG
CPPFLAGS+=	-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS \
		-D__STDC_FORMAT_MACROS

TRIPLE=		${MACHINE_ARCH}-unknown-openbsd${OSREV}
CPPFLAGS+=	-DLLVM_DEFAULT_TARGET_TRIPLE=\"${TRIPLE}\"
CPPFLAGS+=	-DLLVM_HOST_TRIPLE=\"${TRIPLE}\"
CPPFLAGS+=	-DLLVM_PREFIX=\"/usr\"
.include "Makefile.arch"
CPPFLAGS+=-DLLVM_NATIVE_ARCH=\"${LLVM_ARCH}\"
CPPFLAGS+=-DLLVM_NATIVE_ASMPARSER=LLVMInitialize${LLVM_ARCH}AsmParser
CPPFLAGS+=-DLLVM_NATIVE_ASMPRINTER=LLVMInitialize${LLVM_ARCH}AsmPrinter
CPPFLAGS+=-DLLVM_NATIVE_DISASSEMBLER=LLVMInitialize${LLVM_ARCH}Disassembler
CPPFLAGS+=-DLLVM_NATIVE_TARGET=LLVMInitialize${LLVM_ARCH}Target
CPPFLAGS+=-DLLVM_NATIVE_TARGETINFO=LLVMInitialize${LLVM_ARCH}TargetInfo
CPPFLAGS+=-DLLVM_NATIVE_TARGETMC=LLVMInitialize${LLVM_ARCH}TargetMC

# upstream defaults
CFLAGS+=	-ffunction-sections
.if ${MACHINE_ARCH} != "powerpc"
# XXX
CFLAGS+=        -fdata-sections
.endif
CXXFLAGS+=	-std=c++11
CXXFLAGS+=	-fvisibility-inlines-hidden
CXXFLAGS+=	-fno-exceptions -fno-rtti
# warnings (from upstream)
CXXFLAGS+=	-Wall -W -Wno-unused-parameter -Wwrite-strings -Wcast-qual \
		-Wno-missing-field-initializers -pedantic -Wno-long-long \
		-Wdelete-non-virtual-dtor -Wno-comment

.for lib in ${LLVM_LIBDEPS}
DPADD+=	${.OBJDIR}/../lib${lib}/lib${lib}.a
LDADD+=	${.OBJDIR}/../lib${lib}/lib${lib}.a
.endfor