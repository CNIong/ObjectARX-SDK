//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//  DESCRIPTION:  Header for access to AutoCAD JavaScript-specific services.
//

#ifndef   _ACJS_H
#define   _ACJS_H

#ifdef  _ACJSCORESTUB
    #define ACJSCORESTUB_PORT   __declspec(dllexport)
#else
    #define ACJSCORESTUB_PORT   __declspec(dllimport)
#endif


typedef char* (*AcJsFunctionPtr)    (const char*);
typedef void  (*AcJsInvokeCallback) (const char*);

// Mask flags for metadata for native callback function 
#define ACJS_FUNC_INVOKEINDOC       0x00000001      // the function needs to be invoked in a document
#define ACJS_FUNC_INVOKESYNC        0x00000002      // the function should be invoked synchronously via the exec() JavaScript function
#define ACJS_FUNC_INVOKEASYNC       0x00000004      // the function should be invoked asynchronously via the execAsync() JavaScript function



#define ACJSCORESTUB_DEFUN  "acjsDefun"
#define ACJSCORESTUB_INVOKE "acjsInvoke"
typedef Acad::ErrorStatus (*ACJSCORESTUB_DEFUN_PROC)(const TCHAR* name, AcJsFunctionPtr funcAddr, Adesk::Int32 funcFlags);
typedef Acad::ErrorStatus (*ACJSCORESTUB_INVOKE_PROC)(const TCHAR* name, const TCHAR* jsonArgs);

/// <summary>
///  Registers a native callback that can be invoked from JavaScript using 
///  the built-in exec() function.
/// </summary>
/// <param name="name">
///  Name of the callback.
/// </param>
/// <param name="funcAddr">
///  Function to invoke when callback is invoked.
/// </param>
/// <param name="funcFlags">
/// flags for metadata for native callback function.
/// The flags is set to 0 by default. It can be set to ACJS_FUNC_INVOKEINDOC and can logically ORd with other new flags in future.
/// </param>
/// <returns>
///  Returns Acad::eOk if successful.
/// </returns>
extern "C" ACJSCORESTUB_PORT Acad::ErrorStatus acjsDefun    (const TCHAR* name, AcJsFunctionPtr funcAddr, Adesk::Int32 funcFlags = 0);

/// <summary>
///  Invokes a JavaScript callback in the V8 context.
/// </summary>
/// <param name="name">
///  Name of the callback.
/// </param>
/// <param name="jsonArgs">
///  Arguments formatted as JSON string.  Can be NULL if the JavaScript callback
///  doesn't take any arguments.
/// </param>
/// <returns>
///  Returns Acad::eOk if successful.
/// </returns>
/// <remarks>
///  If the callback hasn't been registered in JavaScript, then the operation 
///  will be quietly ignored.
/// </remarks>
extern "C" ACJSCORESTUB_PORT Acad::ErrorStatus acjsInvoke   (const TCHAR* name, const TCHAR* jsonArgs, TCHAR** jsonRetVal = NULL);

/// <summary>
///  Invokes a JavaScript callback asyncronously in the V8 context.
/// </summary>
/// <param name="name">
///  Name of the callback.
/// </param>
/// <param name="jsonArgs">
///  Arguments formatted as JSON string.  Can be NULL if the JavaScript callback
///  doesn't take any arguments.
/// </param>
/// <param name="onComplete">
///  Callback function to be invoked when the JavaScript callback completes
///  successfully.
/// </param>
/// <param name="onError">
///  Callback function to be invoked when the JavaScript callback fails for 
///  any reason.
/// </param>
/// <returns>
///  Returns Acad::eOk if successful.
/// </returns>
/// <remarks>
///  If the callback hasn't been registered in JavaScript, then the operation 
///  will be quietly ignored.
/// </remarks>
extern "C" ACJSCORESTUB_PORT Acad::ErrorStatus acjsInvokeAsync  (const TCHAR* name, 
                                                                 const TCHAR* jsonArgs,
                                                                 AcJsInvokeCallback onComplete,
                                                                 AcJsInvokeCallback onError);

#endif // _ACJS_H

