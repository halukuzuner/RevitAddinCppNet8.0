#include "pch.h"
#include "stdafx.h"
#include "WindowHandler.h"
#include "ExtCmd.h"
#include "ModelessForm.h"
#include "Resource.h"
#include "RequestHandler.h"

namespace RevitAddinCpp
{
#pragma region IExternalCommand Members        
	Result ExtCmd::Execute(ExternalCommandData^ cmdData, String^% msg, ElementSet^ elemSet)
	{
		ExtCmd::_cachedCmdData = cmdData;


		//	From Building coder. To handle main Revit window.
		if (nullptr == ExtCmd::_hWndRevit)
		{
			Process^ process = Process::GetCurrentProcess();

			IntPtr h = process->MainWindowHandle;
			ExtCmd::_hWndRevit = gcnew WindowHandle(h);
		}
		//	From Building coder
		try
		{
			// If we do not have a dialog yet, create and show it
			if (ExtCmd::MainForm == nullptr || ExtCmd::MainForm->IsDisposed)
			{
				// A new handler to handle request posting by the dialog
				RequestHandler^ handler = gcnew RequestHandler();

				// External Event for the dialog to use (to post requests)
				ExternalEvent^ exEvent = ExternalEvent::Create(handler);

				// We give the objects to the new dialog;
				// The dialog becomes the owner responsible fore disposing them, eventually.

				ExtCmd::MainForm = gcnew ModelessForm(cmdData, exEvent, handler);

            if (isMainFormActive == false)
            {
               ExtCmd::MainForm->Show(ExtCmd::_hWndRevit);
               isMainFormActive = true;
            }
			}
			return Result::Succeeded;
		}
		catch (System::Exception^ ex)
		{
			msg = ex->ToString();
			return Result::Failed;
		}

		return Result::Succeeded;
	}
}