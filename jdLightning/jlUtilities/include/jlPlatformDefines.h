#pragma once
//cabecera
#pragma once
//Este es el archivo que nunca va a tener un include

#define JL_PLATFORM_WIN32   1       //Windows Platform
#define JL_PLATFORM_LINUX   2       //Linux Platform
#define JL_PLATFORM_OSX     3       //Linux Platform

#define JL_COMPILER_MSVC    1       //Visual Studio Compiler
#define JL_COMPILER_GNUC    2       //GCC Compiler
#define JL_COMPILER_CLANG   3       //Clang Compiler

#define JL_ARCHITECTURE_x86_32  1   //Intel x86 32 bits
#define JL_ARCHITECTURE_x86_64  2   //Intel x86 32 bits

#define JL_ENDIAN_LITTLE  1         //Little Endian
#define JL_ENDIAN_BIG 1             //Big Endian
/*
Color endianis
RGBA
0xFF0000CC
1111 1111  0000 0000  0000 0000  1100 1100
    A          B          G           R
  low bit                         high bit
Little endian el menor bit se manda primero
Big indian, el mayor bit se manda primero
*/

/*****************************************************************************/
/**
 *Compiler type and version
 */
/*****************************************************************************/
#if defined(__clang__)
#   define JL_COMPILER JL_COMPILER_CLANG
#   define JL_COMP_VER __clang_version__
#   define JL_THREADLOCAL __thread
#   define JL_STDCALL __attribute__((stdcall))
#   define JL_CDECL __attribute__((cdecl))
#   define JL_FALLTHROUGH [[clang::fallthrough]];
#elif defined(__GNUC__)
#   define JL_COMPILER JL_COMPILER_GNUC
#   define JL_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10) +__GNUC_PATCHLEVEL__)
#   define JL_THREADLOCAL __thread
#   define JL_STDCALL __attribute__((stdcall))
#   define JL_CDECL __attribute__((cdecl))
#   define JL_FALLTHROUGH __attribute__((fallthrough));
#elif defined(__INTEL_COMPILER__)
#   define JL_COMPILER JL_COMPILER_GNUC
#   define JL_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10) +__GNUC_PATCHLEVEL__)
#   define JL_THREADLOCAL __thread
#   define JL_STDCALL __attribute__((stdcall))
#   define JL_CDECL __attribute__((cdecl))
#   define JL_FALLTHROUGH __attribute__((fallthrough));
#elif defined(_MSC_VER)
#   define JL_COMPILER JL_COMPILER_MSVC
#   define JL_COMP_VER _MSC_VER
#   define JL_THREADLOCAL __declspec(thread)
#   define JL_STDCALL __stdcall
#   define JL_CDECL __cdecl
#   define JL_FALLTHROUGH 
#   undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No know compiler found, send the error to the output (if any)
#   pragma error "No known compiler. "
#endif

/*****************************************************************************/
/**
 * See if we can use __forceinline or if we need to use _inline instead
 */
/*****************************************************************************/
#if JL_COMPILER==JL_COMPILER_MSVC             //If we are compiling on Visual Studio
# if JL_COMP_VER >= 1600                      //If we are on Visual Studio 9 or higher
#   define FORCEINLINE __forceinline          //Set __forceinline
#   ifndef RESTRICT 
#     define RESTRICT __restrict              //No alias hint
#   endif
# endif
#elif defined(__MINGW32__)                    //If we are on a Unix type system
# if !defined(FORCEINLINE)                    
#   define FORCEINLINE __inline               //Set __inline
#   ifndef RESTRICT 
#     define RESTRICT __restrict              //No alias hint
#   endif
# endif
#else                                         //Any other Compiler
# define FORCEINLINE __inline                 //Set __inline
# ifndef RESTRICT 
#   define RESTRICT __restrict                //No alias hint
# endif
#endif

/*****************************************************************************/
/**
 * Finds the current plataform
 */
/*****************************************************************************/
#if defined(__WIN32__) ||  defined(_WIN32)
# define JL_PLATFORM JL_PLATFORM_WIN32
#elif defined(__APPLE_CC__)
# define JL_PLATFORM JL_PLATFORM_WIN32
#else
# define JL_PLATFORM JL_PLATFORM_LINUX
#endif

/*****************************************************************************/
/**
 * Find the architecture type
 */
