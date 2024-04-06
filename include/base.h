/*********************************************************************
 * @file    base.h    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once

//! Always inline
#if defined(__clang__)
#define ALWAYS_INLINE_FUNCTION inline __attribute__((always_inline))
#define ALWAYS_INLINE __attribute__((always_inline))
#endif

#ifndef ALWAYS_INLINE_FUNCTION
#define ALWAYS_INLINE_FUNCTION inline
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE inline
#endif

// export/import
#define _EXPORT_DLL __declspec(dllexport)
#define _IMPORT_DLL __declspec(dllimport)

#ifdef LIB_BUILD_AS_HEADER_ONLY  // build as header-only
#define DLL_OPTION
#else
#ifdef LIB_BUILD_AS_SHARED  // build as shared
#ifdef LIB_EXPORT_DLL
#define DLL_OPTION _EXPORT_DLL
#else
#define DLL_OPTION _IMPORT_DLL
#endif
#else  // build as static
#define DLL_OPTION
#endif
#endif
