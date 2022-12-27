#pragma once
#include <oleidl.h>
#include <SDL.h>
#include <vector>

class DropManager: public IDropTarget
{

	// Inherited via IDropTarget
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override;
	virtual ULONG __stdcall AddRef(void) override;
	virtual ULONG __stdcall Release(void) override;
	virtual HRESULT __stdcall DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
	virtual HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;
	virtual HRESULT __stdcall DragLeave(void) override;
	virtual HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override;

public:
	Uint32 FileDrop = SDL_RegisterEvents(1);
	std::vector<TCHAR*> files{};
};

