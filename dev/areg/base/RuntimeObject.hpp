#ifndef AREG_BASE_RUNTIMEOBJECT_HPP
#define AREG_BASE_RUNTIMEOBJECT_HPP
/************************************************************************
 * \file        areg/base/RuntimeObject.hpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit 
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG Platform Runtime Object class.
 *              All instances of Runtime Object may have individual
 *              class ID. To define class ID, use macro:
 *              DECLARE_RUNTIME and IMPLEMENT_RUNTIME
 *
 ************************************************************************/
/************************************************************************
 * Include files.
 ************************************************************************/
#include "areg/base/GEGlobal.h"
#include "areg/base/Object.hpp"
#include "areg/base/private/RuntimeBase.hpp"

#include "areg/base/RuntimeClassID.hpp"
#include "areg/base/NEUtilities.hpp"

/**
 * \brief       MACRO to declare Runtime Class ID in runtime object.
 *
 * \example     Runtime Class ID declaration via MACRO
 *
 *              In this small example the class MyClass is declared as Runtime Object
 *              predefined MACRO define Runtime Class ID, which is used in 
 *              function convert(). Function convert() returns valid pointer to 
 *              MyClass object if Runtime Object is an instance of MyClass.
 *              Otherwise it will return NULL.
 *
 *              class MyClass   : public RuntimeObject
 *              {
 *                  DECLARE_RUNTIME(MyClass)
 *              public:
 *                  MyClass( void );
 *                  ~MyClass( void );
 *              };
 *              IMPLEMENT_RUNTIME(MyClass, RuntimeObject)
 * 
 *              MyClass* convert(RuntimeObject& runtimeObj)
 *              {
 *                  return RUNTIME_CAST(&runtimeObj, MyClass);
 *              }
 **/

/************************************************************************/
// Runtime object MACRO definition. Begin
/************************************************************************/

/**
 * \brief   Declare this MACRO in your class to make runtime compatible
 *          Your class should be derived from RuntimeObject class.
 * \param   ClassName   The name of Runtime Class. Should not be string.
 * \example DECLARE_RUNTIME(MyClass)
 **/
//////////////////////////////////////////////////////////////////////////
// DECLARE_RUNTIME macro definition
//////////////////////////////////////////////////////////////////////////
#define DECLARE_RUNTIME(ClassName)                                                                      \
/*********************************************************************/                                 \
/** Static members and constants                                    **/                                 \
/*********************************************************************/                                 \
public:                                                                                                 \
    /** \brief   Returns RuntimeClassID object                      **/                                 \
    static const RuntimeClassID & _getClassId( void );                                                  \
/*********************************************************************/                                 \
/** RuntimeBase class overrides                                     **/                                 \
/*********************************************************************/                                 \
    /** \brief   Returns the Runtime Class Identifier object        **/                                 \
    virtual const RuntimeClassID & getRuntimeClassId( void ) const;                                     \
    /** \brief   Returns the class name (Identifier name)           **/                                 \
    virtual const char* getRuntimeClassName( void ) const;                                              \
    /** \brief   Returns the calculated number of runtime class.    **/                                 \
    virtual unsigned int getRuntimeClassNumber( void ) const;                                           \
    /** \brief   Checks class instance by Class Identifier          **/                                 \
    /**          Checking is done hiearchically and if any class    **/                                 \
    /**          in base hierarchi has same RuntimeClassID,         **/                                 \
    /**          returns true. Otherwise, return false.             **/                                 \
    /** \param   classId    The Class Identifier to check.          **/                                 \
    virtual bool isInstanceOfRuntimeClass(const RuntimeClassID & classId) const;                        \
    /** \brief   Checks class instance by given name                **/                                 \
    /**          Checking is done hiearchically and if any class    **/                                 \
    /**          in base hierarchi has same name, returns true.     **/                                 \
    /**          Otherwise, return false.                           **/                                 \
    /** \param   className  The name of class to check.             **/                                 \
    virtual bool isInstanceOfRuntimeClass(const char * className) const;                                \
    /** \brief   Checks class instance by name.                     **/                                 \
    /** \param   className   The name of class to check.            **/                                 \
    virtual bool isInstanceOfRuntimeClass( unsigned int classMagic ) const;                             \