/*****************************************************************************/
#if defined (__x86_64__) || defined(_M_X64)
# define JL_ARCH_TYPE JL_ARCHITECTURE_x86_64
#else
# define JL_ARCH_TYPE JL_ARCHITECTURE_x86_32
#endif

/*****************************************************************************/
/**
 * Memory Aligment macros
 */
/*****************************************************************************/
#if JL_COMPILER == JL_COMPILER_MSVC  // If we are compiling on visual studio
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
#elif ( JL_COMPILER == JL_COMPILER_GNUC )
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__ ( (__aligned__(n)) )
#else                               // If we are on the Unix type system
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__ ( (packed, aligned(n)) )
# define GCC_ALIGN(n) __attribute__( (aligned(n)) )
#endif

/*****************************************************************************/
/**
 * For throw override (deprecated on c++11 but Visual Studio does not have handle noexcept
 */
/*****************************************************************************/
#if JL_COMPILER == JL_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif JL_COMPILER == JL_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/*****************************************************************************/
/**
 * Library export specifics
 */
/*****************************************************************************/
#if JL_PLATFORM == JL_PLATFORM_WIN32
# if JL_COMPILER == JL_COMPILER_MSVC
#   if defined ( JL_STATIC_LIB )
#     define JL_UTILITY_EXPORT
#   else
#     if defined ( JL_UTILITY_EXPORTS )
#       define JL_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define JL_UTILITY_EXPORT __declspec( dllimport )
#     endif
#   endif
#else // Any other compiler
#  if defined( JL_STATIC_LIB )
#    define JL_UTILITY_EXPORT
#  else 
#    if defined( JL_UTILITY_EXPORTS )
#       define JL_UTILITY_EXPORT __attribute__ (( dllexport ))
#     else
#       define JL_UTILITY_EXPORT __attribute__ (( dllimport ))
#     endif
#   endif
#endif
# define JL_UTILITY_HIDDEN
#else // Linux/Mac settings
# define JL_UTILITY_EXPORT __attribute__ ((visIbility ("default")))
# define JL_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

/*****************************************************************************/
/**
 * DLL export for plug ins
 */
/*****************************************************************************/
#if JL_PLATFORM == JL_PLATFORM_WIN32
# if JL_COMPILER == JL_COMPILER_MSVC
#   define JL_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define JL_PLUGIN_EXPORT __attribute__ ((dllexport))
# endif
#else // Linux/Mac settings
# define JL_PLUGIN_EXPORT __attribute__ ((visibility ("default")))
#endif

/*****************************************************************************/
/**
 * Windows specific Settings
 */
/*****************************************************************************/
// Win32 compilers use _DEBUG for specifying debug builds. For MinGW, we set DEBUG
#if JL_PLATFORM ==JL_PLATFORM_WIN32
# if defined(_DEBUG) || defined (DEBUG)
#   define JL_DEBUG_MODE 1                     //Specifies that we ae on a DEBUG build
# else
#   define JL_DEBUG_MODE 0                     //We are not on a DEBUG buid
# endif
#endif 

/*****************************************************************************/
/**
 * Linux specific settings
 */
/*****************************************************************************/
#if JL_PLATFORM == JL_PLATFORM_LINUX
# define stricmp strcasecmp                    //If we are on a DEBUG build
# if defined(_DEBUG) || defined (DEBUG)
#   define JL_DEBUG_MODE 1                     //Specifies that we ae on a DEBUG build
# else
#   define JL_DEBUG_MODE 0                     //We are not on a DEBUG buid
# endif
#endif 

/*****************************************************************************/
/**
 * Definition of Debug macros
 */
/*****************************************************************************/
#if JL_DEBUG_MODE
# define JL_DEBUG_MODE_ONLY(x) x
# define JL_ASSERT(x) assert(x)
#else
# define JL_DEBUG_ONLY(x)
# define JL_ASSERT(x)
#endif

#if JL_COMPILER == JL_COMPILER_MSVC
# define _CRT_SECURE_NO_WARNINGS
# pragma warning (disable : 4201)//Structuras sin nombre
# pragma warning (disable : 4275)//Para la interface de DLL
# pragma warning (disable : 4251)//Para la interface de DLL
# pragma warning (disable : 4191)
# pragma warning (disable : 4503)//Para nombres extremadamente largos
#endif
