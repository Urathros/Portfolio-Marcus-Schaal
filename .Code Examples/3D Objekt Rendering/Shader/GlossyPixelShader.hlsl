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

//Textur
Texture2D ObjTex;
SamplerState ObjSampler;

/*****************************************************************************/
// Pixel-Shader
/*****************************************************************************/
float4 main(Input input) : SV_TARGET
{
    //normalisieren, damit bei Scaling Lichtberechnung funktioniert
    input.normal = normalize(input.normal);
    
    float specularPower = 8.0;
    float glossyness = 1;
    float4 specularColor = float4(1, 1, 1, 1);
    
    //Farbe aus mehreren Dingen bilden
    float4 diffColor = ObjTex.Sample(ObjSampler, input.uv) 
                       * input.color; //Grundfarbe ist Textur
    
    //blinn
    float3 reflectionVector = reflect(-light.direction, input.normal) ;
    float specRef = specularColor * pow( max(0, 
                    dot(input.viewDirection, reflectionVector) ), 
                    specularPower) * glossyness;
    
    float3 finColor;
    finColor = diffColor * light.ambient + specRef ; //Farbe * Beleuchtung
    finColor += saturate( dot(light.direction, input.normal) 
                          * light.diffuse * diffColor ); //Lichteinfall
    
    
    return float4(finColor, diffColor.a); //entgültige Farbe + Texturalpha
}
/*****************************************************************************/