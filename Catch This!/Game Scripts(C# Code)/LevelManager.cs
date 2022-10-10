using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
    public GameObject playerPrefab;
    public GameObject explosionPrefab;
    public GameObject[] playerPrefabs;
    public GameObject bombPowerPrefab;
    public GameObject speedPowerPrefab;
    public GameObject healthPowerPrefab;
    private bool isPaused;

    void Start()
    {
        isPaused = false;
    }
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (isPaused)
            {
                isPaused = false;
                GameObject.Find("GameCanvas").transform.Find("PauseMenu").gameObject.SetActive(false);
            }
            else
            {
                isPaused = true;
                GameObject.Find("GameCanvas").transform.Find("PauseMenu").gameObject.SetActive(true);
            }
        }
    }

    private void Awake()
    {
        //SpawnPlayer();
        Invoke("SpawnPlayer", 2);
    }
    public void SpawnPlayer()
    {
        Transform spawnPointLocation = GameObject.Find(GameInfo.spawnPointName).transform;
        GameObject currentPlayerPrefab = playerPrefabs[GameInfo.prefabNumber];
        GameObject currentPlayer = PhotonNetwork.Instantiate(currentPlayerPrefab.name,
                                  new Vector3(spawnPointLocation.position.x,
                                              spawnPointLocation.position.y,
                                              0),
                                  Quaternion.identity, 0);
    }
    public void QuitToMenu()
    {
        PhotonNetwork.LeaveRoom();
    }

    public void OnLeftRoom()
    {
        GameObject.FindGameObjectWithTag("Music").GetComponent<PlayMenuMusic>().PlayMusic();
        SceneManager.LoadScene(1);
    }

    [PunRPC]
    public void SpawnPowerUp(Vector2 location, int type)
    {
        /*
        if (type == 1)
        {
            PhotonNetwork.Instantiate("BomwP", new Vector3(location.x, location.y, 0), Quaternion.identity, 0);
        }
        else if (type == 2)
        {
            PhotonNetwork.Instantiate("Speed", new Vector3(location.x, location.y, 0), Quaternion.identity, 0);
        }
        else if (type == 3)
        {
            PhotonNetwork.Instantiate("pills", new Vector3(location.x, location.y, 0), Quaternion.identity, 0);
        }
        */
        if (type == 1)
        {
            Instantiate(bombPowerPrefab, new Vector3(location.x, location.y, 0), Quaternion.identity);
        }
        else if (type == 2)
        {
            Instantiate(speedPowerPrefab, new Vector3(location.x, location.y, 0), Quaternion.identity);
        }
        else if (type == 3)
        {
            Instantiate(healthPowerPrefab, new Vector3(location.x, location.y, 0), Quaternion.identity);
        }
    }

    [PunRPC]
    public void DestroyCrate(int viewId)
    {
        GameObject.Destroy(PhotonView.Find(viewId).gameObject);
    }

    [PunRPC]
    public void SpawnExplosion(Vector2 position, float duration)
    {
        GameObject explosion = Instantiate(explosionPrefab, position, Quaternion.identity) as GameObject;
        Destroy(explosion, duration);
    }

    [PunRPC]
    public void IncreaseBomb()
    {
        // PlayerMovement.bombsAvailable++;
        Debug.Log("This shouldn't be called!!!");
    }
}