/*****************************************************************************
* Project: DPL5000gpr.S1 - Abschlussprüfung
* File   : GameManager.cs
* Date   : 06.04.2021
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	06.04.21	MS	Created,           
*	                +Callbacks: OnEnable, OnDisable, OnPlaySceneLoaded
*	                +Member-Variablen: m_lastPlayerPos,
*	                +Methoden: CalcAsteroidPos, InitAsteroids, FinishGame,
*	                           SaveHighscore, GetFilePath, LoadHighscore,
*	                           OnApplicationQuit,
*	                +Properties: AsteroidNumb, Score, Highscore,
*	                +Konstanten: M_I_ZERO_ASTEROIDS, M_S_FILE_NAME,
*	                             M_F_LEFT_BORDER, M_F_RIGHT_BORDER,
*	                             M_F_BACKWARD_BORDER, M_F_FORWARD_BORDER,
*	                             M_F_HEIGHT, M_F_PLAYER_DISTANCE,
*	                             M_F_TELEPORT_DISTANCE,
*	                             M_S_ASTEROID_PREFAB, M_S_ASTEROID_NAME,
*	                             M_S_PLAYER_PREFAB, M_S_SCENE_NAME
*
*   07.04.21    MS  +GameObjekte: m_HUD,
*                   +Konstanten: M_S_HUD_TAG, Ins Reine geschrieben
******************************************************************************/
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    /*************************************************************************/
    // Konstanten
    /*************************************************************************/
    /*-----------------------------------------------------------------------*/
    // Tags
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Tag, des Head-Up-Displays
    /// </summary>
    private const string M_S_HUD_TAG = "HUD";
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    // Szene
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Name der Spielszene
    /// </summary>
    private const string M_S_SCENE_NAME = "PlayScene";
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    // Asteroid-Koordinaten
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Konstante, für die Anzahl bei keinen vorhandenen Asteroiden
    /// </summary>
    private const byte M_I_ZERO_ASTEROIDS     =  0;

    /// <summary>
    /// Konstante, für die maximale Anzahl an Asteroiden
    /// </summary>
    private const byte M_I_ASTEROIDS_NUMB     =  3;

    /// <summary>
    /// Rechte Begrenzung für Asteroiden-Spawn-Punkte
    /// </summary>
    private const float M_F_RIGHT_BORDER      =  6.0f;

    /// <summary>
    /// Linke Begrenzung für Asteroiden-Spawn-Punke
    /// </summary>
    private const float M_F_LEFT_BORDER       = -6.0f;

    /// <summary>
    /// Vordere Begrenzung für Asteroiden-Spawn-Punkte
    /// </summary>
    private const float M_F_FORWARD_BORDER    =  4.0f;

    /// <summary>
    /// Hintere Begrenzung für Asteroiden-Spawn-Punkte
    /// </summary>
    private const float M_F_BACKWARD_BORDER   = -4.0f;

    /// <summary>
    /// Konstante Höhe
    /// </summary>
    private const float M_F_HEIGHT            =  0.0f;

    /// <summary>
    /// Minimale Distanz die beim Spawnen zur Spielfigur eingehalten werden
    /// muss.
    /// </summary>
    private const float M_F_PLAYER_DISTANCE   =  1.0f;

    /// <summary>
    /// Distanz um die der Asteroid beim Spawnen verschoben wird, 
    /// wenn er zu nah an der Spielfigur ist.
    /// </summary>
    private const float M_F_TELEPORT_DISTANCE =  1.1f;
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    // Prefabs
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Dateipfad des Spielfiguren-Prefabs
    /// </summary>
    private const string M_S_PLAYER_PREFAB   = "Prefabs/Player Controller";

    /// <summary>
    /// Dateipfad des Asteroiden-Prefabs
    /// </summary>
    private const string M_S_ASTEROID_PREFAB = "Prefabs/Asteroid";

    /// <summary>
    /// Name des instanzierten großen Asteroiden
    /// </summary>
    private const string M_S_ASTEROID_NAME   = "Big Asteroid";
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    //Datenverwaltung
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Dateipfad-Endung der Speicherdatei
    /// </summary>
    private const string M_S_FILE_NAME = "/score.dat";
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/



    /*************************************************************************/
    // Member-Variablen
    /*************************************************************************/
    /// <summary>
    /// Aktuelle Anzahl der Asteroiden
    /// </summary>
    [SerializeField] private byte m_iAsteroidNumb = 0;

    /// <summary>
    /// Aktueller Punktestand
    /// </summary>
    [SerializeField] private uint m_iScore        = 0;

    /// <summary>
    /// Bisher erreichter Höcshtpunktestand
    /// </summary>
    [SerializeField] private uint m_iHighscore    = 0;

    /// <summary>
    /// letzte Startposition der Spielfigur
    /// </summary>
    [SerializeField] private Vector3 m_lastPlayerPos = Vector3.zero;

    /*-----------------------------------------------------------------------*/
    // GameObjects
    /*-----------------------------------------------------------------------*/
    /// <summary>
    /// Head-Up-Display
    /// </summary>
    [SerializeField] private HeadUpDisplay m_HUD = null;
    /*-----------------------------------------------------------------------*/
    /*************************************************************************/



    /*************************************************************************/
    //Properties
    /*************************************************************************/
    /// <summary>
    /// Aktuelle Anzahl der Asteroiden
    /// </summary>
    public byte AsteroidNumb
    {
        get { return m_iAsteroidNumb; }
        set
        {
            if( value <= M_I_ZERO_ASTEROIDS ) value = M_I_ZERO_ASTEROIDS;
            if( value == M_I_ZERO_ASTEROIDS ) InitAsteroids();
            m_iAsteroidNumb = value;
        }
    }

    /// <summary>
    /// Aktueller Punktestand
    /// </summary>
    public uint Score
    {
        get { return m_iScore; }
        set
        {
            m_iScore = value;
            if (m_HUD != null) m_HUD.InvokeScoreSet(m_iScore);
        }
    }

    /// <summary>
    /// letzte Startposition der Spielfigur
    /// </summary>
    public uint Highscore
    {
        get { return m_iHighscore; }
        set
        {
            m_iHighscore = value;
            if (m_HUD != null) m_HUD.InvokeHighscoreSet(m_iHighscore);
        }
    }
    /*************************************************************************/



    /*************************************************************************/
    // Methoden
    /*************************************************************************/
    // Daten-Verwaltung
    /*************************************************************************/
    // Datei-Pfad
    /*************************************************************************/
    /// <summary>
    /// Methode, die Dateipfad der Speicherdatei zurückgibt
    /// </summary>
    /// <returns></returns>
    private string GetFilePath()
    {
        return $"{Application.dataPath}{M_S_FILE_NAME}";
    }
    /*************************************************************************/

    /*************************************************************************/
    // Speichern
    /*************************************************************************/
    /// <summary>
    /// Methode, die die aktuelle Punktzahl als Highscore speichert.
    /// </summary>
    /// <param name="_score"></param>
    private void SaveHighscore( uint _score )
    {
        try // versucht Highscore als savefile zu speichern
        {
            using( var fileStream = 
                            new FileStream( GetFilePath(), FileMode.Create ) )
            {
                using( var writer = new BinaryWriter( fileStream ) )
                {
                    writer.Write( _score );
                }
            }
        }
        catch { }
    }
    /*************************************************************************/

    /*************************************************************************/
    // Laden
    /*************************************************************************/
    /// <summary>
    /// Methode, die Highscore aus Speicherdatei ermittelt
    /// </summary>
    /// <returns></returns>
    private uint LoadHighscore()
    {
        uint score = 0;

        if( File.Exists( GetFilePath() ) ) // Fragt ab, ob savefile existiert
        {
            try // versucht Highscore von savefile zu laden
            {
                using( var fileStream = 
                               new FileStream( GetFilePath(), FileMode.Open ) )
                {
                    using( var reader = new BinaryReader( fileStream ) )
                    {
                        score = reader.ReadUInt32();
                    }
                }
            }
            catch { }
        }
        return score;
    }
    /*************************************************************************/
    /*************************************************************************/

    /*************************************************************************/
    // Asteroiden erstellen
    /*************************************************************************/
    /// <summary>
    /// Methode die Position des Asteroiden ermittelt und zurückgibt
    /// </summary>
    /// <returns></returns>
    private Vector3 CalcAsteroidPos()
    {
        // Position auf Spielfeld "auswürfeln"
        var position = 
            new Vector3( Random.Range( M_F_LEFT_BORDER, M_F_RIGHT_BORDER ), 
                         M_F_HEIGHT, 
                         Random.Range( M_F_BACKWARD_BORDER, 
                                       M_F_FORWARD_BORDER ) );

        //Distanz auf der X-Achse zur Spielfigur anpassen
        if(    position.x >= m_lastPlayerPos.x 
            && position.x < m_lastPlayerPos.x + M_F_PLAYER_DISTANCE )
        {
            position.x -= M_F_TELEPORT_DISTANCE;
        }
        else if(    position.x <= m_lastPlayerPos.x 
                 && position.x > m_lastPlayerPos.x - M_F_PLAYER_DISTANCE )
        {
            position.x += M_F_TELEPORT_DISTANCE;
        }

        //Distanz auf der Z-Achse zur Spielfigur anpassen
        if(    position.z >= m_lastPlayerPos.z 
            && position.z < m_lastPlayerPos.z + M_F_PLAYER_DISTANCE )
        {
            position.z -= M_F_TELEPORT_DISTANCE;
        }
        else if(    position.z <= m_lastPlayerPos.z 
                 && position.z > m_lastPlayerPos.z - M_F_PLAYER_DISTANCE )
        {
            position.z += M_F_TELEPORT_DISTANCE;
        }

        return position;
    }
    /*************************************************************************/

    /*************************************************************************/
    // Asteroiden Initialisieren
    /*************************************************************************/
    /// <summary>
    /// Methode, die zu Spielbeginn 3 große Asteroiden initialisiert
    /// </summary>
    private void InitAsteroids()
    {
        // Asteroid-Prefab initialisieren
        var asteroidPrefab = 
            Resources.Load( M_S_ASTEROID_PREFAB ) as GameObject;

        // Asteroiden aus Prefab instanzieren und Initialisieren
        for( int i = M_I_ZERO_ASTEROIDS; i < M_I_ASTEROIDS_NUMB; i++ )
        {
            var bigAsteriod = Instantiate( asteroidPrefab, CalcAsteroidPos(), 
                                           asteroidPrefab.transform.rotation );

            bigAsteriod.name = M_S_ASTEROID_NAME;

            if( bigAsteriod.TryGetComponent( out Asteroid _asteroid ) )
            {
                _asteroid.Initialize( SIZE_TYPE.AT_BIG );
            }
        }
    }
    /*************************************************************************/
    /*************************************************************************/

    /*************************************************************************/
    // Spiel beenden
    /*************************************************************************/
    /// <summary>
    /// Methode, die das Spiel beendet.
    /// </summary>
    public void FinishGame()
    {
        if( Score > Highscore ) SaveHighscore( Score ); // Highscore speichern
        SceneManager.LoadScene( M_S_SCENE_NAME ); // Szene neu laden
    }
    /*************************************************************************/

    /*************************************************************************/
    // Callbacks
    /*************************************************************************/
    /// <summary>
    /// Callback der ausgeführt wird, wenn die Szene läd
    /// </summary>
    /// <param name="_scene"></param>
    /// <param name="_mode"></param>
    private void OnPlaySceneLoaded( Scene _scene, LoadSceneMode _mode )
    {
        if( _scene.name == M_S_SCENE_NAME )
        {
            if( GameObject.FindWithTag( M_S_HUD_TAG )
                .TryGetComponent( out HeadUpDisplay _hud ) )
            {
                if(m_HUD == null)m_HUD = _hud;
            }

            Highscore = LoadHighscore(); // Highscore laden
            m_lastPlayerPos = Vector3.zero;

            // Spielfiguren-Prefab initialisieren
            var playerPrefab = 
                Resources.Load( M_S_PLAYER_PREFAB ) as GameObject;

            // Spielfigur instanzieren 
            var playerController = 
                Instantiate( playerPrefab, m_lastPlayerPos, 
                             playerPrefab.transform.rotation );

            InitAsteroids();
        }
    }
    /*************************************************************************/


    /*************************************************************************/
    // Engine-Methoden
    /*************************************************************************/
    // OnEnable
    /*************************************************************************/
    private void OnEnable()
    {
        SceneManager.sceneLoaded += OnPlaySceneLoaded; //Callback hinzufügen

    }
    /*************************************************************************/

    /*************************************************************************/
    // Start 
    /*************************************************************************/
    void Start()
    {
        //Punkte events aufrufen
        if (m_HUD != null) m_HUD.InvokeScoreSet(m_iScore);
        if (m_HUD != null) m_HUD.InvokeHighscoreSet(m_iHighscore);
    }
    /*************************************************************************/

    /*************************************************************************/
    // OnDisable
    /*************************************************************************/
    private void OnDisable()
    {
        SceneManager.sceneLoaded -= OnPlaySceneLoaded;

    }
    /*************************************************************************/

    /*************************************************************************/
    // OnApplicationQuit
    /*************************************************************************/
    private void OnApplicationQuit()
    {
        if( Score > Highscore ) SaveHighscore( Score );
    }
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
}
