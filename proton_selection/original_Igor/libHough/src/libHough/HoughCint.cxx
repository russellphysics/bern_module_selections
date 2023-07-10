// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HoughCint
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Hough.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Hough(void *p = 0);
   static void *newArray_Hough(Long_t size, void *p);
   static void delete_Hough(void *p);
   static void deleteArray_Hough(void *p);
   static void destruct_Hough(void *p);
   static void streamer_Hough(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Hough*)
   {
      ::Hough *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Hough >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Hough", ::Hough::Class_Version(), "Hough.h", 28,
                  typeid(::Hough), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Hough::Dictionary, isa_proxy, 16,
                  sizeof(::Hough) );
      instance.SetNew(&new_Hough);
      instance.SetNewArray(&newArray_Hough);
      instance.SetDelete(&delete_Hough);
      instance.SetDeleteArray(&deleteArray_Hough);
      instance.SetDestructor(&destruct_Hough);
      instance.SetStreamerFunc(&streamer_Hough);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Hough*)
   {
      return GenerateInitInstanceLocal((::Hough*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Hough*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Hough::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Hough::Class_Name()
{
   return "Hough";
}

//______________________________________________________________________________
const char *Hough::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Hough*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Hough::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Hough*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Hough::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Hough*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Hough::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Hough*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Hough::Streamer(TBuffer &R__b)
{
   // Stream an object of class Hough.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      vec_n.Streamer(R__b);
      vec_p.Streamer(R__b);
      R__b >> xyz;
      R__b >> tpr;
      R__b.CheckByteCount(R__s, R__c, Hough::IsA());
   } else {
      R__c = R__b.WriteVersion(Hough::IsA(), kTRUE);
      TObject::Streamer(R__b);
      vec_n.Streamer(R__b);
      vec_p.Streamer(R__b);
      R__b << (TObject*)xyz;
      R__b << (TObject*)tpr;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Hough(void *p) {
      return  p ? new(p) ::Hough : new ::Hough;
   }
   static void *newArray_Hough(Long_t nElements, void *p) {
      return p ? new(p) ::Hough[nElements] : new ::Hough[nElements];
   }
   // Wrapper around operator delete
   static void delete_Hough(void *p) {
      delete ((::Hough*)p);
   }
   static void deleteArray_Hough(void *p) {
      delete [] ((::Hough*)p);
   }
   static void destruct_Hough(void *p) {
      typedef ::Hough current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Hough(TBuffer &buf, void *obj) {
      ((::Hough*)obj)->::Hough::Streamer(buf);
   }
} // end of namespace ROOT for class ::Hough

namespace {
  void TriggerDictionaryInitialization_HoughCint_Impl() {
    static const char* headers[] = {
"Hough.h",
0
    };
    static const char* includePaths[] = {
"../../include",
"/home/daq/software/anaconda3/envs/larpixDAQ-38/include/",
"/home/daq/workspaces/igor/libHough/src/libHough/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "HoughCint dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate(R"ATTRDUMP(Hough Transform)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Hough.h")))  Hough;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HoughCint dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Hough.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Hough", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HoughCint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HoughCint_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HoughCint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HoughCint() {
  TriggerDictionaryInitialization_HoughCint_Impl();
}
