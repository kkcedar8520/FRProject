struct DS_OUTPUT
{
	float4 vPosition  : SV_POSITION;
	// TODO: 다른 내용을 변경/추가합니다.
};

// 제어점을 출력합니다.
struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : WORLDPOS; 
};

// 패치 상수 데이터를 출력합니다.
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor; // 예를 들어 쿼드 도메인에 대해 [4]입니다.
	float InsideTessFactor			: SV_InsideTessFactor; // 예를 들어 쿼드 도메인에 대해 Inside[2]입니다.
	// TODO: 다른 내용을 변경/추가합니다.
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT Output;

	Output.vPosition = float4(
		patch[0].vPosition*domain.x+patch[1].vPosition*domain.y+patch[2].vPosition*domain.z,1);

	return Output;
}
