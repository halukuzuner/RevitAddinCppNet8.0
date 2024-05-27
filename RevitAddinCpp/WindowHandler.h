#pragma once
#include "pch.h"
#include "stdafx.h"

#pragma region Window handle
/// <summary>
/// Wrapper class for converting IntPtr to IWin32Window.
/// </summary>
public ref class WindowHandle : public System::Windows::Forms::IWin32Window
{
	IntPtr _hwnd;

	public: WindowHandle(IntPtr h)
	{
		Debug::Assert(System::IntPtr::Zero != h, "expected non-null window handle");

		_hwnd = h;
	}

	public: virtual property IntPtr Handle
	{
		System::IntPtr get() {
			return _hwnd;
		}
	}
};
#pragma endregion
