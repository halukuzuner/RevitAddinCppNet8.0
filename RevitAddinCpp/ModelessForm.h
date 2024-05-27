#pragma once

#include "RequestHandler.h"

namespace RevitAddinCpp
{
   using namespace System;
   using namespace System::Collections::Generic;
   using namespace System::ComponentModel;
   using namespace System::Collections;
   using namespace System::Windows::Forms;
   using namespace System::Data;
   using namespace System::Drawing;

   using namespace Autodesk::Revit::DB;

   using View = Autodesk::Revit::DB::View;

   /// <summary>
   /// Summary for ModelessForm
   /// </summary>
   public ref class ModelessForm : System::Windows::Forms::Form
   {
   // In this sample, the dialog owns the handler and the event objects,
   // but it is not a requirement. They may as well be static: properties
   // of the application.

   /// <summary>
   /// A reference to the external command data.
   /// </summary>
private: ExternalCommandData^ extcmdata;
   private: UIApplication^ uiapp;
   private: UIDocument^ uidoc;
   /// <summary>
   /// The active document
   /// </summary>
   private: Document^ doc;
   private: RequestHandler^ m_Handler;
   private: ExternalEvent^ m_ExEvent;
   private: System::Windows::Forms::Button^ btnPick;

   private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;

   // public fields

   public:
      ModelessForm(ExternalCommandData^ ExtCmd, ExternalEvent^ exEvent, RequestHandler^ handler)
      {
         InitializeComponent();
         extcmdata = ExtCmd;
         uiapp = extcmdata->Application;
         uidoc = uiapp->ActiveUIDocument;
         doc = uidoc->Document;
         m_Handler = handler;
         m_ExEvent = exEvent;
      }

   protected:
      /// <summary>
      /// Clean up any resources being used.
      /// </summary>
      ~ModelessForm()
      {
         if (components)
         {
            delete components;
         }
      }

   private: System::Windows::Forms::Button^ btnExit;
   private: System::ComponentModel::IContainer^ components;

   private:
   /// <summary>
   /// Required designer variable.
   /// </summary>
#pragma region Windows Form Designer generated code
   /// <summary>
   /// Required method for Designer support - do not modify
   /// the contents of this method with the code editor.
   /// </summary>
      void InitializeComponent(void)
      {
         this->components = (gcnew System::ComponentModel::Container());
         this->btnExit = (gcnew System::Windows::Forms::Button());
         this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
         this->btnPick = (gcnew System::Windows::Forms::Button());
         this->SuspendLayout();
         // 
         // btnExit
         // 
         this->btnExit->Location = System::Drawing::Point(322, 227);
         this->btnExit->Name = L"btnExit";
         this->btnExit->Size = System::Drawing::Size(50, 20);
         this->btnExit->TabIndex = 1;
         this->btnExit->Text = L"&Exit";
         this->btnExit->UseVisualStyleBackColor = true;
         this->btnExit->Click += gcnew System::EventHandler(this, &ModelessForm::btnExit_Click);
         // 
         // contextMenuStrip1
         // 
         this->contextMenuStrip1->Name = L"contextMenuStrip1";
         this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
         // 
         // btnPick
         // 
         this->btnPick->Location = System::Drawing::Point(15, 227);
         this->btnPick->Name = L"btnPick";
         this->btnPick->Size = System::Drawing::Size(50, 20);
         this->btnPick->TabIndex = 0;
         this->btnPick->Text = L"&Pick";
         this->btnPick->UseVisualStyleBackColor = true;
         this->btnPick->Click += gcnew System::EventHandler(this, &ModelessForm::btnPick_Click);
         // 
         // ModelessForm
         // 
         this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
         this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
         this->ClientSize = System::Drawing::Size(384, 261);
         this->Controls->Add(this->btnPick);
         this->Controls->Add(this->btnExit);
         this->Location = System::Drawing::Point(1000, 700);
         this->MaximizeBox = false;
         this->Name = L"ModelessForm";
         this->ResumeLayout(false);

      }
#pragma endregion Windows Form Designer generated code

   private: void MakeRequest(RequestId request)
   {
      m_Handler->request->Make(request);
      m_ExEvent->Raise();
   }
   private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
   {
      this->Close();
   }
   private: System::Void btnPick_Click(System::Object^ sender, System::EventArgs^ e)
   {
      MakeRequest(RequestId::Pick);
   }
};
}