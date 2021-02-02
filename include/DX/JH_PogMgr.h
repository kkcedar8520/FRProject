//#pragma once
//#include "KG_Std.h"
//namespace JH
//{
//	struct PogCB
//	{
//		D3DXVECTOR4			g_ClipPlane;
//		D3DXVECTOR4			g_FogColor;
//		D3DXVECTOR4			g_FogInfo;
//	};
//	class JH_PogMgr :public Singleton<JH_PogMgr>
//	{
//		protected:
//			Microsoft::WRL::ComPtr<ID3D11Buffer> m_pPogCB;
//			PogCB								 m_cbPog;
//		public:
//			void Create(ID3D11Device* pd3device, ID3D11DeviceContext* pContext, D3DXVECTOR4 ClipPalne, D3DXVECTOR4 FogColor, D3DXVECTOR4 FogInfo);
//
//			Microsoft::WRL::ComPtr<ID3D11Buffer> GetBuffer();
//		public:
//			JH_PogMgr();
//			virtual ~JH_PogMgr();
//	};
//}
//
//#define I_PogMgr JH_PogMgr::GetInstance()