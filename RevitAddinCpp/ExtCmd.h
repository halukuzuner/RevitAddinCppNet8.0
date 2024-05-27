 #pragma once
#include "pch.h"
#include "stdafx.h"
#include "WindowHandler.h"
#include "ModelessForm.h"
#include "Resource.h"
#include "RequestHandler.h"

using namespace Autodesk::Revit::ApplicationServices;
using namespace Autodesk::Revit::Attributes;
using namespace Autodesk::Revit::DB;
//using namespace Autodesk::Revit::UI;

namespace RvtAppSrv = Autodesk::Revit::ApplicationServices;
namespace RvtDB = Autodesk::Revit::DB;

namespace RevitAddinCpp
{
	//	Bu bildirim IExternalCommand tanýmýndan hemen önce yapýlmalý.
	[Transaction(Autodesk::Revit::Attributes::TransactionMode::Manual)]
	[Regeneration(Autodesk::Revit::Attributes::RegenerationOption::Manual)]

	public ref class ExtCmd : IExternalCommand
	{
	private: const String^ _prompt = "Please select some elements.";
	public: static WindowHandle^ _hWndRevit = nullptr;
   //Public so can be set to false from Window closed event
   public: static bool isMainFormActive = false;

#pragma region Cached Variables

	public: static ExternalCommandData^ _cachedCmdData;

	public: static property UIApplication^ CachedUiApp
		{
			UIApplication^ get()
			{
				return _cachedCmdData->Application;
			}
		}

	public: static property UIDocument^ CachedUIDoc
		{
			UIDocument^ get()
			{
				return CachedUiApp->ActiveUIDocument;
			}
		}

	public:	static property RvtAppSrv::Application^ CachedApp
		{
			RvtAppSrv::Application^ get()
			{
				return CachedUiApp->Application;
			}
		}

	public: static property RvtDB::Document^ CachedDoc
		{
			RvtDB::Document^ get()
			{
				return CachedUiApp->ActiveUIDocument->Document;
			}
		}

	public: static ModelessForm^ MainForm;

#pragma endregion

#pragma region IExternalCommand Members        

	public: virtual Result Execute(ExternalCommandData^, String^%, ElementSet^);

#pragma endregion
	};
}