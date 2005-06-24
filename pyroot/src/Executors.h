// @(#)root/pyroot:$Name:  $:$Id: Executors.h,v 1.4 2005/06/02 10:03:17 brun Exp $
// Author: Wim Lavrijsen, Jan 2005
#ifndef PYROOT_EXECUTORS_H
#define PYROOT_EXECUTORS_H

// ROOT
#include "DllImport.h"
#include "TClassRef.h"

// CINT
class G__CallFunc;

// Standard
#include <string>
#include <map>


namespace PyROOT {

/** Executors of CINT calls and conversions back to python
      @author  WLAV
      @date    01/27/2005
      @version 1.0
*/

   class Executor {
   public:
      virtual ~Executor() {}
      virtual PyObject* Execute( G__CallFunc*, void* ) = 0;
   };

#define PYROOT_DECLARE_BASIC_EXECUTOR( name )                                 \
   class name##Executor : public Executor {                                   \
   public:                                                                    \
      virtual PyObject* Execute( G__CallFunc*, void* );                       \
   }

// executors for built-ins
   PYROOT_DECLARE_BASIC_EXECUTOR( Long );
   PYROOT_DECLARE_BASIC_EXECUTOR( Char );
   PYROOT_DECLARE_BASIC_EXECUTOR( Int );
   PYROOT_DECLARE_BASIC_EXECUTOR( ULong );
   PYROOT_DECLARE_BASIC_EXECUTOR( LongLong );
   PYROOT_DECLARE_BASIC_EXECUTOR( Double );
   PYROOT_DECLARE_BASIC_EXECUTOR( Void );
   PYROOT_DECLARE_BASIC_EXECUTOR( CString );

// pointer/array executors
   PYROOT_DECLARE_BASIC_EXECUTOR( VoidArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( ShortArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( UShortArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( IntArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( UIntArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( LongArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( ULongArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( FloatArray );
   PYROOT_DECLARE_BASIC_EXECUTOR( DoubleArray );

// special cases
   PYROOT_DECLARE_BASIC_EXECUTOR( STLString );
   PYROOT_DECLARE_BASIC_EXECUTOR( TGlobal );

   class RootObjectExecutor : public Executor {
   public:
      RootObjectExecutor( const TClassRef& klass ) : fClass( klass ) {}
      virtual PyObject* Execute( G__CallFunc*, void* );

   protected:
      TClassRef fClass;
   };

   class RootObjectByValueExecutor : public RootObjectExecutor {
   public:
      RootObjectByValueExecutor( const TClassRef& klass ) : RootObjectExecutor ( klass ) {}
      virtual PyObject* Execute( G__CallFunc*, void* );
   };

   PYROOT_DECLARE_BASIC_EXECUTOR( Constructor );

// factories
   typedef Executor* (*ExecutorFactory_t) ();
   typedef std::map< std::string, ExecutorFactory_t > ExecFactories_t;
   R__EXTERN ExecFactories_t gExecFactories;

// create executor from fully qualified type
   Executor* CreateExecutor( const std::string& fullType );

} // namespace PyROOT

#endif // !PYROOT_EXECUTORS_H
