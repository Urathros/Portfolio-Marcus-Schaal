/*****************************************************************************
* Project: DPL5000gpr.S1 - Abschlussprüfung
* File   : Actor.cs
* Date   : 01.04.2021
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	01.04.21	MS	Created, 
*	                Klasse abstrakt gesetzt,
*	                aus PlayerController übernommen: M_F_SPEED_MIN_VAL, 
*	                                                 M_F_SPEED_MAX_VAL, 
*	                                                 m_fSpeed, m_direction, 
*	                                                 Speed, MoveActor
*
*   02.04.21    MS  aus PlayerController übernommen: CalcDirection, 
*                                                    M_F_ZERO_ROTA,
*                                                    TeleportActor,
*                                                    M_F_RIGHT_BORDER, 
*                                                    M_F_LEFT_BORDER, 
*                                                    M_F_FORWARD_BORDER, 
*                                                    M_F_BACKWARD_BORDER,
*                                                    M_F_HEIGHT, 
*                                                    M_F_RIGHT_TELEPORT_COORD, 
*                                                    M_F_LEFT_TELEPORT_COORD, 
*                                                   M_F_FORWARD_TELEPORT_COORD,
*                                                  M_F_BACKWARD_TELEPORT_COORD, 
*                                                    M_S_TAG_PLAYING_FIELD, 
*                   +Konstanten: M_F_REVERSED_TELEPORT_FACTOR
*                   
*	06.04.21	MS	RequireComponents aus abgeleiteten Klassen in diese 
*	                verlagert
*
*   07.04.21    MS  Ins Reine geschrieben
******************************************************************************/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[ RequireComponent( typeof( SpriteRenderer ) ) ]
[ RequireComponent( typeof( Rigidbody      ) ) ] 
[ RequireComponent( typeof( BoxCollider    ) ) ] 
public abstract class Actor : MonoBehaviour
{
    /*************************************************************************/
    // Konstanten
    /*************************************************************************/
    /*-----------------------------------------------------------------------*/
    // Geschwindigkeit
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante für die Minimalgeschwindigkeit der Spielfigur.
    /// </summary>
    protected const float M_F_SPEED_MIN_VAL = 0.0f;

    /// <summary>
    /// Konstante für die Maximalgeschwindigkeit der Spielfigur.
    /// </summary>
    private const float M_F_SPEED_MAX_VAL   = 5.0f;
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Drehung
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Drehungskonstante für Stillstand.
    /// </summary>
    protected const float M_F_ZERO_ROTA = 0.0f;
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Spielfeld
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante Höhe der Spielfigur auf dem Spielfeld.
    /// </summary>
    private const float M_F_HEIGHT                   = 0.0f;
    
    /// <summary>
    /// Konstanter Faktor, 
    /// der Koordinaten für den gegenüberliegenden Spielfeldrand setzt.
    /// </summary>
    private const float M_F_REVERSED_TELEPORT_FACTOR = -1.0f;
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Tags
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante des Tags für das Spielfeld.
    /// </summary>
    protected const string M_S_TAG_PLAYING_FIELD = "Playing Field";
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/



    /*************************************************************************/
    // Member-Variablen
    /*************************************************************************/
    /*-----------------------------------------------------------------------*/
    // Transform
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Gleitkommazahl, die die aktuelle Geschwindigkeit der Spielfigur angibt.
    /// </summary>
    [SerializeField] private float m_fSpeed        = 0.0f;

    /// <summary>
    /// 3D-Vektor, der die Blickrichtung des Raumschiffs angibt.
    /// </summary>
    [SerializeField] protected Vector3 m_direction = Vector3.zero;
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Spielfeld
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante, der rechten Außenbegrenzung des Spielfeldes.
    /// </summary>
    protected float m_fRightBorder           = 0.0f;

    /// <summary>
    /// Konstante, der linken Außenbegrenzung des Spielfeldes.
    /// </summary>
    protected float m_fLeftBorder            = 0.0f;

    /// <summary>
    /// Konstante, der vorderen Außenbegrenzung des Spielfeldes.
    /// </summary>
    protected float m_fForwardBorder         = 0.0f;

    /// <summary>
    /// Konstante, der hinteren Außenbegrenzung des Spielfeldes.
    /// </summary>
    protected float m_fBackwardBorder        = 0.0f;

    /// <summary>
    /// Konstante Teleportkoordinate am rechten Spielfeldrand.
    /// </summary>
    protected float m_fRightTeleportCoord    = 0.0f;

    /// <summary>
    /// Konstante Teleportkoordinate am linke Spielfeldrand.
    /// </summary>
    protected float m_fLeftTeleportCoord     = 0.0f;

