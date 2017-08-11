// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
// Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 5/26/17.

#ifndef ZAPI_DS_VARIANT_H
#define ZAPI_DS_VARIANT_H

#include "zapi/Global.h"
#include "zapi/lang/Type.h"

#include <vector>
#include <map>
#include <cstring>
#include <string>

namespace zapi
{

// forward declare with namespace
namespace lang
{
class StdClass;
} // lang

namespace ds
{

namespace internal
{
class VariantPrivate;
}

using internal::VariantPrivate;
using zapi::lang::StdClass;
using zapi::lang::Type;

class ZAPI_DECL_EXPORT Variant
{
public:
   /**
    * Empty constructor (value = NULL)
    */
   Variant();
   /**
    * Constructor for various types
    */
   Variant(std::nullptr_t value);
   Variant(std::int8_t value);
   Variant(std::int16_t value);
   Variant(std::int32_t value);
#if SIZEOF_ZEND_LONG == 8
   Variant(std::int64_t value);
#endif
   Variant(bool value);
   Variant(char value);
   Variant(const std::string &value);
   Variant(const char *value, size_t length);
   Variant(const char *value);
   Variant(double value);
   /**
    * Wrap object around zval
    * @param  zval Zval to wrap
    * @param  ref Force this to be a reference
    */
   Variant(_zval_struct *zval, bool isRef = false);
   
   /**
    * Copy constructor
    * @param  value
    */
   Variant(const Variant &other);
   
   /**
    * Move constructor
    * @param  value
    */
   Variant(Variant &&other) ZAPI_DECL_NOEXCEPT;
   
   /**
    * Destructor
    */
   virtual ~Variant() ZAPI_DECL_NOEXCEPT;
   
   /**
    * Move assignment
    * @param  value
    * @return Value
    */
   Variant &operator=(Variant &&value) ZAPI_DECL_NOEXCEPT;
   
   /**
    * Assignment operator for various types
    * @param  value
    * @return Value
    */
   Variant &operator=(std::nullptr_t value);
   Variant &operator=(const Variant &value);
   Variant &operator=(std::int8_t value);
   Variant &operator=(std::int16_t value);
   Variant &operator=(std::int32_t value);
#if SIZEOF_ZEND_LONG == 8
   Variant &operator=(std::int64_t value);
#endif
   Variant &operator=(bool value);
   Variant &operator=(char value);
   Variant &operator=(const std::string &value);
   Variant &operator=(const char *value);
   Variant &operator=(double value);
   Variant &operator=(zval *value);
   
   /**
    * Cast to a boolean
    * @return boolean
    */
   virtual operator bool () const
   {
      return toBool();
   }
   
   /**
    * Cast to a string
    * @return string
    */
   virtual operator std::string () const
   {
      return toString();
   }
   
   operator zval * () const;
   
   /**
    * The type of object
    * @return Type
    */
   Type getType() const ZAPI_DECL_NOEXCEPT;
   
   /**
    * Make a clone of the value with the same type
    * 
    * @return Value
    */
   Variant clone() const;
   
   /**
    * Check if the value is of a certain type
    * 
    * @return bool
    */
   bool isNull() const ZAPI_DECL_NOEXCEPT;
   bool isLong() const ZAPI_DECL_NOEXCEPT;
   bool isBool() const ZAPI_DECL_NOEXCEPT;
   bool isString() const ZAPI_DECL_NOEXCEPT;
   bool isDouble() const ZAPI_DECL_NOEXCEPT;
   bool isObject() const ZAPI_DECL_NOEXCEPT;
   bool isArray() const ZAPI_DECL_NOEXCEPT;
   bool isScalar() const ZAPI_DECL_NOEXCEPT
   {
      return isNull() || isLong() || isBool() || isString() || isDouble();
   }
   
   /**
    * Retrieve the value as boolean
    * 
    * @return bool
    */
   virtual bool toBool() const ZAPI_DECL_NOEXCEPT;
   
   /**
    * Retrieve the value as a string
    * 
    * @return string
    */
   virtual std::string toString() const ZAPI_DECL_NOEXCEPT;
   
   zval &getZval() ZAPI_DECL_NOEXCEPT;
   zval *getZvalPtr() ZAPI_DECL_NOEXCEPT;
   const zval *getZvalPtr() const ZAPI_DECL_NOEXCEPT;
   uint32_t getRefCount() const ZAPI_DECL_NOEXCEPT;
   zval detach(bool keeprefcount);
   Variant makeReference();
   bool isReference() const ZAPI_DECL_NOEXCEPT;
protected:
   static void stdCopyZval(zval *dest, zval *source);
   static void stdAssignZval(zval *dest, zval *source);
protected: 
   ZAPI_DECLARE_PRIVATE(Variant)
   std::shared_ptr<VariantPrivate> m_implPtr;
};

/**
 * Custom output stream operator
 * 
 * @param  stream
 * @param  value
 * @return ostream
 */
ZAPI_DECL_EXPORT std::ostream &operator<<(std::ostream &stream, const Variant &value);

} // ds
} // zapi

#endif //ZAPI_DS_VARIANT_H