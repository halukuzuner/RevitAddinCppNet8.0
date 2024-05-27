// RequestHandler.cpp
#include "pch.h"
#include "Request.h"
#include "RequestHandler.h"
#include "ModelessForm.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

//using namespace MyTree;

namespace RevitAddinCpp
{
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
   void RequestHandler::Execute(UIApplication^ uiapp)
   {
      try
      {
         switch (request->Take())
         {
         case RequestId::Pick:
         {
            Operation^ operation = gcnew Operation(&RequestHandler::Pick);
            RequestHandler::modify(uiapp, "Pick an element from active view.", operation);
            break;
         }
         case RequestId::Draw:
         {
            Operation^ operation = gcnew Operation(&RequestHandler::Draw);
            RequestHandler::modify(uiapp, "Draw a line", operation);
            break;
         }
         default:
         {
            // some kind of a warning here should
            // notify us about an unexpected request 
            break;
         }
         }
      }
      finally
      {
         //application->thisApp->WakeFormUp();
      }

      return;
   }

   void RequestHandler::modify(UIApplication^ uiapp, String^ str, Operation^ operation)
   {
      try
      {
         Transaction^ trans = gcnew Transaction(uiapp->ActiveUIDocument->Document);

         // The name of the transaction was given as an argument

         if (trans->Start(str) == TransactionStatus::Started)
         {
            operation(uiapp);
            trans->Commit();
         }
      }
      catch (Exception^ ex)
      {
         TaskDialog::Show("Modify ", ex->Message->ToString());
         //return Result::Failed;
      }
   }

   void RequestHandler::Pick(UIApplication^ uiapp)
   {
      UIDocument^ uidoc = uiapp->ActiveUIDocument;
      Document^ doc = uidoc->Document;
      Autodesk::Revit::UI::Selection::Selection^ choices = uidoc->Selection;
      // Pick one object from Revit.
      Reference^ hasPickOne = choices->PickObject(Autodesk::Revit::UI::Selection::ObjectType::Element);
      if (hasPickOne != nullptr)
      {
         TaskDialog::Show("Revit", "One element selected.\n" + "Id: " + hasPickOne->ElementId->ToString());
      }
   }

   void RequestHandler::Draw(UIApplication^ uiapp)
   {
    
   }
}  // End of namespace RevitAddinCpp