    /// <summary>
    /// Konstante Teleportkoordinate am vordere Spielfeldrand.
    /// </summary>
    protected float m_fForwardTeleportCoord  = 0.0f;

    /// <summary>
    /// Konstante Teleportkoordinate am hinteren Spielfeldrand.
    /// </summary>
    protected float m_fBackwardTeleportCoord = 0.0f;
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/




    /*************************************************************************/
    // Properties
    /*************************************************************************/
    /// <summary>
    /// Property, die die aktuelle Geschwindigkeit der Spielfigur angibt.
    /// </summary>
    public float Speed
    {
        get { return m_fSpeed; }
        set
        {
            /*---------------------------------------------------------------*/
            // Wert-Begrenzung
            /*---------------------------------------------------------------*/
            if(     value > M_F_SPEED_MIN_VAL
                 && value <= M_F_SPEED_MAX_VAL ) m_fSpeed = value;

            // max. Geschwindigkeit
            else if( value > M_F_SPEED_MAX_VAL ) m_fSpeed = M_F_SPEED_MAX_VAL;

            // min. Geschwindigkeit
            else m_fSpeed = M_F_SPEED_MIN_VAL;
            /*---------------------------------------------------------------*/
        }
    }
    /*************************************************************************/



    /*************************************************************************/
    // Methoden
    /*************************************************************************/
    // Figur bewegen
    /*************************************************************************/
    /// <summary>
    /// Methode, die einen Bewegungswert zur Laufzeit in eine Richtung 
    /// zurückgibt.
    /// </summary>
    /// <returns></returns>
    protected Vector3 MoveActor()
    {
        return m_direction * Speed * Time.deltaTime;
    }
    /*************************************************************************/

    /*************************************************************************/
    // Richtung berechnen
    /*************************************************************************/
    /// <summary>
    /// Methode, die eine Blickrichtung auf Basis der Drehung der Y-Achse
    /// zurückgibt.
    /// </summary>
    /// <param name="_rotaAngle"></param>
    /// <returns></returns>
    protected Vector3 CalcDirection( float _rotaAngle )
    {
        return Quaternion.Euler( new Vector3( M_F_ZERO_ROTA, _rotaAngle,
                                              M_F_ZERO_ROTA ) )
               * -Vector3.forward;
    }

    /*************************************************************************/
    // Figur an andere Spielfeld-Seite teleportieren
    /*************************************************************************/
    /// <summary>
    /// Methode, die das Gameobjekt, bei verlassen des Spielfelds auf die
    /// andere Seite teleportiert.
    /// </summary>
    /// <param name="_other"></param>
    protected void TeleportActor( Collider _other )
    {
        if( _other.tag == M_S_TAG_PLAYING_FIELD )
        {
            /*---------------------------------------------------------------*/
            // 2D sichern
            /*---------------------------------------------------------------*/
            if(    transform.position.y > M_F_HEIGHT
                || transform.position.y < M_F_HEIGHT )
            {
                transform.position = new Vector3( transform.position.x,
                                                  M_F_HEIGHT,
                                                  transform.position.z  );
                return;
            }
            /*---------------------------------------------------------------*/

            /*---------------------------------------------------------------*/
            //Seiten
            /*---------------------------------------------------------------*/
            // rechte Seite
            else if( transform.position.x >= m_fRightBorder )
            {
                transform.position = new Vector3( m_fLeftTeleportCoord,
                                                  M_F_HEIGHT,
                                                  transform.position.z  );
            }

            // linke Seite
            else if( transform.position.x <= m_fLeftBorder )
            {
                transform.position = new Vector3( m_fRightTeleportCoord,
                                                  M_F_HEIGHT,
                                                  transform.position.z   );
            }

            // vordere Seite
            else if( transform.position.z >= m_fForwardBorder )
            {
                transform.position = new Vector3( transform.position.x,
                                                  M_F_HEIGHT,
                                                  m_fBackwardTeleportCoord );
            }

            // hintere Seite
            else if( transform.position.z <= m_fBackwardBorder )
            {
                transform.position = new Vector3( transform.position.x,
                                                  M_F_HEIGHT,
                                                  m_fForwardTeleportCoord );
            }
            /*---------------------------------------------------------------*/

            /*---------------------------------------------------------------*/
            // schwerwiegender Fehler
            /*---------------------------------------------------------------*/
            else
            {
                transform.position *= M_F_REVERSED_TELEPORT_FACTOR;
            }
            /*---------------------------------------------------------------*/
        }
    }
    /*************************************************************************/
    /*************************************************************************/
}