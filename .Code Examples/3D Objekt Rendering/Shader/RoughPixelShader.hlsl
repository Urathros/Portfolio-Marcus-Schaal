/*****************************************************************************/
//Vertex-Output-Struktur
/*****************************************************************************/
struct Input
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};
/*****************************************************************************/

/*****************************************************************************/
// Licht-Struktur
/*****************************************************************************/
struct Light
{
    float3 direction;
    float4 ambient;
    float4 diffuse;
};
/*****************************************************************************/

/*****************************************************************************/
//per Frame (Light-Buffer)
/*****************************************************************************/
cbuffer FrameLightCB
{
    Light light;
};
/*****************************************************************************/

Texture2D MainTex : register(t0);
SamplerState ObjSampler : register(s0);
Texture2D NormMapTex : register(t1);
SamplerState NomrMapSampler : register(s1);
float shininess = 200;
float specularIntensity = 1;
float glossy = 1.0;


void CalcNormal(inout Input input, float4 normColor)
{
    input.normal = normalize(input.normal);
    input.tangent = normalize(input.tangent);
    input.binormal = normalize(input.binormal);
    
    normColor = normColor * 2.0 - 1.0f;
    float3 normal = normColor.r * input.tangent + normColor.g * input.binormal + normColor.b * input.normal;
    input.normal = normalize(normal);
}

/*****************************************************************************/
// Pixel-Shader
/*****************************************************************************/
float4 main(Input input) : SV_TARGET
{
    //normalisieren, damit bei Scaling Lichtberechnung funktioniert
    
    float specularPower = 8.0;
    float glossyness = 1;
    float4 specularColor = float4(1, 1, 1, 1);
    CalcNormal(input, NormMapTex.Sample(NomrMapSampler, input.uv) * input.color);
    
    //Farbe aus mehreren Dingen bilden
    float4 diffColor = MainTex.Sample(ObjSampler, input.uv) * input.color; 
     
    float3 finColor;
    finColor = diffColor * light.ambient /*+ specRef */; //Farbe * Beleuchtung
    finColor += saturate(dot(light.direction, input.normal) * light.diffuse * diffColor ); //Lichteinfall
    
    //return diffColor;
    return float4(finColor, diffColor.a); //entgültige Farbe + Texturalpha
}
/*****************************************************************************/