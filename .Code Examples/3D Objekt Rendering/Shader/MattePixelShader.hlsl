/*****************************************************************************/
//Vertex-Output-Struktur
/*****************************************************************************/
struct Input
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
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

Texture2D ObjTex;
SamplerState ObjSampler;

/*****************************************************************************/
// Pixel-Shader
/*****************************************************************************/
float4 main(Input input) : SV_TARGET
{
    //normalisieren, damit bei Scaling Lichtberechnung funktioniert
    input.normal = normalize(input.normal);
    
    //Farbe aus mehreren Dingen bilden
    float4 diffColor = ObjTex.Sample(ObjSampler, input.uv) 
                       * input.color; //Grundfarbe ist Textur
    float3 finColor;
    
    finColor = diffColor * light.ambient; //Farbe * Beleuchtung
    finColor += saturate(dot(light.direction, input.normal) 
                * light.diffuse * diffColor); //Lichteinfall
    
    //return diffColor;
    return float4(finColor, diffColor.a); //entgültige Farbe + Texturalpha
}
/*****************************************************************************/