#include "DropManager.h"
#include <vector>
#include <iostream>

//Uint32 FileDrop = SDL_RegisterEvents(1);

HRESULT __stdcall DropManager::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == IID_IDropTarget)
	{
		*ppvObject = this;	// or static_cast<IUnknown*> if preferred
		// AddRef() if doing things properly
					// but then you should probably handle IID_IUnknown as well;
		return S_OK;
	}

	*ppvObject = NULL;
	return E_NOINTERFACE;
}

ULONG __stdcall DropManager::AddRef(void)
{
    return 0;
}

ULONG __stdcall DropManager::Release(void)
{
    return 0;
}

HRESULT __stdcall DropManager::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	*pdwEffect &= DROPEFFECT_COPY;
	return S_OK;
}

HRESULT __stdcall DropManager::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	*pdwEffect &= DROPEFFECT_COPY;
	return S_OK;
}

HRESULT __stdcall DropManager::DragLeave(void)
{
	return S_OK;
}

HRESULT __stdcall DropManager::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
	FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stgm;
	if (SUCCEEDED(pDataObj->GetData(&fmte, &stgm)))
	{
		HDROP hdrop = (HDROP)stgm.hGlobal; // or reinterpret_cast<HDROP> if preferred
		UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
		files.clear();

		for (UINT i = 0; i < file_count; i++)
		{
			TCHAR* szFile = new TCHAR[MAX_PATH];
			UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);

			if (cch > 0 && cch < MAX_PATH)
			{
				files.push_back(szFile);
				//std::wcout << "dawdawd" << std::endl;
			}
		}
		

		if (FileDrop != ((Uint32)-1)) {
			SDL_Event event;
			SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
			event.type = FileDrop;
			//event.user.data1 = v;
			SDL_PushEvent(&event);
		}

		// we have to release the data when we're done with it
		ReleaseStgMedium(&stgm);
	}

	*pdwEffect &= DROPEFFECT_COPY;
	return S_OK;
}