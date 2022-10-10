using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class NetworkMaster : Photon.PunBehaviour
{
    public GameObject selectlevelButton;
    public GameObject playButton;
    public string leaderSymbol = "Leader: ";
    public List<GameObject> playerNames = new List<GameObject>(4);
    public int maxNrPlayers = 4;
    private void Awake()
    {
        for (int i = 0; i < maxNrPlayers && i < PhotonNetwork.playerList.Length; i++)
        {
            if (PhotonNetwork.playerList[i].IsMasterClient || PhotonNetwork.playerList.Length == 1)
            {
                playerNames[i].GetComponent<Text>().text = leaderSymbol + PhotonNetwork.playerList[i].NickName;
            }
            else
            {
                playerNames[i].GetComponent<Text>().text = PhotonNetwork.playerList[i].NickName;
            }
        }
    }
    private void OnPhotonPlayerConnected()
    {
        for (int i = 0; i < maxNrPlayers && i < PhotonNetwork.playerList.Length; i++)
        {
            if (PhotonNetwork.playerList[i].IsMasterClient || PhotonNetwork.playerList.Length == 1)
            {
                playerNames[i].GetComponent<Text>().text = leaderSymbol + PhotonNetwork.playerList[i].NickName;
            }
            else
            {
                playerNames[i].GetComponent<Text>().text = PhotonNetwork.playerList[i].NickName;
            }
        }
    }

    private void OnPhotonPlayerDisconnected()
    {
        for (int i = 0; i < maxNrPlayers; i++)
        {
            if (i >= PhotonNetwork.playerList.Length)
            {
                playerNames[i].GetComponent<Text>().text = "";
                continue;
            }

            if (PhotonNetwork.playerList[i].IsMasterClient || PhotonNetwork.playerList.Length == 1)
            {
                playerNames[i].GetComponent<Text>().text = leaderSymbol + PhotonNetwork.playerList[i].NickName;
            }
            else
            {
                playerNames[i].GetComponent<Text>().text = PhotonNetwork.playerList[i].NickName;
            }
        }
    }

    private void OnMasterClientSwitched()
    {
        if (PhotonNetwork.isMasterClient || PhotonNetwork.playerList.Length == 1)
        {
            selectlevelButton.SetActive(true);
            playButton.SetActive(true);
        }
    }

    [PunRPC]
    public void SetSpawnPoint(string spawnPointName)
    {
        Debug.Log("Spawn Point Name: " + spawnPointName);
        GameInfo.spawnPointName = spawnPointName;
    }

    [PunRPC]
    public void LoadLevel(int levelNo)
    {
        GameObject.FindGameObjectWithTag("Music").GetComponent<PlayMenuMusic>().StopMusic();
        SceneManager.LoadScene(levelNo);
    }

}
