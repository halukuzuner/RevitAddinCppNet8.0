// RequestHandler.h
#pragma once
//
// (C) Copyright 2003-2019 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE. AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

#include "Request.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

namespace RevitAddinCpp
{
   /// <summary>
   ///   A class with methods to execute requests made by the dialog user.
   /// </summary>
   /// 
   public ref class RequestHandler : IExternalEventHandler
   {
   /// A trivial delegate, but handy
   public: delegate void Operation(UIApplication^);

   /// The value of the latest request made by the modeless form 
   public: static Request^ m_request = gcnew RevitAddinCpp::Request;

   /// <summary>
   /// A public: property to access the current request value
   /// </summary>
   public: property Request^ request
   {
      RevitAddinCpp::Request^ get() {
         return this->m_request;
      }
   }
   /// <summary>
   ///   A method to identify this External Event Handler
   /// </summary>
   public: virtual String^ GetName()
   {
      return "R2024 External Event Sample";
   }

   /// <summary>
   ///   The top method of the event handler.
   /// </summary>
   /// <remarks>
   ///   This is called by Revit after the corresponding
   ///   external event was raised (by the modeless form)
   ///   and Revit reached the time at which it could call
   ///   the event's handler (i.e. this object)
   /// </remarks>
   /// 
   public: virtual void Execute(UIApplication^);
   /// <summary>
   /// Cantains transaction method to make madification in the model.
   /// </summary>
   /// <param name="UIApplication^:">UIAplication to be processed.</param>
   /// <param name="String^: ">Name of the transaction.</param>
   /// <param name="Operation^: ">Operation name which appended to delegate.</param>
   private: static void modify(UIApplication^, String^, Operation^);

   /// <summary>
   /// Pick an object from active view.
   /// </summary>
   /// <param name="UIApplication^:">UIAplication to be processed.</param>
   private: static void Pick(UIApplication^);

   /// <summary>
   /// Draws lines in active view.
   /// </summary>
   /// <param name="UIApplication^:">UIAplication to be processed.</param>
   private: static void Draw(UIApplication^);
   };  // End of class
}  // End of namespace