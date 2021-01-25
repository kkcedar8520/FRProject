
#include"JHDXCore.h"
#include"JH_ShapePlane.h"
#include"JH_ShapeLine.h"
#include"JH_Map.h"
#include"QuadTree.h"
#include"RenderTarget.h"
#include"JHShapeBox.h"
#include"MaxObj.h"
#include"TextureMgr.h"
class Sample :public JHDXCore
{
public:
	JH_ShapePlane			m_MiniMap;
	D3DXMATRIX				m_matTopView;
	D3DXMATRIX				m_matTopProj;
	D3DXVECTOR3				m_NearPoint;
	RenderTarget			m_RenderTarget;

	ComPtr<ID3D11Texture2D> m_SplattingTex;
	ComPtr<ID3D11ShaderResourceView>	m_pSplSrv;
	Texture*							m_pTexture;

	shared_ptr<JHShapeBox>	m_pBox;

	map<int,shared_ptr<MaxObj>> m_ObjList;
	shared_ptr<MaxObj>		m_CurrentObj;
	
	D3D11_VIEWPORT	m_vp;
	float m_fTimer;
public:
	shared_ptr<JH_ShapeLine>m_DebugLine;
	shared_ptr<JH_Map>		m_Map;
	shared_ptr<HQuadTree>	m_QuadTree;
public:
	bool bAttach;
	bool bSplatting;
	int	CurrentObjIndex;
public:
	bool CreateMap(int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName=nullptr);
	int CreateObj(const TCHAR* pFileName,D3DXMATRIX& m_matWorld);
	void MapUpDown(SPHERE Sphere);
	HRESULT MapSplatting(SPHERE Sphere,const TCHAR* TextureFileName);
	void GetNearPoint();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	Sample();
	virtual ~Sample();
};

