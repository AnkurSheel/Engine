// *****************************************************************************
//  FontShader   version:  1.0   Ankur Sheel  date: 2012/10/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "FontShader.h"
#include "DxBase.hxx"
#include "Texture.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cFontShader::cFontShader()
{

}

// *****************************************************************************
cFontShader::~cFontShader()
{
}

// *****************************************************************************
bool cFontShader::VSetShaderParameters(const XMFLOAT4X4 & inMatWorld,
									   const XMFLOAT4X4 & inMatView,
									   const XMFLOAT4X4 & inMatProjection)
{
	if(!cBaseShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection))
	{
		return false;
	}
	if(m_pTexture)
	{
		ID3D11ShaderResourceView * pTex = m_pTexture->VGetTexture();
		IDXBase::GetInstance()->VGetDeviceContext()->PSSetShaderResources(0, 1, &pTex);
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Lock the pixel constant buffer so it can be written to.
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pPixelBuffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		Log_Write(ILogger::LT_ERROR, 1, cString("Could not lock the pixel Buffer to update with the matrices data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}

	PixelBufferType * pPixelData = (PixelBufferType*)mappedResource.pData;

	// Copy the pixel color into the pixel constant buffer.
	pPixelData->pixelColor = m_DiffuseColor;

	// Unlock the pixel constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pPixelBuffer, 0);

	// Set the position of the pixel constant buffer in the pixel shader.
	unsigned int iBufferNumber = 0;

	// Now set the pixel constant buffer in the pixel shader with the updated value.
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetConstantBuffers(iBufferNumber, 1, &m_pPixelBuffer);
	return true;
}

// *****************************************************************************
IShader * const IShader::CreateFontShader()
{
	IShader * pShader= DEBUG_NEW cFontShader();
	return pShader;
}