/**
 * \brief   Use this MACRO in source code and specify the base class of Runtime Object.
 * \param   ClassName       The name of Runtime Class. Should not be string.
 * \param   BaseClassName   The name of base / parent class. Should not be string.
 * \example IMPLEMENT_RUNTIME(MyClass, RuntimeObject)
 **/
//////////////////////////////////////////////////////////////////////////
// IMPLEMENT_RUNTIME macro definition
//////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_RUNTIME(ClassName, BaseClassName)                                                             \
/** Return class identifier object **/                                                                          \
const RuntimeClassID & ClassName::_getClassId( void )                                                           \
{   static const RuntimeClassID _classId(#ClassName); return _classId;                                      }   \
/** Return class identifier object **/                                                                          \
const RuntimeClassID & ClassName::getRuntimeClassId( void ) const                                               \
{   return ClassName::_getClassId();                                                                        }   \
/** Return class name **/                                                                                       \
const char* ClassName::getRuntimeClassName( void ) const                                                        \
{   return ClassName::_getClassId().getName();                                                              }   \
/** Return calculated number **/                                                                                \
unsigned int ClassName::getRuntimeClassNumber( void ) const                                                     \
{   return ClassName::_getClassId().getMagic();                                                             }   \
/** Check class instance by Class Identifier **/                                                                \
bool ClassName::isInstanceOfRuntimeClass( const RuntimeClassID & classId ) const                                \
{   return ((ClassName::_getClassId() == classId) || BaseClassName::isInstanceOfRuntimeClass(classId));     }   \
/** Check class instance by name **/                                                                            \
bool ClassName::isInstanceOfRuntimeClass( const char * className ) const                                        \
{   return ((className == ClassName::_getClassId()) || BaseClassName::isInstanceOfRuntimeClass(className)); }   \
/** Check class instance by number **/                                                                          \
bool ClassName::isInstanceOfRuntimeClass( unsigned int classMagic ) const                                       \
{   return ((classMagic == ClassName::_getClassId()) || BaseClassName::isInstanceOfRuntimeClass(classMagic));   }

/**
 * \brief   Use MACRO in source code of class template and specify the base class. 
 *          class template function implementation.
 * \param   Template        The template type definition
 * \param   ClassName       The name of Runtime Class. Should not be string.
 * \param   BaseClassName   The name of base / parent class. Should not be string.
 * \param   ClassIdType     The template Runtime Class ID
 * \example IMPLEMENT_RUNTIME_TEMPLATE(template <class DATA_CLASS, class DATA_CLASS_TYPE>, MyClass<DATA_CLASS, DATA_CLASS_TYPE>, RuntimeObject, MyClass);
 **/
//////////////////////////////////////////////////////////////////////////
// IMPLEMENT_RUNTIME_TEMPLATE macro definition
//////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_RUNTIME_TEMPLATE(Template, ClassName, BaseClassName, ClassIdType)                             \
/** Return class identifier object **/                                                                          \
Template const RuntimeClassID & ClassName::_getClassId( void )                                                  \
{   static const RuntimeClassID _classId(#ClassName); return _classId;                                      }   \
/** Return class identifier object **/                                                                          \
Template const RuntimeClassID& ClassName::getRuntimeClassId( void ) const                                       \
{   return ClassName::_getClassId();                                                                        }   \
/** Return class name **/                                                                                       \
Template const char* ClassName::getRuntimeClassName( void ) const                                               \
{   return ClassName::_getClassId().getName();                                                              }   \
/** Return class number **/                                                                                     \
Template unsigned int ClassName::getRuntimeClassNumber( void ) const                                            \
{   return ClassName::_getClassId().getMagic();                                                             }   \
/** Check class instance by Class Identifier **/                                                                \
Template bool ClassName::isInstanceOfRuntimeClass( const RuntimeClassID & classId ) const                       \
{   return ((ClassName::_getClassId() == classId) || BaseClassName::isInstanceOfRuntimeClass(classId));     }   \
/** Check class instance by name**/                                                                             \
Template bool ClassName::isInstanceOfRuntimeClass( const char * className ) const                               \
{   return ((className == ClassName::_getClassId()) || BaseClassName::isInstanceOfRuntimeClass(className)); }   \
/** Check class instance by number **/                                                                          \
Template bool ClassName::isInstanceOfRuntimeClass( unsigned int classMagic ) const                              \
{   return ((classMagic == ClassName::_getClassId()) || BaseClassName::isInstanceOfRuntimeClass(classMagic));   }

/**
 * \brief   Use this MACRO to make exact object casting of instance of constant object during runtime.
 *          It returns pointer of object if the Runtime Class ID is matching to given ClassName
 *          object. Otherwise, it will return NULL pointer.
 * \param   ptr         Pointer to object
 * \param   ClassName   The name of class to cast
 **/
#define RUNTIME_CONST_EXACT_CAST(ptr, ClassName)    static_cast<const ClassName *>(::RuntimeCast(static_cast<const RuntimeObject *>(ptr), #ClassName))

/**
 * \brief   Use this MACRO to make fast casting of instance of constant object during runtime.
 *          It returns pointer of object if the Runtime Class ID is matching to given ClassName
 *          object. Otherwise, it will return NULL pointer.
 * \param   ptr         Pointer to object
 * \param   ClassName   The name of class to cast
 **/
#define RUNTIME_CONST_FAST_CAST(ptr, ClassName)     static_cast<const ClassName *>(::RuntimeCast(static_cast<const RuntimeObject *>(ptr), ClassName::_getClassId()))

/**
 * \brief   Use this MACRO to make casting of instance of constant object during runtime.
 *          It returns pointer of object if the Runtime Class ID is matching to given ClassName
 *          object. Otherwise, it will return NULL pointer.
 * \param   ptr         Pointer to object
 * \param   ClassName   The name of class to cast
 **/
#define RUNTIME_CONST_CAST(ptr, ClassName)          RUNTIME_CONST_FAST_CAST(ptr, ClassName)

/**
 * \brief   Use this MACRO to make fast casting of instance of object during runtime.
 *          It returns pointer of object if the Runtime Class ID is matching to given ClassName
 *          object. Otherwise, it will return NULL pointer.
 * \param   ptr         Pointer to object
 * \param   ClassName   The name of class to cast
 **/
#define RUNTIME_CAST(ptr, ClassName)          const_cast<ClassName *>(RUNTIME_CONST_CAST(ptr, ClassName))

/************************************************************************/
// Runtime object MACRO definition. End
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// RuntimeObject class declaration
//////////////////////////////////////////////////////////////////////////
/**
 * \brief   Runtime class object is a base class for all Runtime classes,
 *          which contain class name used in Runtime operation.
 **/
class AREG_API RuntimeObject    : private   RuntimeBase   // Base Runtime class, declared as private
                                , public    Object        // Instance of Object class
{
//////////////////////////////////////////////////////////////////////////
// Constructor / Destructor
//////////////////////////////////////////////////////////////////////////
protected:
    /**
     * \brief   Constructor
     **/
    RuntimeObject( void );

    /**
     * \brief   Destructor
     **/
    virtual ~RuntimeObject( void );

//////////////////////////////////////////////////////////////////////////
// Attributes
//////////////////////////////////////////////////////////////////////////
public:
/************************************************************************/
// Declare Runtime standard functions and variables
/************************************************************************/
    /**
     * \brief   The Runtime Object should contain runtime information.
     **/
    DECLARE_RUNTIME(RuntimeObject)

//////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////
public:
    /**
     * \brief	Makes casting of pointer of object during runtime 
     *          by given class identifier. If class is an instance
     *          of given class identifier, it returns valid pointer.
     *          Otherwise, it returns NULL.
     * \param	classId     Class identifier to make casting
     * \return	Returns valid pointer, if class is an instance of passed
     *          class identifier. Otherwise return NULL.
     **/
    inline const RuntimeObject* runtimeCast(const RuntimeClassID & classId) const;

    /**
     * \brief	Makes casting of pointer of object during runtime 
     *          by given class name. If class is an instance
     *          of given class name, it returns valid pointer.
     *          Otherwise, it returns NULL.
     * \param	className   Class name to make casting
     * \return	Returns valid pointer, if class is an instance of passed
     *          class name. Otherwise return NULL.
     **/
    inline const RuntimeObject* runtimeCast(const char * className) const;

    /**
     * \brief	Makes casting of pointer of object during runtime 
     *          by given class number. If class numbers have same 
     *          magic numbers, it returns valid pointer.
     *          Otherwise, it returns NULL.
     * \param	classNumber The magic number of the class to compare
     * \return	Returns valid pointer, if class is an instance of passed
     *          magic number of the class. Otherwise return NULL.
     **/
    inline const RuntimeObject* runtimeCast(unsigned int classNumber) const;

/************************************************************************/
// friend global operations
/************************************************************************/

    /**
     * \brief	Makes casting of constant pointer of object during runtime 
     *          by given class identifier. If class is an instance
     *          of given class identifier, it returns valid pointer.
     *          Otherwise, it returns NULL.
     * \param   ptr         Constant Pointer of object to cast
     * \param	classId     Class identifier to make casting
     * \return	Returns valid pointer, if class is an instance of passed
     *          class identifier. Otherwise return NULL.
     **/
    friend inline const RuntimeObject* runtimeCast(const RuntimeObject * ptr, const RuntimeClassID & classId);

    /**
     * \brief	Makes casting of constant pointer of object during runtime 
     *          by given class name. If class is an instance
     *          of given class name, it returns valid pointer.
     *          Otherwise, it returns NULL.
     * \param   ptr         Constant Pointer of object to cast
     * \param	className   Class name to make casting
     * \return	Returns valid pointer, if class is an instance of passed
     *          class name. Otherwise return NULL.
     **/
    friend inline const RuntimeObject* runtimeCast(const RuntimeObject* ptr, const char* className);

//////////////////////////////////////////////////////////////////////////
// Hidden / Forbidden methods
//////////////////////////////////////////////////////////////////////////
private:
    RuntimeObject( const RuntimeObject & /*src*/ );
    const RuntimeObject & operator = ( const RuntimeObject & /*src*/ );
};

//////////////////////////////////////////////////////////////////////////
// RuntimeObject class inline function implementation
//////////////////////////////////////////////////////////////////////////

inline const RuntimeObject* RuntimeObject::runtimeCast( const RuntimeClassID & classId ) const
{
    return (isInstanceOfRuntimeClass( classId ) ? this : NULL);
}

inline const RuntimeObject* RuntimeObject::runtimeCast( const char* className ) const
{
    return (isInstanceOfRuntimeClass( className ) ? this : NULL);
}

inline const RuntimeObject* RuntimeObject::runtimeCast( unsigned int classNumber ) const
{
    return (isInstanceOfRuntimeClass( classNumber ) ? this : NULL);
}

inline const RuntimeObject* RuntimeCast(const RuntimeObject * ptr, const RuntimeClassID & classId)
{
    return (ptr != NULL ? ptr->runtimeCast(classId) : NULL);
}

inline const RuntimeObject* RuntimeCast(const RuntimeObject * ptr, const char * className)
{
    return (ptr != NULL ? ptr->runtimeCast(className) : NULL);
}

inline const RuntimeObject* RuntimeCast(const RuntimeObject* ptr, unsigned int classNumber)
{
    return (ptr != NULL ? ptr->runtimeCast(classNumber) : NULL);
}

#endif  // AREG_BASE_RUNTIMEOBJECT_HPP