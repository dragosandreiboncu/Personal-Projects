using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class LobbyScript : Photon.MonoBehaviour
{
    public Text player1, player2, player3, player4;
    public GameObject button1, button2;
    GameObject main;
    string level;
    int levelNo = 3;
    public PhotonView phView;
    public List<string> availableSpawnPoints;
    public Text roomName;

    void Start()
    {
        availableSpawnPoints.Add("SpawnPoint1");
        availableSpawnPoints.Add("SpawnPoint2");
        availableSpawnPoints.Add("SpawnPoint3");
        availableSpawnPoints.Add("SpawnPoint4");
        roomName.text = PhotonNetwork.room.Name;
        if (PhotonNetwork.isMasterClient || PhotonNetwork.playerList.Length == 1)
        {
            button1.SetActive(true);
            button2.SetActive(true);
        }
        main = GameObject.Find("MainLobby");
        level = "Level 1";
        levelNo = 3;
        main.transform.Find(level).gameObject.SetActive(true);
    }

    void Update()
    {
    }
    public void selectCharacter1()
    {
        //MainScript.character = "Character 1";
        GameInfo.prefabNumber = 0;
    }
    public void selectCharacter2()
    {
        //MainScript.character = "Character 2";
        GameInfo.prefabNumber = 1;
    }
    public void selectCharacter3()
    {
        //MainScript.character = "Character 3";
        GameInfo.prefabNumber = 2;
    }
    public void selectCharacter4()
    {
        //MainScript.character = "Character 4";
        GameInfo.prefabNumber = 3;
    }
    public void selectLevel1()
    {
        main.transform.Find(level).gameObject.SetActive(false);
        level = "Level 1";
        levelNo = 3;
        main.transform.Find(level).gameObject.SetActive(true);
    }
    public void selectLevel2()
    {
        main.transform.Find(level).gameObject.SetActive(false);
        level = "Level 2";
        levelNo = 4;
        main.transform.Find(level).gameObject.SetActive(true);
    }
    public void selectLevel3()
    {
        main.transform.Find(level).gameObject.SetActive(false);
        level = "Level 3";
        levelNo = 5;
        main.transform.Find(level).gameObject.SetActive(true);
    }
    public void selectLevel4()
    {
        main.transform.Find(level).gameObject.SetActive(false);
        level = "Level 4";
        levelNo = 6;
        main.transform.Find(level).gameObject.SetActive(true);
    }
    public void play()
    {
        //SceneManager.LoadSceneAsync(level, LoadSceneMode.Additive);
        //SceneManager.UnloadSceneAsync("Lobby");
        PhotonNetwork.room.IsVisible = false;
        PhotonNetwork.room.IsOpen = false;

        for (int i = 0; i < PhotonNetwork.playerList.Length; i++)
        {
            //phView.RPC("SetSpawnPoint", )
            int spawnPointIndex = Random.Range(0, availableSpawnPoints.Count - 1);
            phView.RPC("SetSpawnPoint", PhotonNetwork.playerList[i], availableSpawnPoints[spawnPointIndex]);
            availableSpawnPoints.RemoveAt(spawnPointIndex);
        }
        phView.RPC("LoadLevel", PhotonTargets.All, levelNo);
    }

    public void exitLobby()
    {
        //GameObject.Find("EventSystemLobby").SetActive(false);
        //GameObject.Find("Main").transform.Find("CanvasUI").gameObject.SetActive(true);
        //GameObject.Find("Main").transform.Find("EventSystemUI").gameObject.SetActive(true);
        //SceneManager.UnloadSceneAsync("Lobby");
        Debug.Log("Left Room");
        PhotonNetwork.LeaveRoom();
        //SceneManager.LoadScene(1);
    }

    public void OnLeftRoom()
    {
        SceneManager.LoadScene(1);
    }
}
