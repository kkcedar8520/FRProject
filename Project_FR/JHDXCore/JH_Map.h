#pragma once

#include"TextureMgr.h"
#include"NormalMap.h"
#include"LightMgr.h"
#include"JH_Model.h"
#include"JHCamera.h"
#include"QuadTree.h"
#include"JH_SkyBox.h"

	struct CB_SPT
	{
		D3DXVECTOR4 MapSubData;
		CB_SPT()
		{
			MapSubData = D3DXVECTOR4(0, 0, 0, 0);
		}
	};

	struct SplattTextureDesc
	{
		int TexNum;
		float Alpha;
	};
	struct MapDesc
	{
		int iColumNum;
		int iRowNum;
		const TCHAR* TextureFileName;
		const TCHAR* ShaderFileName;
		const TCHAR* pNormMapFileName;
		const TCHAR* pHeightFileName;
		float fSellDistance;
		float fScaleHeight;
		//�ؽ�Ʈ����
		//���̴� 
		//�� ����
		//��
		//��
		//���� �� ��

	};

	class JH_Map :public JH_Model
	{
	public:
		bool	m_bMapEdit;

		//SPlattingData
		std::map<int, Texture*>											 m_vSplattTextureList;
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>	 m_vSplattSRVList;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>				 m_pSplattAlphaSRV;
		std::wstring													 m_AlphaTextureName;
		//
		CB_SPT m_CBSubData;
		Microsoft::WRL::ComPtr<ID3D11Buffer>							 m_CBSub;
	public:
		//SkyBox
		std::shared_ptr<JH_SkyBox>										 m_SkyBox;
		
		const TCHAR*													 m_pSPTAFile;
		
		//QuadTree
		JHCamera*														m_pCamera;
		shared_ptr<HQuadTree>											m_QuadTree;
	public:
		D3DXVECTOR3 m_vEyePos;
		MapDesc m_MapDesc;
		int m_iColumNum;
		int m_iRowNum;
		int m_iVertices;
		int m_iCellCol;
		int m_iCellRow;
		int m_iCellCount;
		float m_fCellDistance;
		float m_fScaleHeight;
		T_STR  m_TextureFileName;
		T_STR  m_ShaderFileName;
		T_STR  m_HegithFileName;
		T_STR m_LightFileName;


		D3DXVECTOR3 m_CharPos;

	public:
		std::vector<float> m_vHeightList;
	public:
		float GetHeight(float fX, float fZ);
		float GetHeightMap(int iRow, int iCol);

		bool CreateMap(int iWidth,
			int iHeight,
			int iCellCount,
			int iCellSize,
			const TCHAR* pTexturFileName,
			const TCHAR* pNormalMapFileName = nullptr,
			const TCHAR* pHeightMapFileName = nullptr,
			const TCHAR* pLightShaderName = nullptr,
			bool bQuad = true);
		bool CreateQuadTree();

		HRESULT Load(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext);
		HRESULT LoadMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* Context, const TCHAR* ShaderFileName = L"../../data/shader/DefaultShader.txt", const TCHAR* TexFileName = nullptr, const CHAR* VSName = "VS", const CHAR* PSName = "PS");
		HRESULT CreateHeightMap(ID3D11Device* pD3D11Device, ID3D11DeviceContext* pD3D11DeviceContext, const TCHAR* TextureFileName);
		bool CreateSkyBox(const TCHAR* pLoadShaderFile,
			const TCHAR* pLoadTextureString);
		float Lerp(float fStart, float fEnd, float fTangent);

		void SetMapDesc(const TCHAR* TextureFileName,
			const TCHAR* ShaderFileName,
			int ColumNum,
			int RowNum,
			float fSellDistance,
			float fScaleHeight);
		void SetMatrix(D3DXMATRIX* matWorld,
			D3DXMATRIX* matView,
			D3DXMATRIX* matProj)override;


		void SetSplattingAlphaShaderResouceView(ID3D11ShaderResourceView* pSrv);
		
		//�븻�� ���� ���� ���

	//�� ���� �Լ�
		INT			AddSplattTexture(const TCHAR* pFileName, int Num, float Alpha = 0.0f);
		D3DXVECTOR3 GetCharPos(){ return m_CharPos; }
		void		SetCharPos(D3DXVECTOR3 vPos) { m_CharPos = vPos; }
	//
		void		SetCamera(JHCamera* Camera) { m_pCamera = Camera; }
		JHCamera*	GetCamera()					{ return m_pCamera; }
		void		UpDownMap(UINT Index, float Value);
		void		FlattingMap(UINT Index);
	public:
	
	public:
		HRESULT		CreateInputLayout()override;
		HRESULT		CreateVertexData()override;
		HRESULT		CreateIndexData()override;
		HRESULT		LoadTexture(const TCHAR* pszTexFileName, const TCHAR* pszNormalTexName = nullptr)override;
		bool		Render()override;
		bool		Frame()override;
		bool		Release()override;

	public:
		bool NoneLightRenderSet(JHCamera* pCamera);
	public:
		JH_Map();
		virtual ~JH_Map();
	};
