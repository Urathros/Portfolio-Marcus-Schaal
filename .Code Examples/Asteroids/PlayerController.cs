/*****************************************************************************
* Project: DPL5000gpr.S1 - Abschlussprüfung
* File   : PlayerController.cs
* Date   : 30.03.2021
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	30.03.21	MS	Created,
*	                +RequireComponent: Sprite Renderer
*	                +Member-Variablen: m_inputControls, m_bIsGameRunning,
*	                                   m_bIsRunningLoop, m_fSpeed
*	                +Methoden: Awake, OnEnable, OnDisable, MoveActor
*	                +Callbacks: OnAccelerate,
*	                +Koroutinen: LoopMovement,
*	                Action-Input-Plugin hinzugefügt & Beschleunigungsmechanik
*
*   31.03.21    MS  +Callbacks: OnRotation,
*                   +Member-Variablen: m_fRotaAngle, m_bIsRotaLoop, 
*                                      m_fRotaInput,
*                                      m_bIsAccelerationLoop, m_fSpeedInput
*                   +Koroutinen: LoopRotation,
*                   +Konstanten: M_F_ROTA_X, M_F_ROTA_Y, M_F_ROTA_CONST,
*                                M_F_SPEED_MIN_VAL, M_F_SPEED_MAX_VAL,
*                   +Methoden: RotateActor, CalcDirection,
*                   Rotation und Richtungsänderung entwickelt,
*                   Koroutinen statt Update
*                   +Properties: Speed
*
*   01.04.21    MS  +Methoden: OnTriggerExit, TeleportActor,
*                   +RequireComponent: Rigidbody, BoxCollider,
*                   +Konstanten: M_F_RIGHT_BORDER, M_F_LEFT_BORDER, 
*                                M_F_FORWARD_BORDER, M_F_BACKWARD_BORDER,
*                                M_F_HEIGHT, 
*                                M_F_RIGHT_TELEPORT_COORD, 
*                                M_F_LEFT_TELEPORT_COORD, 
*                                M_F_FORWARD_TELEPORT_COORD,
*                                M_F_BACKWARD_TELEPORT_COORD, 
*                                M_S_TAG_PLAYING_FIELD, 
*                                M_F_ZERO_ROTA,
*                   Außenbegrenzung für Spielfeld entwickelt,
*                   -Koroutine: LoopMovement,
*                   -Member-Variablen: m_bIsGameRunning,
*                   nach Actor verschoben: M_F_SPEED_MIN_VAL, 
*                                          M_F_SPEED_MAX_VAL, m_fSpeed, 
*                                          m_direction, Speed, MoveActor,
*                   von Actor abgeleitet
*
*   02.04.21    MS  nach Actor verschoben: CalcDirection, M_F_ZERO_ROTA,
*                                          TeleportActor,
*                                          M_F_HEIGHT, 
*                                          M_S_TAG_PLAYING_FIELD
*
*   06.04.21    MS  +Callbacks: OnShoot,
*                   +Konstanten: M_S_LASER_PREFAB, M_F_DIR_PERCENT,
*                   -Member-Variable: m_bIsMoveLoop
*
*   07.04.21    MS  Ins Reine geschrieben
******************************************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerController : Actor
{
    /*************************************************************************/
    // Konstanten
    /*************************************************************************/
    /*-----------------------------------------------------------------------*/
    // Laser
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante die das Abstands-Verhältnis der gespawnten Laser-Munition
    /// zum Raumschiff bestimmt.
    /// </summary>
    private const float M_F_DIR_PERCENT   = 0.3f; 

    /// <summary>
    /// Konstante des Prefab der Laser-Munition.
    /// </summary>
    private const string M_S_LASER_PREFAB = "Prefabs/Laser Bullet";
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Drehung
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Drehungskonstante
    /// </summary>
    private const float M_F_ROTA_CONST = 250.0f;
    
    /// <summary>
    /// X-Konstante des Drehungsvektors
    /// </summary>
    private const float M_F_ROTA_X     = -90.0f;

    /// <summary>
    /// Y-Konstante des Drehungsvektors
    /// </summary>
    private const float M_F_ROTA_Y     =   0.0f;
    /*-----------------------------------------------------------------------*/


    /*-----------------------------------------------------------------------*/
    // Spielfeld
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante, der rechten Außenbegrenzung des Spielfeldes.
    /// </summary>
    private const float M_F_RIGHT_BORDER            =  6.9f;

    /// <summary>
    /// Konstante, der linken Außenbegrenzung des Spielfeldes.
    /// </summary>
    private const float M_F_LEFT_BORDER             = -6.9f;

    /// <summary>
    /// Konstante, der vorderen Außenbegrenzung des Spielfeldes.
    /// </summary>
    private const float M_F_FORWARD_BORDER          =  5.2f;

    /// <summary>
    /// Konstante, der hinteren Außenbegrenzung des Spielfeldes.
    /// </summary>
    private const float M_F_BACKWARD_BORDER         = -5.2f;


    /// <summary>
    /// Konstante Teleportkoordinate am rechten Spielfeldrand.
    /// </summary>
    private const float M_F_RIGHT_TELEPORT_COORD    =  6.65f;

    /// <summary>
    /// Konstante Teleportkoordinate am linke Spielfeldrand.
    /// </summary>
    private const float M_F_LEFT_TELEPORT_COORD     = -6.65f;

    /// <summary>
    /// Konstante Teleportkoordinate am vordere Spielfeldrand.
    /// </summary>
    private const float M_F_FORWARD_TELEPORT_COORD  =  4.95f;

    /// <summary>
    /// Konstante Teleportkoordinate am hinteren Spielfeldrand.
    /// </summary>
    private const float M_F_BACKWARD_TELEPORT_COORD = -4.95f;
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/




    /*************************************************************************/
    // Member-Variablen
    /*************************************************************************/
    /*-----------------------------------------------------------------------*/
    // Transform
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Gleitkommazahl, mit dem Wert des Action Inputs für Drehungen.
    /// </summary>
    [SerializeField] private float m_fSpeedInput = 0.0f;

    /// <summary>
    /// Gleitkommazahl, mit dem Wert des Action Inputs für Drehungen.
    /// </summary>
    [SerializeField] private float m_fRotaInput  = 0.0f;

    /// <summary>
    /// Gleitkommazahl, die die den bisherigen Drehwinkel enthält.
    /// </summary>
    [SerializeField] private float m_fRotaAngle  = 0.0f;
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    // Loops
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Boolean, der anzeigt, ob die "Beschleunigungs"-Koroutine aktiv ist. 
    /// </summary>
    [SerializeField] private bool m_bIsAccelerationLoop = false;

    /// <summary>
    /// Boolean, der anzeigt, ob die "Dreh"-Koroutine aktiv ist. 
    /// </summary>
    [SerializeField] private bool m_bIsRotaLoop         = false;
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    //Input
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Beinhaltet "Input-Actions" zur Tastatureingabe.
    /// </summary>
    [SerializeField] private PlayerInputControls m_inputControls = null;
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/



    /*************************************************************************/
    // Methoden
    /*************************************************************************/
    // Figur drehen
    /*************************************************************************/
    /// <summary>
    /// Methode, die die akutelle Drehung der Figur zurückgibt.
    /// </summary>
    /// <returns></returns>
    private Quaternion RotateActor()
    {
        //Drehwinkel aus Input berechnen
        m_fRotaAngle += m_fRotaInput * M_F_ROTA_CONST * Time.deltaTime;

        // Winkel an Transform-Drehung übergeben
        return Quaternion.Euler( M_F_ROTA_X, M_F_ROTA_Y, m_fRotaAngle );
    }
    /*************************************************************************/



    /*************************************************************************/
    // Koroutinen
    /*************************************************************************/
    // Beschleunigungs-Schleife
    /*************************************************************************/
    /// <summary>
    /// Koroutine, die für die Beschleunigung der Spielfigur sorgt, 
    /// solange der Beschleunigungs-Input über dem Mindestwert liegt.
    /// </summary>
    /// <returns></returns>
    public IEnumerator LoopAcceleration()
    {
        if( !m_bIsAccelerationLoop )
        {
            m_bIsAccelerationLoop = true;

            while( m_fSpeedInput != M_F_SPEED_MIN_VAL )
            {
                //Beschleunigungs-Berechnung
                Speed += m_fSpeedInput  * Time.deltaTime;

                yield return new WaitForEndOfFrame();
            }

            m_bIsAccelerationLoop = false;
        }
    }
    /*************************************************************************/


    /*************************************************************************/
    // Drehungs-Schleife
    /*************************************************************************/
    /// <summary>
    /// Koroutine, die für die Drehung der Spielfigur sorgt,
    /// solange der Drehungs-Input über dem Mindestwert liegt.
    /// </summary>
    /// <returns></returns>
    public IEnumerator LoopRotation()
    {
        if( !m_bIsRotaLoop )
        {
            m_bIsRotaLoop = true;

            while( m_fRotaInput != M_F_ZERO_ROTA )
            {
                // Drehung ermitteln
                transform.rotation = RotateActor(); 

                // neue Richtung ermitteln
                m_direction = CalcDirection(m_fRotaAngle);

                yield return new WaitForEndOfFrame();
            }

            m_bIsRotaLoop = false;
        }
    }
    /*************************************************************************/
    /*************************************************************************/

    /*************************************************************************/
    // Callbacks
    /*************************************************************************/
    // Bei Beschleunigung
    /*************************************************************************/
    /// <summary>
    /// Callback, der bei gedrückthalten der Beschleunigungs-Tasten
    /// die Beschleunigung der Spielfigur auslöst.
    /// </summary>
    /// <param name="_speedInput"></param>
    private void OnAccelerate( float _speedInput )
    {
        m_fSpeedInput = _speedInput;

        if( gameObject.activeSelf )StartCoroutine( LoopAcceleration() );
    }
    /*************************************************************************/

    /*************************************************************************/
    // Bei Drehung
    /*************************************************************************/
    /// <summary>
    /// Callback, der bei gedrückthalten, der Drehungs-Tasten die Drehung
    /// der Spielfigur auslöst.
    /// </summary>
    /// <param name="_rotaInput"></param>
    private void OnRotation( float _rotaInput )
    {
        m_fRotaInput = _rotaInput;

        if( gameObject.activeSelf ) StartCoroutine(LoopRotation());
    }
    /*************************************************************************/

    /*************************************************************************/
    // Beim Schießen
    /*************************************************************************/
    /// <summary>
    /// Callback, das bei Drücken der Schuss-Taste ein Laser-Projektil
    /// vor der Spitze der Spielfigur in ihre Blickrichtung verschießt.
    /// </summary>
    private void OnShoot()
    {
        // Prefab initialisieren
        var prefab = Resources.Load( M_S_LASER_PREFAB ) as GameObject;

        // Laser initialisieren
        var laserBullet = Instantiate(   prefab, transform.position 
                                       + ( m_direction * M_F_DIR_PERCENT ), 
                                       prefab.transform.rotation );

        if( laserBullet.TryGetComponent( out LaserBullet _laserBullet ) )
        {
            _laserBullet.Initialize( m_direction );
        }
    }
    /*************************************************************************/
    /*************************************************************************/

    /*************************************************************************/
    // Engine-Methoden
    /*************************************************************************/
    // Awake
    /*************************************************************************/
    private void Awake()
    {
        m_inputControls = new PlayerInputControls(); //Tasteneingabe init.
    }
    /*************************************************************************/

    /*************************************************************************/
    // OnEnable
    /*************************************************************************/
    private void OnEnable()
    {
        m_inputControls.Enable(); //Tasteneingabe aktivieren

        // Callbacks hinzufügen
        m_inputControls.Standard.Acceleration.performed +=
            context => OnAccelerate( context.ReadValue<float>() );

        m_inputControls.Standard.Acceleration.canceled +=
            context => OnAccelerate( context.ReadValue<float>() );


        m_inputControls.Standard.Rotation.performed +=
            context => OnRotation(   context.ReadValue<float>() );

        m_inputControls.Standard.Rotation.canceled +=
            context => OnRotation(   context.ReadValue<float>() );

        m_inputControls.Standard.Shoot.performed +=
            context => OnShoot();
    }
    /*************************************************************************/

    /*************************************************************************/
    // Start
    /*************************************************************************/
    void Start()
    {
        // Variablen initialisieren
        Speed = 0.0f;
        m_fRotaAngle = -90.0f;
        m_direction = CalcDirection(m_fRotaAngle);

        m_fRightBorder = M_F_RIGHT_BORDER;
        m_fLeftBorder = M_F_LEFT_BORDER;
        m_fForwardBorder = M_F_FORWARD_BORDER;
        m_fBackwardBorder = M_F_BACKWARD_BORDER;
        m_fRightTeleportCoord = M_F_RIGHT_TELEPORT_COORD;
        m_fLeftTeleportCoord = M_F_LEFT_TELEPORT_COORD;
        m_fForwardTeleportCoord = M_F_FORWARD_TELEPORT_COORD;
        m_fBackwardTeleportCoord = M_F_BACKWARD_TELEPORT_COORD;
        
        m_bIsAccelerationLoop = false;
        m_bIsRotaLoop = false;
    }
    /*************************************************************************/

    /*************************************************************************/
    // OnTriggerExit
    /*************************************************************************/
    private void OnTriggerExit(Collider _other)
    {
        TeleportActor(_other); //vom einen Rand des Spielfelds zum anderen
    }
    /*************************************************************************/

    /*************************************************************************/
    // Update
    /*************************************************************************/
    void Update()
    {
        transform.position += MoveActor(); // Gameobjekt konstant bewegen 
    }
    /*************************************************************************/

    /*************************************************************************/
    // OnDisable
    /*************************************************************************/
    private void OnDisable()
    {
        // Callbacks gegenläufig entfernen
        m_inputControls.Standard.Shoot.performed -=
               context => OnShoot();

        m_inputControls.Standard.Rotation.canceled -=
            context => OnRotation(context.ReadValue<float>());

        m_inputControls.Standard.Rotation.performed -=
            context => OnRotation(context.ReadValue<float>());


        m_inputControls.Standard.Acceleration.canceled -=
            context => OnAccelerate(context.ReadValue<float>());

        m_inputControls.Standard.Acceleration.performed -=
            context => OnAccelerate(context.ReadValue<float>());

        m_inputControls.Disable(); // Tasteneingabe deaktivieren
    }
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
}