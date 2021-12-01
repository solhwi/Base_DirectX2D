#pragma once

class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;

class Graphics : public Singleton<Graphics>
{
public:
	friend class Singleton<Graphics>;

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }

	D3DXCOLOR GetClearColor() { return clearColor; }

	void Resize(const UINT& width, const UINT& height);
	void SetViewport(const UINT& width, const UINT& height);

	void Begin();
	void End();

	void SetViewport();
	void SetBackBufferToRTV();

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	Graphics();
	~Graphics();
	
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = 0xff555566;

	UINT numerator = 0;
	UINT denominator = 1;

	UINT gpuMemorySize = 0;
	wstring gpuDescription = L"";

	vector<D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	bool bVsync = true;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class D3DEnumAdapterInfo
{
public:
	D3DEnumAdapterInfo() = default;
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	IDXGIAdapter1* adapter = nullptr;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	D3DEnumOutputInfo* outputInfo = nullptr;
};

class D3DEnumOutputInfo
{
public:
	D3DEnumOutputInfo() = default;
	~D3DEnumOutputInfo();

	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};