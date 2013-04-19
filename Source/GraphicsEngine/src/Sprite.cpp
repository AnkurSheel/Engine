// *****************************************************************************
//  Sprite   version:  1.0   Ankur Sheel  date: 05/09/2008
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Sprite.h"
#include "DxBase.hxx"
#include "Texture.hxx"
#include "TextureShader.h"
#include "vertexstruct.h"
#include "Camera.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "GameDirectories.h"

using namespace Utilities;
using namespace Graphics;
using namespace Base;

// *****************************************************************************
cSprite::cSprite()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_vScale(1.0f, 1.0f)
, m_vPosition(cVector2<float>::Zero())
, m_bIsDirty(true)
, m_iIndexCount(0)
, m_iVertexCount(0)
{
}

// *****************************************************************************
cSprite::~cSprite()
{
	VCleanup();
}

// *****************************************************************************
bool cSprite::VInitialize( shared_ptr<ITexture> const pTexture )
{
	m_pTexture = pTexture;
	m_iVertexCount = 4;
	if(!CreateVertexBuffer())
		return false;

	if(!CreateIndexBuffer())
		return false;

	if(!InitializeShader())
		return false;

	m_vPosition = cVector2<float>(-1.0f, -1.0f);
	
	ID3D11Resource* resource;
	ID3D11Texture2D * texResource;
	D3D11_TEXTURE2D_DESC desc;
	m_pTexture->VGetTexture()->GetResource(&resource);
	texResource = reinterpret_cast<ID3D11Texture2D*>(resource);
	texResource->GetDesc(&desc);
	
	m_vSize.x = static_cast<float>(desc.Width);
	m_vSize.y = static_cast<float>(desc.Height);
	m_vScaledSize = m_vSize;
	m_bIsDirty = true;
	SafeRelease(&resource);
	return true;
}

// *****************************************************************************
bool cSprite::VInitialize( const Base::cString & strTextureFilename )
{
	Log_Write(ILogger::LT_EVENT, 2, "Loading Sprite : " + strTextureFilename);

	m_pTexture = ITextureManager::GetInstance()->VGetTexture(cGameDirectories::GameDirectories().strSpriteDirectory + strTextureFilename);
	
	if (m_pTexture != NULL)
	{
		return VInitialize(m_pTexture);
	}
	return false;
}

// *****************************************************************************
void cSprite::VRender(const ICamera * const pCamera)
{
	if (!m_pTexture || m_vScaledSize == cVector2<float>::Zero())
	{
		return;
	}
	if (m_bIsDirty)
	{
		RecalculateVertexData(pCamera);
		m_bIsDirty = false;
	}

	unsigned int stride = sizeof(stTexVertex);
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, 
		&m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOff();
	if (m_pShader)
	{
		XMFLOAT4X4 matView;
		XMStoreFloat4x4(&matView, XMMatrixIdentity());

		m_pShader->VSetTexture(m_pTexture);
		m_pShader->VRender(IDXBase::GetInstance()->VGetWorldMatrix(),
			matView, IDXBase::GetInstance()->VGetOrthoMatrix());
	}
	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);
}

// *****************************************************************************
void cSprite::VSetPosition(const Base::cVector2<float> & vPosition)
{
	if(m_vPosition != vPosition)
	{
		m_vPosition = vPosition;
		m_bIsDirty = true;
	}
}

// *****************************************************************************
void cSprite::VSetSize(const Base::cVector2<float> & vSize)
{
	if(m_vScaledSize != vSize)
	{
		if(vSize == cVector2<float>::Zero())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Setting sprite size to 0");
		}
		m_vScaledSize = vSize;
		m_vScale.x = m_vScaledSize.x / vSize.x;
		m_vScale.y = m_vScaledSize.y / vSize.y;
		m_bIsDirty = true;
	}
}

// *****************************************************************************
cVector2<float> cSprite::VGetScaledSize() const
{
	return m_vScaledSize;
}

// *****************************************************************************
void cSprite::VSetScale(const Base::cVector2<float> & vScale)
{
	if(m_vScale != vScale)
	{
		m_vScale = vScale;
		m_vScaledSize = m_vSize * m_vScale;
		m_bIsDirty = true;
	}
}

// ***************************************************************************************
void cSprite::VSetTexture(shared_ptr<ITexture> const pTexture)
{
	m_pTexture = pTexture;
}

// *****************************************************************************
void cSprite::VCleanup()
{
	SafeRelease(&m_pVertexBuffer);
	SafeRelease(&m_pIndexBuffer);
}

// *****************************************************************************
bool cSprite::CreateVertexBuffer()
{
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(stTexVertex) * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc,
		&vertexData, &m_pVertexBuffer);

	SafeDeleteArray(&pVertices);

	if(FAILED(result))
	{
		Log_Write(ILogger::LT_ERROR, 1, cString("Could not create Vertex Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// *****************************************************************************
bool cSprite::CreateIndexBuffer()
{
	unsigned long aIndices[] = {0,1,2,
								1,3,2};
	m_iIndexCount = 6;
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = aIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&indexBufferDesc,
		&indexData, &m_pIndexBuffer);

	if(FAILED(result))
	{
		Log_Write(ILogger::LT_ERROR, 1, cString("Could not create Index Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;

}

// *****************************************************************************
bool cSprite::RecalculateVertexData(const ICamera * const pCamera)
{
	//center of the screen is 0,0
	float left = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.x;
	float right = left + m_vScaledSize.x;
	float top = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.y;
	float bottom = top - m_vScaledSize.y;

	float z = 1.0f;
	// Create the vertex array.
	stTexVertex * pVertices = DEBUG_NEW stTexVertex [4];
	pVertices[0] = stTexVertex(left, bottom, z, 0.0f, 1.0f);
	pVertices[1] = stTexVertex(left, top, z, 0.0f, 0.0f);
	pVertices[2] = stTexVertex(right, bottom, z, 1.0f, 1.0f);
	pVertices[3] = stTexVertex(right, top, z, 1.0f, 0.0f);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		Log_Write(ILogger::LT_ERROR, 1, cString("Could not lock the  vertex buffer to update with the vertex data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		
		SafeDeleteArray(&pVertices);
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	stTexVertex * verticesPtr = (stTexVertex*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)pVertices, (sizeof(stTexVertex) * 4));

	// Unlock the vertex buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pVertexBuffer, 0);

	SafeDeleteArray(&pVertices);
	return true;
}

// *****************************************************************************
bool cSprite::InitializeShader()
{
	m_pShader = shared_ptr<IShader>(IShader::CreateTextureShader());
	return IShaderManager::GetInstance()->VGetShader(m_pShader, "Texture");
}

// *****************************************************************************
shared_ptr<ISprite> ISprite::CreateSprite()
{
	return shared_ptr<ISprite> (DEBUG_NEW cSprite());
}
