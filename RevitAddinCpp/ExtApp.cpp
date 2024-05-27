#include "pch.h"
#include "StdAfx.h"

using namespace Autodesk::Revit::ApplicationServices;
using namespace Autodesk::Revit::Attributes;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;

namespace RevitAddinCpp
{
[Transaction(TransactionMode::Manual)]
[Regeneration(RegenerationOption::Manual)]
public ref class ExtApp : IExternalApplication
{
#pragma region Cached Variables

public:	static UIControlledApplication^ _cachedUiCtrApp;

#pragma endregion Cached Variables

#pragma region IExternalApplication Members

	virtual Result OnStartup(UIControlledApplication^ uiApp)
	{
		_cachedUiCtrApp = uiApp;

		try
		{
			RibbonPanel^ ribbonPanel = CreateRibbonPanel();

			//TODO: add you code below->

			return Result::Succeeded;
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->ToString());
			return Result::Failed;
		}
	}

	virtual Result OnShutdown(UIControlledApplication^ uiApp)
	{
		try
		{
			//TODO: add you code below->

			return Result::Succeeded;
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->ToString());
			return Result::Failed;
		}
	}

#pragma endregion IExternalApplication Members

#pragma region Local Methods

private: RibbonPanel^ CreateRibbonPanel()
{
	RibbonPanel^ panel = _cachedUiCtrApp->CreateRibbonPanel("RevitAddinCpp");

	////Default button:
	PushButtonData^ pbDataExtCmd = gcnew PushButtonData("ExtCmd", "RevitAddin\nCpp", Assembly::GetExecutingAssembly()->Location, "RevitAddinCpp.ExtCmd");
	PushButton^ pbExtCmd = static_cast<PushButton^>(panel->AddItem(pbDataExtCmd));
	pbExtCmd->ToolTip = "ExtCmd";
	pbExtCmd->LargeImage = BmpImageSource("ExtCmd32x32");
	pbExtCmd->Image = BmpImageSource("ExtCmd16x16");

	////More buttons:

	return panel;
}

private: System::Windows::Media::ImageSource^ BmpImageSource(String^ embeddedPath)
{
	ResourceManager^ resources = gcnew ResourceManager("RevitAddinCpp.Resources", Assembly::GetExecutingAssembly());
	System::Drawing::Bitmap^ img = (cli::safe_cast<System::Drawing::Bitmap^>(resources->GetObject(embeddedPath)));

	IntPtr hBitmap = img->GetHbitmap();
	return System::Windows::Interop::Imaging::CreateBitmapSourceFromHBitmap(hBitmap, IntPtr::Zero, Int32Rect::Empty, System::Windows::Media::Imaging::BitmapSizeOptions::FromEmptyOptions());
}
		
#pragma endregion Local Methods
};	//	End of "ref class ExtApp : IExternalApplication"
}	//	End of namespace "RevitAddinCpp"